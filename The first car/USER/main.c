#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "usart2.h" 
#include "usart3.h" 
#include "stdio.h" 
#include "stdlib.h"
#include "math.h"
#include "key.h"
#include "wheel.h"
#include "xunji.h"
#include "pid.h"

extern int  USART_PRINTF_FLAG;  

extern u8 rxbuf_usart3[10];
extern u8 rxbuf_usart2[10];
int dianji_sudu_zuo,dianji_sudu_you;
int dianji_zuo_duqu,dianji_you_duqu;
int pwm_dianji_zuo,pwm_dianji_you;
pid_t speed_pid_zuo,speed_pid_you;

//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	if(USART_PRINTF_FLAG==2)
//	{
//	 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){};//循环发送,直到发送完毕   
//   USART_SendData(USART2,(uint8_t)ch); 
//	}
//	if(USART_PRINTF_FLAG==1)
//	{
//	 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){};//循环发送,直到发送完毕   
//   USART_SendData(USART1,(uint8_t)ch); 
//	}
//	if(USART_PRINTF_FLAG==3)
//	{
//	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET){};//循环发送,直到发送完毕   
//   USART_SendData(USART3,(uint8_t)ch); 
//	}
//	return ch;
//}


 int main(void)
 {	
	 
	LED_Init();	
	delay_init();	
	My_USART1_Init();  	
	My_USART2_Init();
  My_USART3_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	  Encoder_Init();
	  TIM4_Int_Init(39999,71);
	  encoder_PWM_Init(499,71);
	  Encoder_Init_TIM2();
	  Encoder_Init_TIM3();
	 delay_ms(1000);
	 delay_ms(1000);
	 delay_ms(1000);
	 	 delay_ms(1000);
	 delay_ms(1000);
	 delay_ms(1000);
	 	 delay_ms(1000);
	 delay_ms(1000);
	 delay_ms(1000);	
	 delay_ms(1000);
	  pid_init(&speed_pid_zuo,250,150,1.4,0,0);
	  pid_init(&speed_pid_you,250,150,1.4,0,0);
	 
	while(1)
	{
//   youguai(190,60,500);
//		youguai(120,120,600);
//		  diaotou(120,750);
//		while(1)
//		{
//		 stop(5);
//		}

// 	  qianjin(150,150,50);
//    if(rxbuf_usart2[0]==0x31)
//		{
//			GPIO_SetBits(GPIOC,GPIO_Pin_15);
////		  xunji4();
//		}
		while(yaopin){stop(5);}
		
//		if(rxbuf_usart2[0]==0)
//		{
//			if(rxbuf_usart3[0]==1)
//				xunji1();
//			if(rxbuf_usart3[0]==2)
//				xunji2();
//			if(rxbuf_usart3[0]==3||rxbuf_usart3[0]==4||rxbuf_usart3[0]==5||rxbuf_usart3[0]==6||rxbuf_usart3[0]==7||rxbuf_usart3[0]==8)
//				xunji3();
//		}
		
//		
		
		
	}
		
}




void TIM4_IRQHandler(void)   //TIM3??
{	 		
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
	 TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	 dianji_zuo_duqu=Read_Encoder(3);
	 dianji_you_duqu=Read_Encoder(2);
	 pwm_dianji_zuo=pid_speed(&speed_pid_zuo,abs(dianji_zuo_duqu),dianji_sudu_zuo);
	 pwm_dianji_you=pid_speed(&speed_pid_you,abs(dianji_you_duqu),dianji_sudu_you);
	}
}










