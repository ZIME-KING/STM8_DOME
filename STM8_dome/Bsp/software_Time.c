/*
 * software_Time.c
 *
 *  Created on: 2020年9月10日
 *      Author: champion
 */
#include "main.h"
#include "software_Time.h"

//获取系统时间
u32 User_GetTick(void){
return sys_time;
}

 TIME_TYPE_ST Task_50;
 TIME_TYPE_ST Task_100;
 //TIME_TYPE_ST Task_500;
 
 //__attribute__机制在main之前运行一次 set_time
//static __attribute__((constructor)) void SetTime();

//设定间隔时间
void SetTime(){
	//Task_1.TimeInter     = 1;//设定间隔时间
	Task_50.TimeInter    = 50;
	Task_100.TimeInter   = 100;
	//Task_200.TimeInter   = 200;
	//Task_500.TimeInter   = 500;
	//Task_1000.TimeInter  = 1000;
}
void GetTime(TIME_TYPE_ST *TimeType)
{
    TimeType->TimeStart = User_GetTick();//获取起始时间
}
 
uint8_t CompareTime(TIME_TYPE_ST *TimeType)//每隔1毫秒，计数器就会增加1
{
  if((User_GetTick()-TimeType->TimeStart) >= TimeType->TimeInter)
    return 1;
  else
    return 0;
  
}
