#ifndef __user_timer_h_
#define __user_timer_h_
#include "stm8s.h"

void Set_RGB_Pwm(uint16_t R,uint16_t G,uint16_t B);
void user_timer_init();
void Set_Buzzer_Pwm(uint8_t mode,uint16_t time);


#endif