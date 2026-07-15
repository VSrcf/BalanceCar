#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"
#include "Track.h"
#include "Motor.h"
#include "Timer.h"
#include "PID.h"



int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Encoder1_Init();
	Encoder2_Init();
	
	Motor_Init();
	Infrared_Init();
	Timer_Init();
	
	pid_Init(&left_pid, DELTA_PID, 0.5f, 0.01f, 0.0f, 50.0f);
	pid_Init(&right_pid, DELTA_PID, 0.5f, 0.01f, 0.0f, 50.0f);
	
	OLED_ShowString(1, 1, "M1:");
	OLED_ShowString(2, 1, "M2:");

	
	while (1)
	{
		OLED_ShowNum(1, 5, Speed1, 4);
		OLED_ShowNum(2, 5, Speed2, 4);
		
		
	}
}


