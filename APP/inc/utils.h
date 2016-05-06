#ifndef __UTILS_H
#define __UTILS_H

//设置usart接收缓存的大小
#define USART_REC_LEN 10240
		   
#include <sys.h>	  

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

int getindex(char *str,char c);
int getmid(char *str, char a, char b,char *out);
int getcontent(char *str, char* a, char* b,char *out);



#include "stm32f4xx.h"

void sendString(USART_TypeDef*  USART,const char * str);

#endif











