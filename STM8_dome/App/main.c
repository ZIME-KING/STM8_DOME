/**
<<<<<<< HEAD
******************************************************************************
* @file    Project/main.c 
* @author  MCD Application Team
* @version V2.3.0
* @date    16-June-2017
* @brief   Main program body
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
*
* Unless required by applicable law or agreed to in writing, software 
* distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************
*/ 

/*
注意下载需配置OPT2中AFR0位为1 端口复用,选项ST_link ->option_Bytes中设置即可
Port C5 alternate function = TIM2_CH1; port C6 alternate function =
TIM1_CH1; port C7 alternate function = TIM1_CH2.
*/
=======
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"
<<<<<<< HEAD
#include "user_data_processing.h"    
//#include <string.h>
u32 sys_time;

char unsigned send_buf;
//int key_flag_1;
//int key_flag_2;

char power_pattern=0;
char power_flag=1;

unsigned char buff_type[2];
unsigned char user_test;
unsigned char user_test_buf[10];
unsigned char i;
=======
#include "user_function.h"
>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

<<<<<<< HEAD
//unsigned char card_data[2]; 			   

char user_status;
void main(void){
  
  User_Configure_Init();
  
  Set_Buzzer_Pwm(1,500);
  
   GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
   Delay(200);
   GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
   Delay(200); 
   GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
   Delay(200);
     //rc522初始化
//  
  user_status= PcdReset();
  PcdAntennaOff(); 
  Delay(10);
  PcdAntennaOn();  
  user_status= M500PcdConfigISOType( 'A' );
  
  Set_RGB_Pwm(0,0,0);
=======
    void delay(int n){
    int i;
    int ii=200;
    for(i=n;i>0;i--){
      while(ii--);
      ii=200;
    }
    
    }
    
void main(void)
{
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//设置为内部高速时钟
  
  GPIO_ExternalPullUpConfig(GPIOA, GPIO_PIN_ALL, ENABLE);  //接上拉电阻
  GPIO_ExternalPullUpConfig(GPIOB, GPIO_PIN_ALL, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_PIN_ALL, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOD, GPIO_PIN_ALL, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOE, GPIO_PIN_ALL, ENABLE);
  
  GPIO_Init(GPIOA, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_FAST); //高速推挽输出高电平
  GPIO_Init(GPIOB, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(GPIOC, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(GPIOD, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(GPIOE, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_FAST);

  

  
>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
  
  /* Infinite loop */
  while (1)
  {
<<<<<<< HEAD
    //power_pattern进外部中断后至1，启动电源后置0 检测模式
    if(power_pattern==0){
      if(CompareTime(&Task_50)){
        GetTime(&Task_50);
        
        //user_test= PcdRequest(0x52,&buff_type[0]);
       for(i=4;i<10;i++){
          WriteRawRC(0x01,i);  //写
          user_test_buf[i]=ReadRawRC(0x01);
        }
        //WriteRawRC(0x04,0x00);
        //user_status= PcdReset();
        

         
        //user_test=ReadRawRC(0x33);
        //UART1_SendData8(0x10);
        
        //UART1_SendData8(0x10);
       // User_Mfrc522(&M1_Card,1); //数据存M1_Card结构题里，1为读1扇区
         //User_Run_Function();
        /*
        添加自己的函数
        */
      }
      if(CompareTime(&Task_100)){
        GetTime(&Task_100);
        GPIO_WriteReverse(GPIOB, GPIO_PIN_5);

        //运行状态下
        if(power_flag==1){
          if(Get_Key_State()==3){
            EnterHalt();
          }
        }
      }
    }
    //检测电源键模式
    else {
      Power_Control();
    }
  }
=======
    GPIO_WriteReverse(GPIOE, GPIO_PIN_5);
    delay(100);
    GPIO_WriteReverse(GPIOE, GPIO_PIN_5);
    delay(100);
    GPIO_WriteReverse(GPIOE, GPIO_PIN_5);
    delay(100);
    GPIO_WriteReverse(GPIOE, GPIO_PIN_5);
    delay(100);
    GPIO_WriteReverse(GPIOE, GPIO_PIN_5);
    delay(100);
    
    //EnterHalt();
  }
  
>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
}

#ifdef USE_FULL_ASSERT

/**
<<<<<<< HEAD
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
=======
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

>>>>>>> c0ac351fb1e84eab7d5059c79897c66397421437
  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
