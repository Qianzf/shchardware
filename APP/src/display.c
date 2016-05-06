#include "display.h"
#include "lcd.h"
#include "utils.h"
#include "gui.h"
#include "test.h"
#include "pic.h"

//========================variable==========================//
u16 ColorTab[5]={BRED,YELLOW,RED,GREEN,BLUE};//������ɫ����
//=====================end of variable======================//

//******************************************************************
//��������  DrawTestPage
//���ڣ�    2013-02-22
//���ܣ�    ���Ʋ��Խ���
//���������str :�ַ���ָ��
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void DrawTestPage(u8 *str)
{
//���ƹ̶���up
LCD_Fill(0,0,lcddev.width,20,BLUE);
//���ƹ̶���down
LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
POINT_COLOR=WHITE;
Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//������ʾ
Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,(u8*)"Qianzf��Ȩ����",16,1);//������ʾ
//���Ʋ�������
LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}
/***********************************************************
*
*							��ʾϵͳ�Ļ�ӭ��Ϣ
*
**********************************************************/
void display_welcome()
{
	DrawTestPage("��ӭʹ�ñ�ϵͳ");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GRAY);

	Gui_StrCenter(10,70,WHITE,YELLOW,"Ǯ�зɵı�ҵ�����Ʒ",16,1);
	
	Gui_StrCenter(10,120,WHITE,YELLOW,"��оƬ��STM32F407VG",16,1);
	Gui_StrCenter(10,140,WHITE,YELLOW,"����оƬ��ESP8862",16,1);
	Gui_StrCenter(10,160,WHITE,YELLOW,"FLASH: 1MB�����أ�",16,1);
	Gui_StrCenter(10,180,WHITE,YELLOW,"��Ļ�ֱ��ʣ�320x480",16,1);
	Gui_StrCenter(10,280,WHITE,YELLOW,"GitHub��ҳ��http://qianzf.github.io",16,1);
	//��ɺ���ʱһ��
	delay_ms(1200);
}

/***********************************************************
*
*						��ʾϵͳ����
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
	
	DrawTestPage("������IP:192.168.4.1     �������˿ڣ�4848");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(5,25,lcddev.width-5,lcddev.height-25);
	LCD_DrawLine(5,70,lcddev.width-5,70);
	
	display_title("���ܰ칫��ʾ��");
	display_info("��ʹ�ð�׿�ͻ�����������ʾ����");
	//��ɺ���ʱһ��
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



