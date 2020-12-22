/*************************************************************************
*说明一张卡读两个字节，第一个字节为卡片类型，第二个为值
*卡片类型有灯类卡，电机类卡，延时类卡，按第2个字节的内容执行相应动作
*循环卡类可以在任意位置刷入，值可叠，根据值控制整个流程的次数
*开始卡和结束卡仅用做开始结束数据判断不保存内容
**************************************************************************/
#include "user_data_processing.h"
#include "main.h"
#include "stm8s.h"

unsigned char  DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  //默认验证密码不改
unsigned char  SelectedSnr[4];  //防冲撞机制下返回的卡号      
//unsigned char  temp_buf[16]={0x10,0x10,0xfe,0x01,0x01,0x01,0x01,0x01,0x01};

Card_TypeDef  M1_Card;
Fream_TypeDef R_fream;
Card_Data_Typedef loop;
//等待卡离开
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
//接收数据处理
void Fream_Handle(Card_TypeDef *card,Fream_TypeDef *fream){
  char i;
  static unsigned char count;
  
  //是结束卡
  if(card->buf[0]==END_0 && card->buf[1]==END_1){
   fream->flag=0;   //数据接收完成标记
  }
  
  if(fream->flag==1){
    if(card->buf[0]==0x01 ||card->buf[0]==0x02 ||card->buf[0]==0x03||card->buf[0]==0x04){
      fream->buf[count]   = card->buf[0] ;
      fream->buf[count+1] = card->buf[1] ;
      count+=2;
    }
  }
  
  //是开始卡
  if(card->buf[0]==START_0 && card->buf[1]==START_1){
   //运行数据清空
    for(i=0;i<RX_LENTH;i++){
   fream->buf[i]=0;
    }
   count=0;
   fream->flag=1;   //数据开始接收标记
  }
  fream->len=count;
}
//读卡相关操作
//保存卡结构体
//读取的扇区
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
        //snr = 1;  //扇区号1
        card->snr=snr;
        status = PcdAuthState(KEYA, ((card->snr)*4+3), DefaultKey, SelectedSnr);// 校验1扇区密码，密码位于每一扇区第3块
        {
          if(!status)
          {
            status = PcdRead(((card->snr) * 4 + 0), &card->buf[0]);  // 读卡，读取1扇区0块数据到buf[0]-buf[16] 
            Fream_Handle(card,&R_fream);
            card->buf[0]=0;
            card->buf[1]=0;     
           // status = PcdWrite((1*4+0), &temp_buf[0]);  // 写卡，将buf[0]-buf[16]写入1扇区0块
            if(!status)
            {
              //读写成功，点亮LED
              //LED_GREEN = 0;	
              WaitCardOff();
            }
          }
        }
      }
    }
  }
}


//传入卡片数据
//执行相应动作
//返回延时的时间
unsigned Judge_Card(char type,char value){
  //暂定这四大类
  switch(type){
  case 0x01:       //循环不做操作
    return 0;
    break;
  case 0x02:       //延时单位s
    return (value*1000);
    break;
  case 0x03:        //电机相关
    //Motor_Function(value);
    return 500;
    break;
  case 0x04:        //灯相关
    Led_Function(value);
    return 200;
    break;
  }
  return 0;
}
// 
void Run_Function(){
  char cycles=1;//循环次数
  char i,ii;
  unsigned int time;
  //找循环卡个数和坐标
  for(i=0;i<RX_LENTH;i++){
    if(R_fream.buf[i]==LOOP_ID){
      loop.pos[loop.count]=i;
      loop.count++;
      if(loop.count>CARD_COUNT)loop.count=CARD_COUNT;
    }
  }
  //计算循环次数
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
  //接收完成且有数据
  if(R_fream.buf[0]!=0 && R_fream.flag==0){
    Run_Function();    //执行动作
    R_fream.buf[0]=0;
  }
}




