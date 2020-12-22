#include "uart.h"
#include "main.h"

Uart_TypeDef uart_data;

unsigned char RX_Buf[UART_RX_LENTH];

//读取数据
void read_buf(Uart_TypeDef *data,unsigned char *p){
  unsigned char i;
  //开始接收先数据清空
  for(i=0;i<UART_RX_LENTH;i++){
    *p=0;
    p++;
  }
  //给数据赋值
  for(i=0;i<data->len;i++){
    *p=data->buf[i];
    p++;
  }
  //缓存数据清空
  for(i=0;i<UART_RX_LENTH;i++){
    data->buf[i]=0;
  }
  data->len=0;
}