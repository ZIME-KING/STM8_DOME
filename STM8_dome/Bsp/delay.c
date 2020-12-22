#include "delay.h"
#include "stm8s.h"

uint32_t TimingDelay;
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(uint32_t nTime)
{
  TimingDelay = nTime;

  while (TimingDelay != 0);
}


//这个放1ms的定时器中断里面去 对应TIM4
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}