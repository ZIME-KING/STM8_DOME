<<<<<<< HEAD
#include "main.h"
#include "user_function.h"
=======
#include "stm8s.h"
#include "user_function.h"

void EXTI_Init(){
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_LOW);  //����c���ⲿ�жϵ͵�ƽ���½��Ӵ���
}

>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
/*****************************************************************
//���뵽ͣ��ģʽ
*****************************************************************/
void EnterHalt()
{
<<<<<<< HEAD
  int j=255;
  
  power_flag=0;       //power_flag�ϵ�Ϊ1
  power_pattern=1;
  
  /* ��ֹ��ʱ���жϻ�����CPU*/
  TIM1_Cmd(DISABLE);
  
  asm("sim");               //��ֹ�жϣ��������ж�֮ǰҪ�ȹر��ж�
  
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);                        //C4 �����������ж� 
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY); //����c���ⲿ�ж� �½��Ӵ���
  
  for(j=255;j>0;j--);  //��ʱһ������ض�ʱ���˾Ͳ���Delay��
  
  asm("rim");   //�����ж�
  asm("HALT"); /* ����ͣ��ģʽ */
}

/*****************************************************************
//�˳�ͣ��ģʽ
//mode =1 ����Դ���ģʽ
//mode =0 ������������
*****************************************************************/
void ExitHalt(char mode) {
  TIM1_Cmd(ENABLE); //���¿���ʱ��
  //PC3 ����Ϊ��ͨIO�� �������ж� ���ڰ������
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
  
  if(mode==1) power_pattern=1;           //������ģʽ
  else if(mode==0) power_pattern=0;     //����������ģʽ
  
  power_flag=1;
}

void Sysclk_Init(){
  CLK_HSICmd(ENABLE);                        //�����ڲ�ʱ��Դ
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);   //1��Ƶ16mhz
  //����ʱ��Ƶ��
  //u32_clk_freq = CLK_GetClockFreq();     
}

/***********************
//��Դ����
************************/
void Power_Control(){
  static u32 temp_time;
  temp_time=User_GetTick();
  //��5s�ڼ�ⰴ���Ƿ�Ϊ���� �����������˳����������Ǽ���ͣ��
  while((User_GetTick()-temp_time)<5000){
    if(Get_Key_State()==3){
      ExitHalt(0);     //�˳�ͣ��ģʽ��������
      return;
    }
    
  }
  EnterHalt();
}

/***********************
//IO�ڳ�ʼ��
************************/
void User_GPIO_init(){
  GPIO_ExternalPullUpConfig(GPIOA, GPIO_PIN_ALL, ENABLE);  //����������
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_PIN_ALL, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_PIN_ALL, ENABLE);

  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_SLOW);

  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);   //C4 �����������ж�
}

void SPI_init(){
  //GPIO_ExternalPullUpConfig(GPIOD, GPIO_PIN_ALL, ENABLE);
  GPIO_Init(GPIOD, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);  //D�����ģ��SPI ���ٿ����ø���ģʽ����ԭ��δ֪
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);        //D6 MISO�����������ж�
}

/***********************
//���ڳ�ʼ��
************************/
void User_UART1_Init(){
  
  UART1_DeInit(); 
   //���ͽ������ǿڳ�ʼ��
   GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
   GPIO_Init(GPIOD,GPIO_PIN_6, GPIO_MODE_IN_PU_IT);  
   
   //UART�Ĳ�����ʼ��
   UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
   
   //UART�ж�ʹ��
   UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
   //�����ж� 
   //UART1_ITConfig(UART1_IT_TXE, ENABLE);
   //ʹ��UART
   UART1_Cmd(ENABLE);
   
   //�ж�ʹ��
   enableInterrupts();  
}
/***********************
//�û����ó�ʼ��
************************/
void User_Configure_Init(){
  SetTime();            //�����ʱ��ʼ��
  Sysclk_Init();        //ϵͳʱ�ӳ�ʼ��
  User_GPIO_init();     //GPIO��ʼ��
  User_UART1_Init();    //
  user_timer_init();    //�û���ʱ����ʼ��
  //SPI_init();
}



////�����ַ���
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
    
    /* ��ֹ��ʱ���жϻ�����CPU */
//    TIM1_CR1 &= 0xFE;     /*  �û������������ص� */

    asm("sim");               //��ֹ�жϣ��������ж�֮ǰҪ�ȹر��ж�

    EXTI_Init();
    for(j=255;j>0;j--);  //��ʱһ��

    asm("rim");   //�����ж�
    asm("HALT"); /* ����ͣ��ģʽ */
}
>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
