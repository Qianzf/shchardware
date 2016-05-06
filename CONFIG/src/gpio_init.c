
/******************************************
*
*初始化GPIO口配置文件的头文件。
*
*******************************************/

#include "gpio_init.h"
#include "usart.h"
#include "stm32f4xx_gpio.h" 

GPIO_InitTypeDef GPIO_InitStructure;

//板载LED初始化
void LED_Init()
{
  //初始化时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  //初始化灯引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;                              
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //设置GPIO口速率
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
}

/*板载按键初始化
void Button_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//初始化按键
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置输出频率
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //不设置上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
}
*/
//串口初始化
//此处初始化的是usart6
//引脚用的是pc6->TX
//					pc7->RX
void USART6_Init()
{
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);  //开GPIOC的时钟
  //PC6->TX  PC7->Rx
  /* Configure USART6 Tx (PC.6) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//设置复用模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* Configure USART6 Rx (PC.7) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//设置复用模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);//设置引脚复用
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
}


//此处初始化的是usart2
//引脚用的是pa2->TX
//					pa3->RX
void USART2_Init()
{
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);  //开GPIOC的时钟
  //PA2->TX  PA3->Rx
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//设置复用模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);//设置引脚复用
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
}

//******************************************************************
//函数名：  LCD_GPIOInit
//功能：    液晶屏IO初始化，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_GPIOInit(void)
{

 	//初始化时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
  //初始化控制引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5;                              
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //设置GPIO口速率
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_11|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//初始化16位串行引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;                              
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_All);
	 
}
/*
**************************************************************************************************
*					!!!上方添加其它的初始化函数部分主体，这样可以不用修改头文件！！！                      *
**************************************************************************************************
*/

void Config_Init()
{
	//初始化LED
	LED_Init();
	//初始化串口引脚
	USART2_Init();
	USART6_Init();
	//初始化屏幕引脚
	LCD_GPIOInit();
	//配置uart
	USART_Config();
	
}
