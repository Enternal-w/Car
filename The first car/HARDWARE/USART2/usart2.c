#include "usart2.h"
#include "sys.h"
#include "stdio.h"


void My_USART2_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStrue;  
    USART_InitTypeDef USART_InitStrue;  
    NVIC_InitTypeDef NVIC_InitStrue;  
      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//GPIO????  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//??????  
	
	
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;   
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStrue);  
      
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;  
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;  
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA,&GPIO_InitStrue);  

    USART_InitStrue.USART_BaudRate=9600;  
    USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
    USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  
    USART_InitStrue.USART_Parity=USART_Parity_No;  
    USART_InitStrue.USART_StopBits=USART_StopBits_1;  
    USART_InitStrue.USART_WordLength=USART_WordLength_8b;    
    USART_Init(USART2,&USART_InitStrue);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//??????  
		
		
		USART_ClearFlag(USART2,USART_FLAG_TC);	
    USART_Cmd(USART2,ENABLE);//????1  
				 
				 
    NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;  
    NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;  
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;  
    NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;  
    NVIC_Init(&NVIC_InitStrue);  
      
}  
		 
		 
u8 rxbuf_usart2[10]={0}; 
		
void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
		rxbuf_usart2[0] = USART_ReceiveData(USART2);	//读取接收到的数据
    if(rxbuf_usart2[0]==0x31)
			GPIO_SetBits(GPIOC,GPIO_Pin_15);

		return;
	}
}
		 
		 



