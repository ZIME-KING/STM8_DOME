#include "stm8s.h"
#include "user_function.h"

void EXTI_Init(){
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_LOW);  //����c���ⲿ�жϵ͵�ƽ���½��Ӵ���
}

/*****************************************************************
//���뵽ͣ��ģʽ
*****************************************************************/
void EnterHalt()
{
    int j=255;
    
    /* ��ֹ��ʱ���жϻ�����CPU */
//    TIM1_CR1 &= 0xFE;     /*  �û������������ص� */

    asm("sim");               //��ֹ�жϣ��������ж�֮ǰҪ�ȹر��ж�

    EXTI_Init();
    for(j=255;j>0;j--);  //��ʱһ��

    asm("rim");   //�����ж�
    asm("HALT"); /* ����ͣ��ģʽ */
}
