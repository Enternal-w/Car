#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define yaopin  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//读取按键0



void KEY_Init(void);//IO初始化			    
#endif
