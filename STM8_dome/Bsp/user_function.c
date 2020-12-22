<<<<<<< HEAD
#include "main.h"
#include "user_function.h"
=======
#include "stm8s.h"
#include "user_function.h"

void EXTI_Init(){
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_LOW);  //设置c口外部中断低电平和下降延触发
}

>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
/*****************************************************************
//进入到停机模式
*****************************************************************/
void EnterHalt()
{
<<<<<<< HEAD
  int j=255;
  
  power_flag=0;       //power_flag上电为1
  power_pattern=1;
  
  /* 防止定时器中断唤醒了CPU*/
  TIM1_Cmd(DISABLE);
  
  asm("sim");               //禁止中断，在配置中断之前要先关闭中断
  
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);                        //C4 上拉输入有中断 
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY); //设置c口外部中断 下降延触发
  
  for(j=255;j>0;j--);  //延时一会这里关定时器了就不用Delay了
  
  asm("rim");   //启动中断
  asm("HALT"); /* 进入停机模式 */
}

/*****************************************************************
//退出停机模式
//mode =1 到电源检测模式
//mode =0 到运行主程序
*****************************************************************/
void ExitHalt(char mode) {
  TIM1_Cmd(ENABLE); //重新开定时器
  //PC3 配置为普通IO口 输入无中断 用于按键检测
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
  
  if(mode==1) power_pattern=1;           //进入检测模式
  else if(mode==0) power_pattern=0;     //进入主程序模式
  
  power_flag=1;
}

void Sysclk_Init(){
  CLK_HSICmd(ENABLE);                        //启用内部时钟源
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);   //1分频16mhz
  //返回时钟频率
  //u32_clk_freq = CLK_GetClockFreq();     
}

/***********************
//电源控制
************************/
void Power_Control(){
  static u32 temp_time;
  temp_time=User_GetTick();
  //在5s内检测按键是否为长按 是择启动，退出函数，不是继续停机
  while((User_GetTick()-temp_time)<5000){
    if(Get_Key_State()==3){
      ExitHalt(0);     //退出停机模式到主程序
      return;
    }
    
  }
  EnterHalt();
}

/***********************
//IO口初始化
************************/
void User_GPIO_init(){
  GPIO_ExternalPullUpConfig(GPIOA, GPIO_PIN_ALL, ENABLE);  //接上拉电阻
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_PIN_ALL, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_PIN_ALL, ENABLE);

  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_SLOW);

  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);   //C4 上拉输入无中断
}

void SPI_init(){
  //GPIO_ExternalPullUpConfig(GPIOD, GPIO_PIN_ALL, ENABLE);
  GPIO_Init(GPIOD, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);  //D口软件模拟SPI 低速可以用高速模式不行原因未知
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);        //D6 MISO上拉输入无中断
}

/***********************
//串口初始化
************************/
void User_UART1_Init(){
  
  UART1_DeInit(); 
   //发送接收引角口初始化
   GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
   GPIO_Init(GPIOD,GPIO_PIN_6, GPIO_MODE_IN_PU_IT);  
   
   //UART的参数初始化
   UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
   
   //UART中断使能
   UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
   //发送中断 
   //UART1_ITConfig(UART1_IT_TXE, ENABLE);
   //使能UART
   UART1_Cmd(ENABLE);
   
   //中断使能
   enableInterrupts();  
}
/***********************
//用户配置初始化
************************/
void User_Configure_Init(){
  SetTime();            //软件分时初始化
  Sysclk_Init();        //系统时钟初始化
  User_GPIO_init();     //GPIO初始化
  User_UART1_Init();    //
  user_timer_init();    //用户定时器初始化
  //SPI_init();
}



////发送字符串
//void Send_Str(char *p){
//  
//  while(*p != '\0'){
//    UART1_SendData8(*p);
//    p++;
//    while(!UART1_GetFlagStatus(UART1_FLAG_TXE)); 
//  }
//}
//


=======
    int j=255;
    
    /* 防止定时器中断唤醒了CPU */
//    TIM1_CR1 &= 0xFE;     /*  用户操作计数器关掉 */

    asm("sim");               //禁止中断，在配置中断之前要先关闭中断

    EXTI_Init();
    for(j=255;j>0;j--);  //延时一会

    asm("rim");   //启动中断
    asm("HALT"); /* 进入停机模式 */
}
>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
