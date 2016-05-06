
#include "WiFiInit.h"
#include "includes.h"
#include "utils.h"
#include "gpio_init.h"
#include "LED_Effect.h"
#include "gui.h"
#include "display.h"
#include "lcd.h"

extern u16 USART2_RX_STA ; 
extern u8 status;
extern u8 dis_status;
void WiFiStartConnection()
{
	u8 temp = 0;
	u8 temp2 = 1;
	while(temp2)
	{
		switch(temp)
		{
			case 0:
				if(WiFiCmd("AT+GMR\r\n")) 
				{
					temp++;
					LED_Green_On;
					word_tips(260,"WiFi init(Step1/Step5)...",GRAY);

				}
				else temp = 99;
			break;
			
			case 1:
				if(WiFiCmd("AT+CWMODE=2\r\n")) 
				{
					temp++;
					LED_Yellow_On;
					word_tips(260,"WiFi init(Step2/Step5)...",GRAY);

				}
				else temp = 99;
			break;
			
			case 2:
				if(WiFiCmd("AT+CIFSR\r\n")) 
				{
					temp++;
					LED_Orange_On;
					word_tips(260,"WiFi init(Step3/Step5)...",GRAY);

				}
				else temp = 99;
			break;
			
			case 3:
				WiFiCmd("AT+CIPMUX=1\r\n");
				{
					temp++;
					LED_Blue_On;
					word_tips(260,"WiFi init(Step4/Step5)...",GRAY);

				}
				
			break;
			
			case 4:
				if(WiFiCmd("AT+CIPSERVER=1,4848\r\n")) 
				{
					temp++;
					LED_Green_Off;
					word_tips(260,"WiFi init(Step5/Step5)...",GRAY);

				}
				else temp = 99;
			break;
			
			case 5:
				if(WiFiCmd("AT+CIPSTATUS\r\n")) 
				{
					temp2 = 0;
					word_tips(260,"WiFi init  Finished...",GRAY);
					delay_ms(200);
					dis_status = 1;
					sendString(DEBUG,"\r\n-----------WiFiInitFinished!!!!!!----------\r\n");
				}
				else temp = 99;
			break;
			
			case 99:
				word_tips(260,"WiFi init failed ,Please check your wifi device!",GRAY);
				sendString(DEBUG,"\r\n-----------WiFiInitFailed!!!!!!----------\r\n");
				temp2 = 0;
				break;
		}
	}
}

//无线控制命令执行函数，执行成功返回1，失败回0，失败后会自动重复三次执行
u8 WiFiCmd(char *cmd)
{
		u8 time = 3;
		sendString(WIFIC,cmd);
		delay_ms(1000);
		while(--time&&status!=200)
		{
			sendString(WIFIC,cmd);
			delay_ms(20);
			if(status==200) break;
		}
		status = 0;
		USART2_RX_STA = 0; 
		
		if(time == 0)
			return 0;
		else
			return 1;

}


























