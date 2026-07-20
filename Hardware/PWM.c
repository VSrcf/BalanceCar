#include "stm32f10x.h"                  // Device header


/**
  * 函  数：PWM初始化
  * 参  数：无
  * 返回值：无
  * 说  明：配置TIM1的CH1(PA8)和CH4(PA11)输出PWM，用于控制左右电机
  */
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);           // 开启TIM2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);          // 开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;                           // 定义GPIO初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                // 复用推挽输出（PWM输出必须用此模式）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;       // 选择PA0(TIM2_CH1)和PA1(TIM2_CH2)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;              // GPIO速度设为50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);                          // 将配置写入GPIOA
	
	TIM_InternalClockConfig(TIM2);                                 // 选择TIM2时钟源为内部时钟（72MHz）
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              // 定义时基单元初始化结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    // 时钟分频：不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器模式：向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                // ARR自动重装值：99（PWM周期 = 100）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;              // PSC预分频值：35（72MHz / 36 = 2MHz计数频率）
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;           // 重复计数器：不使用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);             // 将配置写入TIM2
	
	TIM_OCInitTypeDef TIM_OCInitStructure;                         // 定义输出比较初始化结构体
	TIM_OCStructInit(&TIM_OCInitStructure);                        // 给结构体填充默认值，避免未赋值成员出问题
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;              // 输出比较模式：PWM模式1（CNT < CCR 时有效电平）
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      // 输出极性：高电平有效
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  // 输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                             // CCR捕获/比较值初始为0（占空比0%）
	
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);                        // 将配置写入TIM2通道1（控制左电机）
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);                        // 将配置写入TIM2通道4（控制右电机）
	
	TIM_CtrlPWMOutputs(TIM2, ENABLE);                              // 使能TIM2的PWM主输出（高级定时器必须加，且在TIM_Cmd之前）
	
	TIM_Cmd(TIM2,ENABLE);                                          // 使能TIM2，开始计数
}

/**
  * 函  数：设置PWM通道1的占空比
  * 参  数：Compare 比较值，范围：0~100（对应占空比0%~100%）
  * 返回值：无
  */
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);                                 // 将比较值写入TIM2的CCR1寄存器
}

/**
  * 函  数：设置PWM通道2的占空比
  * 参  数：Compare 比较值，范围：0~100（对应占空比0%~100%）
  * 返回值：无
  */
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);                                 // 将比较值写入TIM2的CCR2寄存器
}
