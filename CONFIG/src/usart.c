# include "usart.h"
# include "stm32f4xx_usart.h"

/******************************
**         USART初始化
*******************************/
void USART_Config()
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能USART2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//使能USART6时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
	
	//设置USART6串口传输相关参数 
	USART_InitStructure.USART_BaudRate = 115200;//波特率：115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;//不设置校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//初始化USART6，并使其使能  
	USART_Init(USART6,&USART_InitStructure); 
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);//设置中断！！！！！！！！！！！！
	//USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);
	USART_Cmd(USART6,ENABLE);
	//初始化USART中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2,2:2
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//设置中断源USART6
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	 //中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级0
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	//设置USART2串口传输相关参数 
	USART_InitStructure.USART_BaudRate = 115200;//波特率：115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;//不设置校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	//初始化USART2，并使其使能  
	USART_Init(USART2,&USART_InitStructure); 
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//设置中断！！！！！！！！！！！！
	//USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);
	USART_Cmd(USART2,ENABLE);
	//初始化USART中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2,2:2
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//设置中断源USART2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	 //中断使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//响应优先级0
	NVIC_Init(&NVIC_InitStructure);
	
}





















