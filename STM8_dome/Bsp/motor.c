#include "main.h"
#include "motor.h"
/***********************************
电机驱动内部下拉，io配置输出低电平就好
L L  关
H H  停（刹车）
H L  正
L H  反
*************************************/
#define IN1_L()  GPIO_WriteLow(GPIOA, GPIO_PIN_0)
#define IN1_H()  GPIO_WriteHigh(GPIOA, GPIO_PIN_0)

#define IN2_L()  GPIO_WriteLow(GPIOA, GPIO_PIN_0)
#define IN2_H()  GPIO_WriteHigh(GPIOA, GPIO_PIN_0)

#define IN3_L()  GPIO_WriteLow(GPIOA, GPIO_PIN_0)
#define IN3_H()  GPIO_WriteHigh(GPIOA, GPIO_PIN_0)

#define IN4_L()  GPIO_WriteLow(GPIOA, GPIO_PIN_0)
#define IN4_H()  GPIO_WriteHigh(GPIOA, GPIO_PIN_0)

void Motor_Function(unsigned char mode){
  switch(mode){
    //关  
  case 0x00:
    IN1_L();
    IN2_L();
    IN3_L();
    IN4_L();
    break;
    //前进
  case 0x01:
    IN1_L();
    IN2_H();
    IN3_L();
    IN4_H();
    
    break;
    //后退 
  case 0x02:
    IN1_H();
    IN2_L();
    IN3_H();
    IN4_L();
    break;
    //停
  case 0x03:
    IN1_H();
    IN2_H();
    IN3_H();
    IN4_H();    
    break;
  }
}