#include "led.h"
#include "main.h"

//0回到默认值
void Led_Function(char mode){
 static char flag;
  //翻转LED 
  if(mode==0x00){
    flag=!flag;
    if(flag){
      Set_RGB_Pwm(1023,0,0);
    }
    else{
      Set_RGB_Pwm(0,0,0);
    }
  }
  //开LED
  else if(mode==0x01){
    
  }
  //关LED
  else if(mode==0x02){
    
  }
  //暂定
  else if(mode==0x03){
    
  }
  //暂定
  else if(mode==0x04){
  }  
}