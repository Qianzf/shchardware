/*****************************************************************
*
*						该函数用来监听ESP芯片的 USART输出信息
*
******************************************************************/
#include "WiFiListener.h"
#include "stm32f4xx.h"
#include "utils.h"
#include "gpio_init.h"
#include "display.h"

extern u16 USART6_RX_STA;
extern u8  USART6_RX_BUF[USART_REC_LEN];
extern u8 status;
extern u16 USART2_RX_STA;
extern u8  USART2_RX_BUF[USART_REC_LEN];
u16 len;
u16 t;
u8 n = 0;
char temp[10240];
char temp1[10240];


void WiFiListener()
	{
					
			//接收状态位，正常返回200，不正常返回201，数据溢出返回202
			if(status == 200)
			{
				sendString(DEBUG," \r\n++++++Mission Success!++++++\r\n");
				USART2_RX_STA=0;
				status = 0;
			}
			if(status == 201)
			{
				sendString(DEBUG," \r\n++++++Mission Failed!++++++\r\n");
				USART2_RX_STA=0;
				status = 0;
			}
			
			if(status == 202)
			{
				sendString(DEBUG," \r\n++++++DATA OVERFLOW!+++++++\r\n");
				
			}
			
			if(status == 203)
			{
				getcontent((char*)USART2_RX_BUF, "title:", "^",temp);
				display_title(temp);
				getcontent((char*)USART2_RX_BUF, "info:", "^",temp1);
				display_info(temp1);
				USART2_RX_STA=0;
				status = 0;
			}
}



