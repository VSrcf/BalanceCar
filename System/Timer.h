#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
#include "PID.h"

void Timer_Init(void);
void speed_loop(pid_t *pid,float target_speed,float current_speed, uint8_t is_left);
void TIM3_IRQHandler(void);

extern  int16_t Speed1;
extern  int16_t Speed2;

#endif
