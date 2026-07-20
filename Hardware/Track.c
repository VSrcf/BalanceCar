#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "OLED.h"




void Infrared_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}




uint8_t Read_L1(void) { return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8); }
uint8_t Read_L2(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); }
uint8_t Read_L3(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1); }
uint8_t Read_L4(void) { return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5); }
uint8_t Read_L5(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4); }
uint8_t Read_L6(void) { return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4); }
uint8_t Read_L7(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5); }
uint8_t Read_L8(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6); }

	
void Infrared_OLED(void)
{
    // 直接读取8个传感器
	uint8_t L1 = Read_L1();
	uint8_t L2 = Read_L2();
	uint8_t L3 = Read_L3();
	uint8_t L4 = Read_L4();
	uint8_t L5 = Read_L5();
	uint8_t L6 = Read_L6();
	uint8_t L7 = Read_L7();
	uint8_t L8 = Read_L8();
	
	
	
}
void Infrared_Track(void)
{
	uint8_t L1 = Read_L1();
	uint8_t L2 = Read_L2();
	uint8_t L3 = Read_L3();
	uint8_t L4 = Read_L4();
	uint8_t L5 = Read_L5();
	uint8_t L6 = Read_L6();
	uint8_t L7 = Read_L7();
	uint8_t L8 = Read_L8();
	
	// 中间 → 直行
	if( L4==0 || L5==0 )
	{
		Go_Ahead();
	}
	// 中左 → 微左转
	else if( L3==0 )
	{
		Turn_Left_Slow();
	}
	// 中右 → 微右转
	else if( L6==0 )
	{
		Turn_Right_Slow();
	}
	// 偏左 → 中左转
	else if( L2==0 )
	{
		Turn_Left_Medium();
	}
	// 偏右 → 中右转
	else if( L7==0 )
	{
		Turn_Right_Medium();
	}
	
	else if( L1==0 )
	{
		Turn_Left_Fast();
	}
	
	else if( L8==0 )
	{
		Turn_Right_Fast();
	}
	// 无线 → 停车
	else
	{
		Car_Stop();
	}
}
	
	
	

