#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Timer.h"
#include "MPU6050.h"
#include "Encoder.h"

uint16_t count;

int16_t AX, AY, AZ,GX,GY,GZ;		
uint8_t TimerErrorFlag;
uint16_t TimerCount;

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	LED_Init();		//LED初始化
	Timer_Init();		//定时器初始化
	MPU6050_Init();		//MPU6050初始化
	Encoder_Init();		//编码器初始化
	
	while (1)
	{
		
		OLED_Printf(0,0,OLED_8X16,"%+06d",AX);		//在OLED上显示加速度数据
		OLED_Printf(0,16,OLED_8X16,"%+06d",AY);
		OLED_Printf(0,32,OLED_8X16,"%+06d",AZ);
		OLED_Printf(64,0,OLED_8X16,"%+06d",GX);
		OLED_Printf(64,16,OLED_8X16,"%+06d",GY);
		OLED_Printf(64,32,OLED_8X16,"%+06d",GZ);
		OLED_Printf(0,48,OLED_8X16,"Flag:%d",TimerErrorFlag);
		OLED_Printf(64,48,OLED_8X16,"C:%d",TimerCount);
		OLED_Update();		//OLED更新显示
		
	}
}

/* 定时器中断函数，可以复制到使用它的地方 */
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

		
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);		//获取MPU6050数据
		
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
		{
			TimerErrorFlag = 1;		//如果中断标志位仍然为SET，则说明中断处理函数执行时间过长，导致下一个中断到来时，上一个中断还未处理完
			TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		}
		TimerCount = TIM_GetCounter(TIM1);		//获取定时器计数值
	}
}

