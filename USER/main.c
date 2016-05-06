
////////////////////////////////////////////////////////
//*                                                   //
//*																										//
//*					基于Stm32F407的毕业设计										//
//*																										//
//*					@毕业设计题目：智能办公提示牌							//
//*																										//
//*					@操作系统：uCOSII													//
//*																										//
//*					@开始时间：2016年3月24日17:07:40					//
//*																										//
//*					@作者：钱中飞（Qianzf）										//
//*																										//
//*																										//
////////////////////////////////////////////////////////


//设置使用的开发板为Discovery开发板
#define __BOARD_DISCOVERY_

#include "includes.h"
#include "ttl_display.h"
//要执行的初始化操作
#include "gpio_init.h"
#include "WiFiInit.h"
//要执行的功能函数头文件
#include "utils.h"

#include "WiFiListener.h"
#include "LED_Effect.h"
#include "display.h"
#include "lcd.h"
#include "gui.h"

#define START_STK_SIZE  128
//设置启动任务堆栈
OS_STK START_TASK_STK[START_STK_SIZE];

#define WiFiListenerTask_STK_SIZE  128
//设置无线监听任务堆栈
OS_STK WiFiListenerTask_TASK_STK[WiFiListenerTask_STK_SIZE];

//启动任务
void StartTask(void*pdata);
//任务1
void WiFiListenerTask(void*pdata);


u8 dis_status = 0;
/********************************************************************
**									主函数，程序入口！
******************************************************************/

int main(void){
	
	//设置系统时钟
	SysTick_Config(SystemCoreClock / 1000);
	
	//初始化延时函数，延时函数部分代码来自正点原子的教程
	delay_init(168);					
	//初始化操作系统
	OSInit (); 
	//创建启动任务
	OSTaskCreate(
							StartTask,//任务名
							(void *)0,//任务参数表，即创建任务的输入参数
							&START_TASK_STK[START_STK_SIZE-1],//创建任务堆栈
							1//设置优先级，总共有64个优先级(不同任务要同时执行需要保持优先级不同)
							);
	
	//启动操作系统，开始对任务进行调度管理
	OSStart (); 
}

/*****************************************************************
**			该任务主要用来完成系统初始化，并启动其它任务
******************************************************************/
void StartTask(void* pdata){
	
	pdata = pdata;
	
	//初始化配置
	Config_Init();
	//液晶屏初始化
	LCD_Init();	   
	//显示欢迎页面
	display_welcome();
	//串口输出系统欢迎信息
	startinfo();
	//初始化wifi服务器设置
	WiFiStartConnection();
	//创建一个监听任务，监听从ESP芯片中接收到的数据信息
	sendString(USART6,"System is creating WiFiListener...\n\r");
	
	while(1)
	{
			if(dis_status==1)
			{
				word_tips(260,"正在创建任务无线监听器...",GRAY);
				delay_ms(500);
				OSTaskCreate(WiFiListenerTask,(void *)0,&WiFiListenerTask_TASK_STK[WiFiListenerTask_STK_SIZE-1],2);	
					
				sendString(USART6,"System is creating task2...\n\r");	
				
				sendString(USART6,"Enjoy it now!\n\r");
				display_now();	
				
				OSTaskDel (OS_PRIO_SELF); //任务完成后删除自己
			}
	}
}

/*****************************************************************
**									该任务主要用来监听wifi信息
******************************************************************/
void WiFiListenerTask(void*pdata){
	pdata = pdata;
	while(1)
	{
		//开始监听WiFi端口输入
		WiFiListener();
		LED_Circle();
	}
}



























