#ifndef __user_data_processing_h
#define __user_data_processing_h

#define  RX_LENTH    10    //�����������С һ�ζ����ֽ�һ��Ҫ˫��
#define  LOOP_MAX    20    //ѭ��������
#define  CARD_COUNT  5     //ͬһ�ſ�Ƭ���ˢ����
#define  LOOP_ID     0x01
#define  START_0     0x10
#define  START_1     0x10
#define  END_0       0xfe
#define  END_1       0xfe

#define  KEYA        0x60
#define  REQ_ALL        0x52

typedef struct{
  unsigned char TagType[2];    //������
  unsigned char buf[16];       //����������
  char snr;                    //Ҫ������������
}Card_TypeDef;

typedef struct{
  unsigned char flag;           //֡��ɱ��   �������Ϊ0
  unsigned char buf[RX_LENTH];  //֡�洢�ռ�
  unsigned char len;            //֡��
}Fream_TypeDef;


typedef struct{
unsigned char  count;             //һ����һ�������й�ˢ�˼���
unsigned char  pos[CARD_COUNT];  //ÿ�γ��ֵ�λ��
}Card_Data_Typedef;

extern Card_TypeDef  M1_Card;
void User_Mfrc522(Card_TypeDef *card,char snr);
void User_Run_Function();

#endif