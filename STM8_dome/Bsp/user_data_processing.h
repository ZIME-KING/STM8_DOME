#ifndef __user_data_processing_h
#define __user_data_processing_h

#define  RX_LENTH    10    //接收区缓存大小 一次读两字节一定要双数
#define  LOOP_MAX    20    //循环最大次数
#define  CARD_COUNT  5     //同一张卡片最多刷几次
#define  LOOP_ID     0x01
#define  START_0     0x10
#define  START_1     0x10
#define  END_0       0xfe
#define  END_1       0xfe

#define  KEYA        0x60
#define  REQ_ALL        0x52

typedef struct{
  unsigned char TagType[2];    //卡类型
  unsigned char buf[16];       //读出的数据
  char snr;                    //要操作的扇区号
}Card_TypeDef;

typedef struct{
  unsigned char flag;           //帧完成标记   接收完成为0
  unsigned char buf[RX_LENTH];  //帧存储空间
  unsigned char len;            //帧长
}Fream_TypeDef;


typedef struct{
unsigned char  count;             //一个卡一个流程中共刷了几次
unsigned char  pos[CARD_COUNT];  //每次出现的位置
}Card_Data_Typedef;

extern Card_TypeDef  M1_Card;
void User_Mfrc522(Card_TypeDef *card,char snr);
void User_Run_Function();

#endif