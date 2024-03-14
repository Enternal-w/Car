#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
void encoder_PWM_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM3(void);
int Read_Encoder(u8 TIMX);
void Encoder_Init(void);
#endif















