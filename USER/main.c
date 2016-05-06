
////////////////////////////////////////////////////////
//*                                                   //
//*																										//
//*					����Stm32F407�ı�ҵ���										//
//*																										//
//*					@��ҵ�����Ŀ�����ܰ칫��ʾ��							//
//*																										//
//*					@����ϵͳ��uCOSII													//
//*																										//
//*					@��ʼʱ�䣺2016��3��24��17:07:40					//
//*																										//
//*					@���ߣ�Ǯ�зɣ�Qianzf��										//
//*																										//
//*																										//
////////////////////////////////////////////////////////


//����ʹ�õĿ�����ΪDiscovery������
#define __BOARD_DISCOVERY_

#include "includes.h"
#include "ttl_display.h"
//Ҫִ�еĳ�ʼ������
#include "gpio_init.h"
#include "WiFiInit.h"
//Ҫִ�еĹ��ܺ���ͷ�ļ�
#include "utils.h"

#include "WiFiListener.h"
#include "LED_Effect.h"
#include "display.h"
#include "lcd.h"
#include "gui.h"

#define START_STK_SIZE  128
//�������������ջ
OS_STK START_TASK_STK[START_STK_SIZE];

#define WiFiListenerTask_STK_SIZE  128
//�������߼��������ջ
OS_STK WiFiListenerTask_TASK_STK[WiFiListenerTask_STK_SIZE];

//��������
void StartTask(void*pdata);
//����1
void WiFiListenerTask(void*pdata);


u8 dis_status = 0;
/********************************************************************
**									��������������ڣ�
******************************************************************/

int main(void){
	
	//����ϵͳʱ��
	SysTick_Config(SystemCoreClock / 1000);
	
	//��ʼ����ʱ��������ʱ�������ִ�����������ԭ�ӵĽ̳�
	delay_init(168);					
	//��ʼ������ϵͳ
	OSInit (); 
	//������������
	OSTaskCreate(
							StartTask,//������
							(void *)0,//���������������������������
							&START_TASK_STK[START_STK_SIZE-1],//���������ջ
							1//�������ȼ����ܹ���64�����ȼ�(��ͬ����Ҫͬʱִ����Ҫ�������ȼ���ͬ)
							);
	
	//��������ϵͳ����ʼ��������е��ȹ���
	OSStart (); 
}

/*****************************************************************
**			��������Ҫ�������ϵͳ��ʼ������������������
******************************************************************/
void StartTask(void* pdata){
	
	pdata = pdata;
	
	//��ʼ������
	Config_Init();
	//Һ������ʼ��
	LCD_Init();	   
	//��ʾ��ӭҳ��
	display_welcome();
	//�������ϵͳ��ӭ��Ϣ
	startinfo();
	//��ʼ��wifi����������
	WiFiStartConnection();
	//����һ���������񣬼�����ESPоƬ�н��յ���������Ϣ
	sendString(USART6,"System is creating WiFiListener...\n\r");
	
	while(1)
	{
			if(dis_status==1)
			{
				word_tips(260,"���ڴ����������߼�����...",GRAY);
				delay_ms(500);
				OSTaskCreate(WiFiListenerTask,(void *)0,&WiFiListenerTask_TASK_STK[WiFiListenerTask_STK_SIZE-1],2);	
					
				sendString(USART6,"System is creating task2...\n\r");	
				
				sendString(USART6,"Enjoy it now!\n\r");
				display_now();	
				
				OSTaskDel (OS_PRIO_SELF); //������ɺ�ɾ���Լ�
			}
	}
}

/*****************************************************************
**									��������Ҫ��������wifi��Ϣ
******************************************************************/
void WiFiListenerTask(void*pdata){
	pdata = pdata;
	while(1)
	{
		//��ʼ����WiFi�˿�����
		WiFiListener();
		LED_Circle();
	}
}



























