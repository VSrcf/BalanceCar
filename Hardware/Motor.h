#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>

void Motor_Init(void);
void Motor_SetPWM(uint8_t n,int8_t PWM);

int8_t Motor_GetLeftSpeed(void);

int8_t Motor_GetRightSpeed(void);


#endif
