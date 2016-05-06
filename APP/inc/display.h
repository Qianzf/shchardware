#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f4xx.h"

void DrawTestPage(u8* str);
void display_welcome(void);
void display_now(void);
void word_tips(u16 height,char* str,u16 color);
void display_title(char* str);
void display_info(char* str);

#endif




