#include "stm8s.h"
#include "user_function.h"

void EXTI_Init(){
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_LOW);  //设置c口外部中断低电平和下降延触发
}

/*****************************************************************
//进入到停机模式
*****************************************************************/
void EnterHalt()
{
    int j=255;
    
    /* 防止定时器中断唤醒了CPU */
//    TIM1_CR1 &= 0xFE;     /*  用户操作计数器关掉 */

    asm("sim");               //禁止中断，在配置中断之前要先关闭中断

    EXTI_Init();
    for(j=255;j>0;j--);  //延时一会

    asm("rim");   //启动中断
    asm("HALT"); /* 进入停机模式 */
}
