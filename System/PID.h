#ifndef __PID_H
#define __PID_H

#include <stdint.h>

enum {
	POSITION_PID,        //位置式
	DELTA_PID          //增量式
};

typedef struct
{
	float now_speed;
	float target;
	float p,i,d;
	float p_out,i_out,d_out;
	float i_limit;
	float out;
	float error[3];
	uint8_t mode;
	
}pid_t;



void pid_Init(pid_t *pid,uint8_t mode,float p,float i,float d, float i_limit);
void pid_cal(pid_t *pid);
extern pid_t speed_pid;
extern pid_t left_pid;
extern pid_t right_pid;

#endif
