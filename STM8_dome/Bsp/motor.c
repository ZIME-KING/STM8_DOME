#include "main.h"
#include "motor.h"
/***********************************
��������ڲ�������io��������͵�ƽ�ͺ�
L L  ��
H H  ͣ��ɲ����
H L  ��
L H  ��
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
    //��  
  case 0x00:
    IN1_L();
    IN2_L();
    IN3_L();
    IN4_L();
    break;
    //ǰ��
  case 0x01:
    IN1_L();
    IN2_H();
    IN3_L();
    IN4_H();
    
    break;
    //���� 
  case 0x02:
    IN1_H();
    IN2_L();
    IN3_H();
    IN4_L();
    break;
    //ͣ
  case 0x03:
    IN1_H();
    IN2_H();
    IN3_H();
    IN4_H();    
    break;
  }
}