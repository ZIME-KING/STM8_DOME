#include "led.h"
#include "main.h"

//0�ص�Ĭ��ֵ
void Led_Function(char mode){
 static char flag;
  //��תLED 
  if(mode==0x00){
    flag=!flag;
    if(flag){
      Set_RGB_Pwm(1023,0,0);
    }
    else{
      Set_RGB_Pwm(0,0,0);
    }
  }
  //��LED
  else if(mode==0x01){
    
  }
  //��LED
  else if(mode==0x02){
    
  }
  //�ݶ�
  else if(mode==0x03){
    
  }
  //�ݶ�
  else if(mode==0x04){
  }  
}