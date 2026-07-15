#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Car.h"

void Car_Init(void)
{
	Motor_Init();
}
// 直行
void Go_Ahead(void)
{
	Motor_SetLeftSpeed(16);
	Motor_SetRightSpeed(16);
}
//哈哈哈哈
void Go_Back(void)
{
	Motor_SetLeftSpeed(-16);
	Motor_SetRightSpeed(-16);
}

// 快转
void Turn_Left_Fast(void)
{
	Motor_SetLeftSpeed(5);
	Motor_SetRightSpeed(20);
}
void Turn_Right_Fast(void)
{
	Motor_SetLeftSpeed(20);
	Motor_SetRightSpeed(5);
}

// 慢转弯（循迹微调）
void Turn_Left_Slow(void)
{
	Motor_SetLeftSpeed(13);
	Motor_SetRightSpeed(20);
}
void Turn_Right_Slow(void)
{
	Motor_SetLeftSpeed(20);
	Motor_SetRightSpeed(13);
}

// 中等转弯
void Turn_Left_Medium(void)
{
	Motor_SetLeftSpeed(10);
	Motor_SetRightSpeed(20);
}
void Turn_Right_Medium(void)
{
	Motor_SetLeftSpeed(20);
	Motor_SetRightSpeed(10);
}

// 原地转圈
void Self_Left(void)
{
	Motor_SetLeftSpeed(-15);
	Motor_SetRightSpeed(15);
}
void Self_Right(void)
{
	Motor_SetLeftSpeed(15);
	Motor_SetRightSpeed(-15);
}

// 停车
void Car_Stop(void)
{
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}
