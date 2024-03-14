#include "usart3.h"
#include "delay.h"



void My_USART3_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStrue;  
    USART_InitTypeDef USART_InitStrue;  
    NVIC_InitTypeDef NVIC_InitStrue;  
      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//GPIO????  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//??????  
	
	
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB,&GPIO_InitStrue);  
      
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_11;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB,&GPIO_InitStrue);  

    USART_InitStrue.USART_BaudRate=9600;  
    USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
    USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  
    USART_InitStrue.USART_Parity=USART_Parity_No;  
    USART_InitStrue.USART_StopBits=USART_StopBits_1;  
    USART_InitStrue.USART_WordLength=USART_WordLength_8b;    
    USART_Init(USART3,&USART_InitStrue);
		
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//??????  
    USART_Cmd(USART3,ENABLE);//????1  
				 
				 
    NVIC_InitStrue.NVIC_IRQChannel=USART3_IRQn;  
    NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;  
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;  
    NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;  
    NVIC_Init(&NVIC_InitStrue);  
      
}  

u8 num_usart3=0;
u8 start_usart3;
u8 packerflag_usart3;
u8 rxbuf_usart3[10]={0,0};

void USART3_IRQHandler(void)  
{
  u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res = USART_ReceiveData(USART3);	//读取接收到的数据
		if(Res == 0xaa)
		{
			start_usart3 = 1;
			num_usart3 = 0;
			packerflag_usart3 = 0;
			return ;
		}
		if(start_usart3 == 1) //是否处于接收数据包状态
		{
			rxbuf_usart3[num_usart3 ++] = Res; 
		}
		if(Res == 0xbb) //检测是否是包尾
		{
			start_usart3 = 0;
			packerflag_usart3 = 1;//用于告知系统已经接收到一个完整的数据包
			return ;
		}
	}
}


