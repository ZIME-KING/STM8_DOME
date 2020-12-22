#include "key.h"
#include "stm8s.h"
#include "user_function.h"

//����ƽʱ���ö�ʱ�����ж� ���ⲿ�жϹص�
//��ͣ��ģʽ���ⲿ�жϴ� 
#define RISE_FLAG        0Xf 
#define DECLINE_FLAG     0Xf0
#define SHOUT_TIME       500     //С��500ms��̰�
#define LONG_TIME        1500    //����1500ms�㳤�������ػ� ����ʱ����Ч

char key_act;   //�������� 0̧�� 1����  2�޶��� 
char key_state; //����״̬ 0���� 1����
char Level_detection_flag;


//��ƽ�ж�
void static Key_Level_detection(){
  Level_detection_flag = Level_detection_flag<<1;
  if(GPIO_ReadInputPin(GPIOC, GPIO_PIN_4)){
    Level_detection_flag++;
  }
 
  //��⵽�����ӣ�����̧��
  if(Level_detection_flag==RISE_FLAG){
    key_act=0;
  }
  //��⵽�½��ӣ���������
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
  //����̧��ʱ�ж�һ��
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

//����Ŷ�ʱ���ж����
void User_Key_Function(){
  Key_Level_detection();
  Key_judgment();
}


char Get_Key_State(){
  char temp = key_state;
  key_state=0;
  return temp;
}


