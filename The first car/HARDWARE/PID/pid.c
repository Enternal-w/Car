#include "pid.h"

void pid_init(pid_t *pid,u32 max_out,u32 integral_limit,float kp,float ki,float kd)
{
	pid->integral_limit=integral_limit;
	pid->max_output=max_out;
	pid->p=kp;
	pid->i=ki;
	pid->d=kd;
}                                                                    //pid的初始化

static void abs_limit(float *a,float ABS_MAX)
{
	if(*a>ABS_MAX)*a=ABS_MAX;
	if(*a<-ABS_MAX)*a=-ABS_MAX;
}


//电机闭环
int pid_speed(pid_t *pid,int get,int set)
{
	pid->get=get;
	pid->set=set;
	pid->err[NOW]=set-get;
	
	pid->pout=pid->p*pid->err[NOW];
	pid->iout+=pid->i*pid->err[NOW];
	
	abs_limit(&(pid->iout),pid->integral_limit);
	pid->out=pid->pout+pid->iout;
	
	abs_limit(&(pid->out),pid->max_output);
	pid->err[LAST]=pid->err[NOW];
	return pid->out;
}










