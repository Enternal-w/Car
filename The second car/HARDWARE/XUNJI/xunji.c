#include "xunji.h"
#include "sys.h"
#include "wheel.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "pid.h"
#include "led.h"
#include "usart3.h"
#include "usart2.h"

int  USART_PRINTF_FLAG=2;  
extern u8 rxbuf_usart2[10];       //蓝牙
extern u8 rxbuf_usart3[10];       //物块
extern u8 rxbuf_usart1[10];       //循迹
int shizi=0;
int zhuanwan_flag=0,tingzhi_flag=0;
int hongdian;
int diaotou_flag=0;
int zhuanwan[4]={0,0,0,0};

struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	if(USART_PRINTF_FLAG==2)
	{
	 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){};//循环发送,直到发送完毕   
   USART_SendData(USART2,(uint8_t)ch); 
	}
	if(USART_PRINTF_FLAG==1)
	{
	 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){};//循环发送,直到发送完毕   
   USART_SendData(USART1,(uint8_t)ch); 
	}
	if(USART_PRINTF_FLAG==3)
	{
	 while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET){};//循环发送,直到发送完毕   
   USART_SendData(USART3,(uint8_t)ch); 
	}
	return ch;
}


void zuoguai(int sudu_zuo,int sudu_you,int shijian)
{
   zuo_h(sudu_zuo);
	 you_q(sudu_you);
	 delay_ms(shijian);
}                                             //左拐

void qianjin(int sudu_zuo,int sudu_you,int shijian)
{
   zuo_q(sudu_zuo);
	 you_q(sudu_you);
	 delay_ms(shijian);
}         
void stop(int time)
{
	zuo_q(0);
	you_q(0);
	delay_ms(time);


}


void youguai(int sudu_zuo,int sudu_you,int shijian)
{
   zuo_q(sudu_zuo);
	 you_h(sudu_you);
	 delay_ms(shijian);
}                                                 //右拐

void diaotou(int sudu,int shijian)
{
   zuo_h(sudu);
	 you_q(sudu);
	 delay_ms(shijian);
}                                             //掉头


void xunji(void)
{
   	zuo_q(120);
		you_q(120);
		hongdian=rxbuf_usart1[0]-25;
		if(hongdian>0&&hongdian<=1)
		{
			zuo_q(125);
		  you_q(120);
			delay_us(5);
		}
		if(hongdian<0&&hongdian>=-1)
		{
			zuo_q(120);
		  you_q(125);
			delay_us(5);
		}
		if(hongdian>1&&hongdian<=4)
		{
			zuo_q(130);
		  you_q(120);
			delay_us(5);
		}
		if(hongdian<0&&hongdian>=-4)
		{
			zuo_q(120);
		  you_q(130);
			delay_us(5);
		}
		if(hongdian>4)
		{
			zuo_q(155);
		  you_q(120);
			delay_us(5);
		}
		if(hongdian<-4)
		{
			zuo_q(120);
		  you_q(155);
			delay_us(5);
		}
}


void xunji1(void)
{
	while(1)
	{
		if(rxbuf_usart1[2]==0)
  	xunji();
		if(rxbuf_usart1[2]==1&&diaotou_flag==0)
		{
		  qianjin(120,120,170);
			stop(1000);
			zuoguai(120,120,420);
			stop(1000);
			rxbuf_usart1[2]=0;
		}
		if(rxbuf_usart1[2]==2&&tingzhi_flag==0)
		{
			qianjin(120,120,170);
			stop(500);	
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			while(!yaopin){stop(5);}
			stop(500);
	  	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		  diaotou(120,740);
			diaotou_flag=1;
			tingzhi_flag=1;
			rxbuf_usart1[2]=0;
			stop(1000);
		}
		if(rxbuf_usart1[2]==1&&diaotou_flag==1)
		{
	    qianjin(120,120,150);
			stop(800);
			youguai(120,120,410);
			stop(1000);
			rxbuf_usart1[2]=0;
		}
		if(tingzhi_flag==1&&rxbuf_usart1[2]==2)
		{
			qianjin(120,120,170 );
		  while(1){stop(5);GPIO_SetBits(GPIOC,GPIO_Pin_14);}
			
		}
	}
}


void xunji2(void)
{
	while(1)
	{
		if(rxbuf_usart1[2]==0)
  	xunji();
		if(rxbuf_usart1[2]==1&&diaotou_flag==0)
		{
		  qianjin(120,120,170);
			stop(1000);
			youguai(120,120,420);
			stop(1000);
			rxbuf_usart1[2]=0;
		}
		if(rxbuf_usart1[2]==2&&tingzhi_flag==0)
		{
			qianjin(120,120,170);
			stop(500);
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			while(!yaopin){stop(5);}
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			stop(500);
		  diaotou(120,740);
			diaotou_flag=1;
			tingzhi_flag=1;
			rxbuf_usart1[2]=0;
			stop(1000);
		}
		if(rxbuf_usart1[2]==1&&diaotou_flag==1)
		{
	    qianjin(120,120,150);
			stop(800);
			zuoguai(120,120,410);
			stop(1000);
			rxbuf_usart1[2]=0;
		}
		if(tingzhi_flag==1&&rxbuf_usart1[2]==2)
		{
			qianjin(120,120,170);
		  while(1){stop(5);GPIO_SetBits(GPIOC,GPIO_Pin_14);}
			
		}

		
	}
}


