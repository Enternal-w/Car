#include "sys.h"
#include "usart.h"	  



void My_USART1_Init(void)  
{
	USART_InitTypeDef USART_InitSturct;
 
	GPIO_InitTypeDef GPIO_InitStruct;
 
  NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOB , ENABLE);//????????
  GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;//????
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//??????
	GPIO_Init(GPIOB , &GPIO_InitStruct);//??????????????
 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;//????
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO??????
  GPIO_Init(GPIOB, &GPIO_InitStruct);//??????????????
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	USART_InitSturct.USART_BaudRate = 9600;//???19200
	USART_InitSturct.USART_WordLength = USART_WordLength_8b;//????8?
	USART_InitSturct.USART_StopBits = USART_StopBits_1;//?????
	USART_InitSturct.USART_Parity = USART_Parity_No;//?????
	USART_InitSturct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitSturct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//??????
	
	USART_Init(USART1 , &USART_InitSturct);//??????????????	
	USART_ITConfig(USART1 , USART_IT_RXNE , ENABLE);//??????
	USART_Cmd(USART1 , ENABLE);//????

	USART_ClearFlag(USART1 , USART_FLAG_TC);//??????????????
}

u8 num_usart1=0;
u8 start_usart1;
u8 packerflag_usart1;
u8 rxbuf_usart1[10]={27};



void USART1_IRQHandler(void)  
{
  u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res = USART_ReceiveData(USART1);	//读取接收到的数据
		if(Res == 0xaa)
		{
			start_usart1 = 1;
			num_usart1 = 0;
			packerflag_usart1 = 0;
			return ;
		}
		if(start_usart1 == 1) //是否处于接收数据包状态
		{
			rxbuf_usart1[num_usart1 ++] = Res; 
		}
		if(Res == 0xbb) //检测是否是包尾
		{
			start_usart1 = 0;
			packerflag_usart1 = 1;//用于告知系统已经接收到一个完整的数据包
			return ;
		}
	}
}
















