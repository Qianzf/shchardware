
//写一些板载的灯光效果
#include "LED_Effect.h"
#include "gpio_init.h"
#include "utils.h"
#include "stm32f4xx_gpio.h"



int led_num = 4;
int i = 0;

uint16_t led[4]={LED_Green,LED_Yellow,LED_Orange,LED_Blue};

void LED_OFF(){		
	for(i=0;i<led_num;++i)
	{
		GPIO_ResetBits(LED,led[i]);
	}
}
void LED_ON(){
	
		for(i=0;i<led_num;++i)
		{
			GPIO_SetBits(LED,led[i]);
		}
}

void LED_Blink(){
		
		LED_ON();
		delay_ms(1000);
		LED_OFF();
		delay_ms(1000);
}

void LED_Circle(){
		
		for(i=0;i<led_num*2;++i)
		{
			if(i<led_num)
			{
				GPIO_SetBits(LED,led[i]);
			}else
			{
				GPIO_ResetBits(LED,led[i-led_num]);
			}
			delay_ms(120);
		}
			
}



















