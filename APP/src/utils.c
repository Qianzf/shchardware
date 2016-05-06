
//这是一个工具包函数，包括各种工具函数
#include "utils.h"
#include "stdio.h"
#include "stm32f4xx.h"

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"				 
#endif

#pragma import(__use_no_semihosting) 


/***********************************************************************
*       重定义printf&&scanf相关
***********************************************************************/ 
USART_TypeDef*  USARTX = USART6;
//省略微库的写法，来源：网易博客佚名
void _sys_exit(int x) 
{ 
	x = x; 
} 
struct __FILE 
{ 
int handle; 
}; 
FILE __stdout;

//重写下面两个函数
int fputc(int ch, FILE *f)
{

	USART_SendData(USARTX, (unsigned char) ch);// 设置为USART6这个可以按需求改

	while (!(USARTX->SR & USART_FLAG_TXE));

	return (ch);

}

int GetKey (void) 
{

	while (!(USARTX->SR & USART_FLAG_RXNE));

	return ((int)(USARTX->DR & 0x1FF));

}

//重写发送代码部分，以适应不同的串口发送
void sendString(USART_TypeDef*  USART,const char * str)
	{
		USARTX = USART;
		printf(str);
	}


/****************************************************
**		此部分代码来源网络，因为自己写半天也没搞定。。。
**		主要作用是设置延时
**		感谢正点原子的代码。。。。
*****************************************************/
 
static u8  fac_us=0;		   
static u16 fac_ms=0;

#ifdef OS_CRITICAL_METHOD 	

void SysTick_Handler(void)
{				   
		OSIntEnter();		
    OSTimeTick();                
    OSIntExit();        
}
#endif
			   

void delay_init(u8 SYSCLK)
{
#ifdef OS_CRITICAL_METHOD 	
	u32 reload;
#endif
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SYSCLK/8;		
	    
#ifdef OS_CRITICAL_METHOD 	
	reload=SYSCLK/8;		 
	reload*=1000000/OS_TICKS_PER_SEC;
						
	fac_ms=1000/OS_TICKS_PER_SEC; 
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	
	SysTick->LOAD=reload; 	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   
#else
	fac_ms=(u16)fac_us*1000;
#endif
}								    

#ifdef OS_CRITICAL_METHOD 	
	    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	  	 
	ticks=nus*fac_us; 			
	tcnt=0;
	OSSchedLock();				
	told=SysTick->VAL;       
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;
		}  
	};
	OSSchedUnlock();								    
}

void delay_ms(u16 nms)
{	
		if(OSRunning==OS_TRUE&&OSLockNesting==0)
	{		  
		if(nms>=fac_ms)
		{
   			OSTimeDly(nms/fac_ms);	
		}
		nms%=fac_ms;				
	}
	delay_us((u32)(nms*1000));	
}
#else  

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;  		 
	SysTick->VAL=0x00;        
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;       
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));  
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;    
	SysTick->VAL =0X00;      
}

void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;         
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));  
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;      
	SysTick->VAL =0X00;      	    
} 

//nms:0~65535
void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;	
						
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
	
} 
#endif
			 

/*****************************************************************
*
*									字符串处理函数部分
*
*****************************************************************/

int getmid(char *str, char a, char b,char *out)
/* 
* str为输入的字符串，a为起点，b为终点，out为输出的中间字符串
* 如果参数正确，返回0，否则返回-1
*/
{
	u8 temp = 0;
   while(*str!='\0')
	 {
			if(*str == a)
			{
				temp = 1;
			}
			str++;
			if(*str == b)
			{
				temp = 0;
			}
			if(temp == 1)
			{
				*out = *str;
				out++;
			}

	 }
	 
		*out='\0';

	 return 0;
}





int getcontent(char *str, char* a, char* b,char *out)
/* 
* str为输入的字符串，a为起点，b为终点，out为输出的中间字符串
* 如果参数正确，返回0，否则返回-1
*/
{
	u8 temp = 0;
	u8 status = 0;

   while(*str!='\0')
	 {
		 if(status==0)
		 {
				 if(*str == *a)
				 {
					 temp++;
					 a++;
					 if(*a=='\0')
					 {
						//匹配成功
						 status = 1;
						 temp = 0;
					 }
				 }else if(temp!=0)
				 {
					 //匹配错误，回滚
					while(temp)
					{
						a--;
						temp--;
					}
				 }
			}
		 
		 str++;
		 
			if(status==1)
			{
				if(*str == *b)
			 {
				 temp++;
				 b++;
				 if(*b=='\0')
				 {
					//匹配成功
					 status = 2;
					 break;
				 }
			 }else if(temp!=0)
			 {
				 //匹配错误，回滚
				while(temp)
				{
					b--;
					temp--;
				}	
			}
		 
			if(status==1)
			{
				*out = *str;
				out++;
			}

		}
			
	}
	 *out='\0';
	 return 0;

}










