/*************************************************************************
*˵��һ�ſ��������ֽڣ���һ���ֽ�Ϊ��Ƭ���ͣ��ڶ���Ϊֵ
*��Ƭ�����е��࿨������࿨����ʱ�࿨������2���ֽڵ�����ִ����Ӧ����
*ѭ���������������λ��ˢ�룬ֵ�ɵ�������ֵ�����������̵Ĵ���
*��ʼ���ͽ�������������ʼ���������жϲ���������
**************************************************************************/
#include "user_data_processing.h"
#include "main.h"
#include "stm8s.h"

unsigned char  DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  //Ĭ����֤���벻��
unsigned char  SelectedSnr[4];  //����ײ�����·��صĿ���      
//unsigned char  temp_buf[16]={0x10,0x10,0xfe,0x01,0x01,0x01,0x01,0x01,0x01};

Card_TypeDef  M1_Card;
Fream_TypeDef R_fream;
Card_Data_Typedef loop;
//�ȴ����뿪
void WaitCardOff(void)
{
  unsigned char status, TagType[2];
  while(1)
  {
    status = PcdRequest(REQ_ALL, TagType);
    if(status)
    {
      status = PcdRequest(REQ_ALL, TagType);
      if(status)
      {
        status = PcdRequest(REQ_ALL, TagType);
        if(status)
        {
          return;
        }
      }
    }
    Delay(1);
  }
}
//�������ݴ���
void Fream_Handle(Card_TypeDef *card,Fream_TypeDef *fream){
  char i;
  static unsigned char count;
  
  //�ǽ�����
  if(card->buf[0]==END_0 && card->buf[1]==END_1){
   fream->flag=0;   //���ݽ�����ɱ��
  }
  
  if(fream->flag==1){
    if(card->buf[0]==0x01 ||card->buf[0]==0x02 ||card->buf[0]==0x03||card->buf[0]==0x04){
      fream->buf[count]   = card->buf[0] ;
      fream->buf[count+1] = card->buf[1] ;
      count+=2;
    }
  }
  
  //�ǿ�ʼ��
  if(card->buf[0]==START_0 && card->buf[1]==START_1){
   //�����������
    for(i=0;i<RX_LENTH;i++){
   fream->buf[i]=0;
    }
   count=0;
   fream->flag=1;   //���ݿ�ʼ���ձ��
  }
  fream->len=count;
}
//������ز���
//���濨�ṹ��
//��ȡ������
void User_Mfrc522(Card_TypeDef *card,char snr){
  char status;
  status= PcdRequest(0x52,&card->TagType[0]);
  if(!status)
  {
    status = PcdAnticoll(SelectedSnr);
    if(!status)
    {
      status=PcdSelect(SelectedSnr);
      if(!status)
      {
        //snr = 1;  //������1
        card->snr=snr;
        status = PcdAuthState(KEYA, ((card->snr)*4+3), DefaultKey, SelectedSnr);// У��1�������룬����λ��ÿһ������3��
        {
          if(!status)
          {
            status = PcdRead(((card->snr) * 4 + 0), &card->buf[0]);  // ��������ȡ1����0�����ݵ�buf[0]-buf[16] 
            Fream_Handle(card,&R_fream);
            card->buf[0]=0;
            card->buf[1]=0;     
           // status = PcdWrite((1*4+0), &temp_buf[0]);  // д������buf[0]-buf[16]д��1����0��
            if(!status)
            {
              //��д�ɹ�������LED
              //LED_GREEN = 0;	
              WaitCardOff();
            }
          }
        }
      }
    }
  }
}


//���뿨Ƭ����
//ִ����Ӧ����
//������ʱ��ʱ��
unsigned Judge_Card(char type,char value){
  //�ݶ����Ĵ���
  switch(type){
  case 0x01:       //ѭ����������
    return 0;
    break;
  case 0x02:       //��ʱ��λs
    return (value*1000);
    break;
  case 0x03:        //������
    //Motor_Function(value);
    return 500;
    break;
  case 0x04:        //�����
    Led_Function(value);
    return 200;
    break;
  }
  return 0;
}
// 
void Run_Function(){
  char cycles=1;//ѭ������
  char i,ii;
  unsigned int time;
  //��ѭ��������������
  for(i=0;i<RX_LENTH;i++){
    if(R_fream.buf[i]==LOOP_ID){
      loop.pos[loop.count]=i;
      loop.count++;
      if(loop.count>CARD_COUNT)loop.count=CARD_COUNT;
    }
  }
  //����ѭ������
  for(i=0;i<loop.count;i++){
    cycles+=R_fream.buf[loop.pos[i]+1];
  }
  if(cycles>LOOP_MAX) cycles=LOOP_MAX;
    
  for(ii=0;ii<cycles;ii++){
    for(i=0;i<R_fream.len;i+=2){
      time=Judge_Card(R_fream.buf[i],R_fream.buf[i+1]);
      Delay(time);
  }
  }
}

void User_Run_Function(){
  //���������������
  if(R_fream.buf[0]!=0 && R_fream.flag==0){
    Run_Function();    //ִ�ж���
    R_fream.buf[0]=0;
  }
}




