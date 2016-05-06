/**
*
*初始化GPIO口配置文件的头文件。
*
*/

#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H

#define DEBUG USART6
#define WIFIC USART2

#define LED GPIOD
#define LED_Yellow GPIO_Pin_13
#define LED_Orange GPIO_Pin_14
#define LED_Blue   GPIO_Pin_15
#define LED_Green  GPIO_Pin_12

#define LED_Blue_Off    GPIO_ResetBits(LED,LED_Blue)
#define LED_Yellow_Off  GPIO_ResetBits(LED,LED_Yellow)
#define LED_Green_Off   GPIO_ResetBits(LED,LED_Green)
#define LED_Orange_Off  GPIO_ResetBits(LED,LED_Orange)

#define LED_Blue_On    GPIO_SetBits(LED,LED_Blue)
#define LED_Yellow_On  GPIO_SetBits(LED,LED_Yellow)
#define LED_Green_On   GPIO_SetBits(LED,LED_Green)
#define LED_Orange_On  GPIO_SetBits(LED,LED_Orange)


//初始化函数
void Config_Init(void);

#endif









