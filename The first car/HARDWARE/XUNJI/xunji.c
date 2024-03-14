#include "xunji.h"
#include "sys.h"
#include "wheel.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "pid.h"
#include "led.h"
#include "usart3.h"

int  USART_PRINTF_FLAG=2;  
extern u8 rxbuf_usart3[10];
extern u8 rxbuf_usart1[10];
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
//	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
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
			zuo_q(128);
		  you_q(120);
			delay_us(5);
		}
		if(hongdian<0&&hongdian>=-1)
		{
			zuo_q(120);
		  you_q(128);
			delay_us(5);
		}
		if(hongdian>1&&hongdian<=4)
		{
			zuo_q(135);
		  you_q(120);
			delay_us(5);
		}
		if(hongdian<0&&hongdian>=-4)
		{
			zuo_q(120);
		  you_q(135);
			delay_us(5);
		}
		if(hongdian>4)
		{
			zuo_q(160);
		  you_q(120);
			delay_us(5);
		}
		if(hongdian<-4)
		{
			zuo_q(120);
		  you_q(160);
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
		if(rxbuf_usart1[2]==2&&tingzhi_flag==1)
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
				youguai(120,120,420);
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
				zuoguai(120,120,380);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
			if(rxbuf_usart3[1]==7)
			{
				zhuanwan_flag=3;
				zhuanwan[zhuanwan_flag]=2;
				qianjin(120,120,170);
				stop(1000);
				youguai(120,120,380);
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
			stop(500);
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			diaotou(120,740);
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
				youguai(120,120,420);
				stop(1000);
				rxbuf_usart1[2]=0;
				zhuanwan_flag=zhuanwan_flag-1;
			}
			if(zhuanwan[zhuanwan_flag]==2)
			{
			  qianjin(120,120,160);
				stop(1000);
				zuoguai(120,120,400);
				stop(1000);
				rxbuf_usart1[2]=0;
				zhuanwan_flag=zhuanwan_flag-1;
			}
			if(zhuanwan[zhuanwan_flag]==0)
					qianjin(120,120,350);
		}
		if(tingzhi_flag==1&&rxbuf_usart1[2]==2)
		{
			qianjin(120,120,170 );
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
				youguai(120,120,420);
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
				zuoguai(120,120,380);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
			if(rxbuf_usart3[1]==7)
			{
				zhuanwan_flag=3;
				zhuanwan[zhuanwan_flag]=2;
				qianjin(120,120,170);
				stop(1000);
				youguai(120,120,380);
				stop(1000);
				rxbuf_usart1[2]=0;
			}
		}
		if(rxbuf_usart1[2]==2)
		{
			qianjin(120,120,160);
			stop(500);
			GPIO_SetBits(GPIOC,GPIO_Pin_13);
			while(!yaopin){stop(5);}
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			stop(500);
			diaotou(120,740);
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
				youguai(120,120,420);
				stop(1000);
				rxbuf_usart1[2]=0;
				zhuanwan_flag=zhuanwan_flag-1;
			}
			if(zhuanwan[zhuanwan_flag]==2)
			{
			  qianjin(120,120,160);
				stop(1000);
				zuoguai(120,120,400);
				stop(1000);
				rxbuf_usart1[2]=0;
				zhuanwan_flag=zhuanwan_flag-1;
			}
			if(zhuanwan_flag==1)
				printf("%d",'1');
			if(zhuanwan[zhuanwan_flag]==0)
					qianjin(120,120,350);
		}
		if(tingzhi_flag==1&&rxbuf_usart1[2]==2)
		 {
			qianjin(120,120,170 );
		  while(1){stop(5);	GPIO_SetBits(GPIOC,GPIO_Pin_14);}
		
		}
		}
}





























