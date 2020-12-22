//#include "user_flash.h"
//#include "main.h"
//#include "stm8s.h"
//
// #define FLASH_EOP 0X04  //标志位
// #define FLASH_DUL 0X08  //标志位
//void FLASH_Init(void)  //端口重映射初始化函数，在此将PC5映射为TIM2_CH1
//{
//    unsigned char *flash_OPT2;
//    unsigned char *flash_NOPT2;
//    flash_OPT2=(unsigned char*)0x4803;   //OPT2寄存器的ADDR
//    flash_NOPT2=(unsigned char*)0x4804;  //NOPT2寄存器的ADDR,此寄存器的值是OPT2的取反值
//    //------------------------------------------------------------- 
//    //第一步  初始化FLASH  
//    while( (FLASH_IAPSR & FLASH_DUL) == 0X00 )      
//    {  
//        FLASH_DUKR = 0XAE;       
//        FLASH_DUKR = 0X56;    
//    } //一旦配置失败，此处将陷入死循环。实际使用请加入超时机制，在此省略 
//    //-------------------------------------------------------------           
//    //第二步  对OPT进行编程，首先需要如下操作：开启opt编程  
//    FLASH_CR2 |= 0X80;     //OPT  = 1  
//    FLASH_NCR2 &= 0X7F;    //NOPT = 0   
//    //-------------------------------------------------------------       
//    //第三步  修改内存  
//    1.修改参数，启用复用功能 
//    2.OPT2 和 NOPT2要相反  
//    //修改OPT2  
//    *flash_OPT2 = 0X01;      // 0000 0001  AFR0=1，PC5复用为TIM2_CH1其它默认清0   
//    while( (FLASH_IAPSR & FLASH_EOP) == 0 );  //等待操作完成   
//    //修改NOPT2  
//    *flash_NOPT2 = ~*flash_OPT2;     
//    while( (FLASH_IAPSR & FLASH_EOP) == 0 );  //等待操作完成  
//    //一旦配置失败，此处将陷入死循环。实际使用请加入超时机制，在此省略
//    //-------------------------------------------------------------   
//    //第四步  对OPT进行编程，最后需要如下操作：禁用opt编程  
//    FLASH_CR2 &= ~0X80;    //OPT  = 1  
//    FLASH_NCR2 |= 0X80;    //NOPT = 0  
//}