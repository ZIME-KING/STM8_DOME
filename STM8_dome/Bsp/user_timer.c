//定时器1ch1，ch2输出，定时器2 ch2 硬件pwm输出
//定时器3     1ms时基

/* Includes ------------------------------------------------------------------*/
#include "user_timer.h"
#include "main.h"
#include "stm8s.h"


uint16_t TIM1_CCR1_Val=1023;
uint16_t TIM1_CCR2_Val=512;
uint16_t TIM2_CCR1_Val=512;
uint16_t TIM2_CCR2_Val=0;

static void TIM1_Config(void);
static void TIM2_Config(void);
static void TIM4_Config(void);

static void TIM1_Config(void)
{
  TIM1_DeInit();
  /* Time Base configuration */
  TIM1_DeInit();  
  
  TIM1_TimeBaseInit(TIM2_PRESCALER_16, TIM1_COUNTERMODE_UP,1024, 0x00);  //16分频向上计数，最大为4095 预载值为0
  
  TIM1_OC1Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, 
               TIM1_OUTPUTNSTATE_DISABLE, 
               TIM1_CCR1_Val, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH,
               TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_SET);
  
  TIM1_OC2Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, 
               TIM1_OUTPUTNSTATE_DISABLE, 
               TIM1_CCR2_Val, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH,
               TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_SET);
  
  
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);
}

static void TIM2_Config(void)
{
  TIM2_DeInit();
  
  
  TIM2_TimeBaseInit(TIM2_PRESCALER_16,1023);        //16分频，最大为1023到1023清0
  
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,
               TIM2_CCR1_Val, 
               TIM2_OCPOLARITY_HIGH);
  
  TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,
               TIM2_CCR2_Val, 
               TIM2_OCPOLARITY_HIGH);
  
  TIM2_Cmd(ENABLE);
  
}

void Set_RGB_Pwm(uint16_t R,uint16_t G,uint16_t B){
  TIM1_CCR1_Val=R;
  TIM1_CCR2_Val=G;
  TIM2_CCR1_Val=B;
  TIM1_Config();
  TIM2_Config();
}

//mode:音色，调占空比实现频率改频率灯的pwm这边也要改不动先
//time：持续时间单位ms
void Set_Buzzer_Pwm(uint8_t mode,uint16_t time){
  
  if(mode==0)
    TIM2_CCR2_Val=333;
  else if(mode==1)
    TIM2_CCR2_Val=666;
  else if(mode==2)
    TIM2_CCR2_Val=999;
  
  TIM2_Config();
  
  Delay(time);
  TIM2_CCR2_Val=0;
  TIM2_Config(); 
}




#define TIM4_PERIOD       124
static void TIM4_Config(void)
{
  /* TIM4 configuration:
  - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
  clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
  max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
  min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
  so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */
  
  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  
  /* enable interrupts */
  enableInterrupts();
  
  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}


void user_timer_init()
{
  TIM1_Config();
  TIM2_Config();
  TIM4_Config();
}