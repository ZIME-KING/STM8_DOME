#ifndef __main_h
#define __main_h

#include "stm8s.h"
#include "user_function.h"
#include "delay.h"
#include "user_timer.h"
#include "key.h"
#include "stdio.h"
#include "software_Time.h"
#include "MFRC522.h"
#include "led.h"
#include "motor.h"
#include "uart.h"

extern u32 sys_time;
extern char power_pattern; 
extern char power_flag;
extern unsigned char send_buf;
#define SPI_MISO_READ() GPIO_ReadInputPin(GPIOD, GPIO_PIN_6)

#define SPI_MOSI_L() GPIO_WriteLow(GPIOD, GPIO_PIN_2)
#define SPI_MOSI_H() GPIO_WriteHigh(GPIOD, GPIO_PIN_2)

#define SPI_SCK_L() GPIO_WriteLow(GPIOD, GPIO_PIN_3)
#define SPI_SCK_H() GPIO_WriteHigh(GPIOD, GPIO_PIN_3)

#define SPI_NSS_L() GPIO_WriteLow(GPIOD, GPIO_PIN_5)
#define SPI_NSS_H() GPIO_WriteHigh(GPIOD, GPIO_PIN_5)

#define RC522_RST_L() GPIO_WriteLow(GPIOD, GPIO_PIN_4)
#define RC522_RST_H() GPIO_WriteHigh(GPIOD, GPIO_PIN_4)


////MFRC522
//sbit     MF522_RST  =    P1^4;                   //RC500??
//sbit     MF522_NSS  =    P1^2;   SDA
//sbit     MF522_SCK  =    P1^1;
//sbit     MF522_SI   =    P1^0;
//sbit     MF522_SO   =    P1^3;
//
//sbit     LED_GREEN  =    P1^5;     
//


#endif
