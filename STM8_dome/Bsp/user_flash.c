//#include "user_flash.h"
//#include "main.h"
//#include "stm8s.h"
//
// #define FLASH_EOP 0X04  //��־λ
// #define FLASH_DUL 0X08  //��־λ
//void FLASH_Init(void)  //�˿���ӳ���ʼ���������ڴ˽�PC5ӳ��ΪTIM2_CH1
//{
//    unsigned char *flash_OPT2;
//    unsigned char *flash_NOPT2;
//    flash_OPT2=(unsigned char*)0x4803;   //OPT2�Ĵ�����ADDR
//    flash_NOPT2=(unsigned char*)0x4804;  //NOPT2�Ĵ�����ADDR,�˼Ĵ�����ֵ��OPT2��ȡ��ֵ
//    //------------------------------------------------------------- 
//    //��һ��  ��ʼ��FLASH  
//    while( (FLASH_IAPSR & FLASH_DUL) == 0X00 )      
//    {  
//        FLASH_DUKR = 0XAE;       
//        FLASH_DUKR = 0X56;    
//    } //һ������ʧ�ܣ��˴���������ѭ����ʵ��ʹ������볬ʱ���ƣ��ڴ�ʡ�� 
//    //-------------------------------------------------------------           
//    //�ڶ���  ��OPT���б�̣�������Ҫ���²���������opt���  
//    FLASH_CR2 |= 0X80;     //OPT  = 1  
//    FLASH_NCR2 &= 0X7F;    //NOPT = 0   
//    //-------------------------------------------------------------       
//    //������  �޸��ڴ�  
//    1.�޸Ĳ��������ø��ù��� 
//    2.OPT2 �� NOPT2Ҫ�෴  
//    //�޸�OPT2  
//    *flash_OPT2 = 0X01;      // 0000 0001  AFR0=1��PC5����ΪTIM2_CH1����Ĭ����0   
//    while( (FLASH_IAPSR & FLASH_EOP) == 0 );  //�ȴ��������   
//    //�޸�NOPT2  
//    *flash_NOPT2 = ~*flash_OPT2;     
//    while( (FLASH_IAPSR & FLASH_EOP) == 0 );  //�ȴ��������  
//    //һ������ʧ�ܣ��˴���������ѭ����ʵ��ʹ������볬ʱ���ƣ��ڴ�ʡ��
//    //-------------------------------------------------------------   
//    //���Ĳ�  ��OPT���б�̣������Ҫ���²���������opt���  
//    FLASH_CR2 &= ~0X80;    //OPT  = 1  
//    FLASH_NCR2 |= 0X80;    //NOPT = 0  
//}