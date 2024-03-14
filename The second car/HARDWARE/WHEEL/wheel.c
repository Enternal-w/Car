#include "wheel.h"
#include "sys.h"

extern int dianji_sudu_zuo,dianji_sudu_you;
extern int pwm_dianji_zuo,pwm_dianji_you;

void you_h(int sudu)
{
	dianji_sudu_you=sudu;
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	TIM_SetCompare1(TIM1,sudu*1.4+pwm_dianji_you);		
}


void you_q(int sudu)
{
	dianji_sudu_you=sudu;
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	TIM_SetCompare1(TIM1,sudu*1.4+pwm_dianji_you);		
}


void zuo_q(int sudu)
{
	  dianji_sudu_zuo=sudu;
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		TIM_SetCompare3(TIM1,sudu*1.4+pwm_dianji_zuo);			
}


void zuo_h(int sudu)
{
	  dianji_sudu_zuo=sudu;
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		TIM_SetCompare3(TIM1,sudu*1.4+pwm_dianji_zuo);			
}




