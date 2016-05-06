#include "display.h"
#include "lcd.h"
#include "utils.h"
#include "gui.h"
#include "test.h"
#include "pic.h"

//========================variable==========================//
u16 ColorTab[5]={BRED,YELLOW,RED,GREEN,BLUE};//定义颜色数组
//=====================end of variable======================//

//******************************************************************
//函数名：  DrawTestPage
//日期：    2013-02-22
//功能：    绘制测试界面
//输入参数：str :字符串指针
//返回值：  无
//修改记录：
//******************************************************************
void DrawTestPage(u8 *str)
{
//绘制固定栏up
LCD_Fill(0,0,lcddev.width,20,BLUE);
//绘制固定栏down
LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
POINT_COLOR=WHITE;
Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//居中显示
Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,(u8*)"Qianzf版权所有",16,1);//居中显示
//绘制测试区域
LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}
/***********************************************************
*
*							显示系统的欢迎信息
*
**********************************************************/
void display_welcome()
{
	DrawTestPage("欢迎使用本系统");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GRAY);

	Gui_StrCenter(10,70,WHITE,YELLOW,"钱中飞的毕业设计作品",16,1);
	
	Gui_StrCenter(10,120,WHITE,YELLOW,"主芯片：STM32F407VG",16,1);
	Gui_StrCenter(10,140,WHITE,YELLOW,"无线芯片：ESP8862",16,1);
	Gui_StrCenter(10,160,WHITE,YELLOW,"FLASH: 1MB（板载）",16,1);
	Gui_StrCenter(10,180,WHITE,YELLOW,"屏幕分辨率：320x480",16,1);
	Gui_StrCenter(10,280,WHITE,YELLOW,"GitHub首页：http://qianzf.github.io",16,1);
	//完成后延时一下
	delay_ms(1200);
}

/***********************************************************
*
*						显示系统界面
*
**********************************************************/
void display_title(char* str)
{
	LCD_Fill(6,26,lcddev.width-6,69,WHITE);
	Gui_StrCenter(10,40,BLACK,YELLOW,(u8*)str,16,1);
}

void display_info(char* str)
{
	LCD_Fill(6,71,lcddev.width-6,lcddev.height-26,WHITE);
	Show_Str(10,75,BLACK,YELLOW,(u8*)str,16,1);
}

void display_now()
{
	
	DrawTestPage("服务器IP:192.168.4.1     服务器端口：4848");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(5,25,lcddev.width-5,lcddev.height-25);
	LCD_DrawLine(5,70,lcddev.width-5,70);
	
	display_title("智能办公提示牌");
	display_info("请使用安卓客户端来更改显示内容");
	//完成后延时一下
	delay_ms(120);
}
/*********************************************************
**
**
*********************************************************/

void word_tips(u16 height,char* str,u16 color)
{
		LCD_Fill(0,height,lcddev.width,height+20,color);
		Gui_StrCenter(5,height,BLACK,YELLOW,(u8*)str,16,0);
}



