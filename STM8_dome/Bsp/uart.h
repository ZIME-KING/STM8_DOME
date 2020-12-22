#ifndef __uart_h
#define __uart_h

#define UART_RX_LENTH  2


typedef struct{
 unsigned char len;
 unsigned char buf[UART_RX_LENTH];
}Uart_TypeDef; 

extern Uart_TypeDef uart_data;
extern unsigned char RX_Buf[UART_RX_LENTH];

void read_buf(Uart_TypeDef *data,unsigned char *p);

#endif