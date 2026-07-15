#include "stm32f10x.h"
#include "PID.h"

pid_t speed_pid;
pid_t left_pid;
pid_t right_pid;


void pid_Init(pid_t *pid,uint8_t mode,float p,float i,float d, float i_limit)
{
	pid->mode = mode;
    pid->p = p;
	pid->i = i;
	pid->d = d;
	pid->i_limit = i_limit;

	pid->now_speed = 0.0f;
	pid->target = 0.0f;
	pid->p_out = 0.0f;
	pid->i_out = 0.0f;
	pid->d_out = 0.0f;
	pid->out = 0.0f;
	pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
}

void pid_cal(pid_t *pid)
{
	pid->error[0] = pid->target - pid->now_speed;        //计算误差
	
	if (pid-> mode == POSITION_PID)                                  //位置式
	{
		pid->p_out = pid->p * pid->error[0];
		pid->i_out += pid->i * pid->error[0];
		// 积分限幅
		if (pid->i_out > pid->i_limit) pid->i_out = pid->i_limit;
		if (pid->i_out < -pid->i_limit) pid->i_out = -pid->i_limit;
		pid->d_out = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->p_out + pid->i_out + pid->d_out;
	}
	
	else if(pid->mode == DELTA_PID)                               // 增量式
	{
		pid->p_out = pid->p * (pid->error[0] - pid->error[1]);
		pid->i_out = pid->i * pid->error[0];
		// 对增量式也限制单步积分贡献，避免突变
		if (pid->i_out > pid->i_limit) pid->i_out = pid->i_limit;
		if (pid->i_out < -pid->i_limit) pid->i_out = -pid->i_limit;
		pid->d_out = pid->d * (pid->error[0] - 2*pid->error[1] + pid->error[2]);
		
		pid->out += pid->p_out + pid->i_out + pid->d_out;
	}
	
	pid->error[1] = pid->error[0];
	pid->error[2] = pid->error[1];
}




