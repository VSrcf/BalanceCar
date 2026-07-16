#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>

void Motor_Init(void);
void Motor_SetRightSpeed(int8_t Speed);
void Motor_SetLeftSpeed(int8_t Speed);

int8_t Motor_GetLeftSpeed(void);

int8_t Motor_GetRightSpeed(void);


#endif
