#include "uart.h"
#include "main.h"

Uart_TypeDef uart_data;

unsigned char RX_Buf[UART_RX_LENTH];

//��ȡ����
void read_buf(Uart_TypeDef *data,unsigned char *p){
  unsigned char i;
  //��ʼ�������������
  for(i=0;i<UART_RX_LENTH;i++){
    *p=0;
    p++;
  }
  //�����ݸ�ֵ
  for(i=0;i<data->len;i++){
    *p=data->buf[i];
    p++;
  }
  //�����������
  for(i=0;i<UART_RX_LENTH;i++){
    data->buf[i]=0;
  }
  data->len=0;
}