void xunji3(void)
{
	while(1)
	{
		if(rxbuf_usart1[2]==0)
			xunji();
		if(rxbuf_usart1[2]==1&&zhuanwan_flag==0&&diaotou_flag==0)
		{
			qianjin(120,120,350);
			zhuanwan_flag=1;
			zhuanwan[zhuanwan_flag]=0;
			rxbuf_usart1[2]=0;
			rxbuf_usart3[1]=0;
		}
		if(rxbuf_usart1[2]==1&&zhuanwan_flag==1&&diaotou_flag==0)
		{
			if(rxbuf_usart3[1]==6)
			{
				zhuanwan_flag=2;
				zhuanwan[zhuanwan_flag]=1;
				qianjin(120,120,160);
				stop(1000);
				zuoguai(120,120,420);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
			if(rxbuf_usart3[1]==7)
			{
				zhuanwan_flag=2;
				zhuanwan[zhuanwan_flag]=2;
				qianjin(120,120,160);
				stop(1000);
				youguai(120,120,390);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
		}
		if(rxbuf_usart1[2]==1&&zhuanwan_flag==2&&diaotou_flag==0)
		{
			
			if(rxbuf_usart3[1]==6)
			{
				zhuanwan_flag=3;
				zhuanwan[zhuanwan_flag]=1;
				qianjin(120,120,170);
				stop(1000);
				zuoguai(120,120,390);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
			if(rxbuf_usart3[1]==7)
			{
				zhuanwan_flag=3;
				zhuanwan[zhuanwan_flag]=2;
				qianjin(120,120,170);
				stop(1000);
				youguai(120,120,390);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
		}
		if(rxbuf_usart1[2]==2&&tingzhi_flag==0)
		{
			qianjin(120,120,160);
			stop(500);
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			while(!yaopin){stop(5);}
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			stop(500);
			diaotou(120,650);
			diaotou_flag=1;
			tingzhi_flag=1;
			rxbuf_usart1[2]=0;
			stop(2000);
		}
		if(rxbuf_usart1[2]==1&&diaotou_flag==1&&zhuanwan_flag>=0)
		{
		  if(zhuanwan[zhuanwan_flag]==1)
			{
			  qianjin(120,120,160);
				stop(1000);
				youguai(120,120,390);
				stop(1000);
				rxbuf_usart1[2]=0;
				zhuanwan_flag=zhuanwan_flag-1;
			}
			if(zhuanwan[zhuanwan_flag]==2)
			{
			  qianjin(120,120,160);
				stop(1000);
				zuoguai(120,120,390);
				stop(1000);
				rxbuf_usart1[2]=0;
				zhuanwan_flag=zhuanwan_flag-1;
			}
			if(zhuanwan[zhuanwan_flag]==0)
					qianjin(120,120,350);
		}
		if(rxbuf_usart1[2]==2&&tingzhi_flag==1)
		{
			qianjin(120,120,160 );
		  while(1){stop(5);GPIO_SetBits(GPIOC,GPIO_Pin_14);}
			
		}
		}
}



void xunji4(void)
{
	while(1)
	{
		if(rxbuf_usart1[2]==0)
			xunji();
		if(rxbuf_usart1[2]==1&&diaotou_flag==0)
		{
			qianjin(120,120,160);
			stop(1000);
			youguai(120,120,390);
			stop(1000);
		
			GPIO_ResetBits(GPIOC,GPIO_Pin_15);
			zhuanwan_flag=1;
			zhuanwan[zhuanwan_flag]=0;
			rxbuf_usart1[2]=0;
			rxbuf_usart3[1]=0;
		}
		if(rxbuf_usart1[2]==2)
		{
			qianjin(120,120,140);
			stop(500);
			stop(500);
			diaotou(120,650);
			GPIO_SetBits(GPIOC,GPIO_Pin_15);
			zuo_q(0);
	   you_q(0);
			delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);
				delay_ms(1500);

			GPIO_ResetBits(GPIOC,GPIO_Pin_15);
			diaotou_flag=1;
			rxbuf_usart1[2]=0;
		}
		if(rxbuf_usart1[2]==1&&diaotou_flag==1)
		{
			diaotou_flag=0;
		  qianjin(120,120,160);
			stop(1000);
			youguai(120,120,390);
			stop(1000);
			while(1)
			{
			  xunji3();
			}
		}
	}
}































