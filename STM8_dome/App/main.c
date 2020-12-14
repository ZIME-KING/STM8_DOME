/**
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


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"
#include "user_function.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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

  

  
  
  /* Infinite loop */
  while (1)
  {
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
  
}

#ifdef USE_FULL_ASSERT

/**
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

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
