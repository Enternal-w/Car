#ifndef _pid_h
#define _pid_h
#include "sys.h"

typedef struct PID
{
	float p;
	float i;
	float d;
	
	float set;
	float get;
	float err[2];
	
	float pout;
	float iout;
	float dout;
	
	float out;
	u16 max_output;
	u16 integral_limit;
}pid_t;


enum
{
	LAST=0,
	NOW=1,
};

void pid_init(pid_t *pid,u32 max_out,u32 integral_limit,float kp,float ki,float kd);
int pid_speed(pid_t *pid,int get,int set);





















#endif  




