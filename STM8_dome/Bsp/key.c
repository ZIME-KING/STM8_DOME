#include "key.h"
#include "stm8s.h"
#include "user_function.h"

//按键平时钟用定时器做判断 把外部中断关掉
//进停机模式把外部中断打开 
#define RISE_FLAG        0Xf 
#define DECLINE_FLAG     0Xf0
#define SHOUT_TIME       500     //小于500ms算短按
#define LONG_TIME        1500    //大于1500ms算长按（）关机 其他时间无效

char key_act;   //按键动作 0抬起 1按下  2无动作 
char key_state; //按键状态 0空闲 1按下
char Level_detection_flag;


//电平判断
void static Key_Level_detection(){
  Level_detection_flag = Level_detection_flag<<1;
  if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_4)){
    Level_detection_flag++;
  }
 
  //检测到上升延，按键抬起
  if(Level_detection_flag==RISE_FLAG){
    key_act=0;
  }
  //检测到下降延，按键按下
  else if(Level_detection_flag==DECLINE_FLAG){
    key_act=1;
  }
  else{
    key_act=2;
  }


}
void static Key_judgment(){ 
  static unsigned int count;
  static char count_flag;
  if(key_act==1){
    count_flag=1;
  }
  //按键抬起时判断一下
  if(key_act==0){
    count_flag=0;
    if(count != 0){
      if(10 < count && count<SHOUT_TIME){
        key_state=1;
      }
      else if(count>LONG_TIME ){
        key_state=3;
      }
      else{
        key_state=0;
      }
    }
  }
  
  if(count_flag){
    count++;
  }
  else{
    count=0;
  }
}

//这个放定时器中断里的
void User_Key_Function(){
  Key_Level_detection();
  Key_judgment();
}


char Get_Key_State(){
  char temp = key_state;
  key_state=0;
  return temp;
}


