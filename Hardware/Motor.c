#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"

int16_t Motor_LeftSpeed;		//定义左轮速度变量
int16_t Motor_RightSpeed;	//定义右轮速度变量

/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PB12和PB13和PB14和PB15引脚初始化为推挽输出	
	
	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：PWM 要设置的PWM值，范围：-100~100
  * 返 回 值：无
  */
void Motor_SetPWM(uint8_t n,int8_t PWM)
{
	if(n == 1)
	{
		
	if (PWM > 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_13);	//PB13置高电平
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	//PB12置低电平，设置方向为正转
		PWM_SetCompare1(PWM);				//PWM设置为速度值
		
	}
	else if (PWM == 0)								
	{                                        //停止
		GPIO_SetBits(GPIOB, GPIO_Pin_13);	//PB13置高电平
		GPIO_SetBits(GPIOB ,GPIO_Pin_12);	//PB12置高电平
		PWM_SetCompare1(PWM);			
		
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);	//PB13置低电平
		GPIO_SetBits(GPIOB ,GPIO_Pin_12);	//PB12置高电平，设置方向为反转
		PWM_SetCompare1(-PWM);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
		
	}

	}
	else if(n == 2)
	{
		if (PWM > 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);	//PB14置高电平
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);	//PB15置低电平，设置方向为正转
		PWM_SetCompare2(PWM);				//PWM设置为速度值
		
	}
	else if (PWM == 0)								
	{                                        //停止
		GPIO_SetBits(GPIOB, GPIO_Pin_14);	//PB14置高电平
		GPIO_SetBits(GPIOB ,GPIO_Pin_15);	//PB15置高电平
		PWM_SetCompare2(PWM);			
		
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);	//PB14置低电平
		GPIO_SetBits(GPIOB ,GPIO_Pin_15);	//PB15置高电平，设置方向为反转
		PWM_SetCompare2(-PWM);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
		
	}
	}
	
}


int8_t Motor_GetLeftSpeed(void)
{
	return Motor_LeftSpeed;
}

// 读取右轮当前速度
int8_t Motor_GetRightSpeed(void)
{
	return Motor_RightSpeed;
}
