#ifndef __LCD_H__
#define __LCD_H__

#include "stm32f10x.h"



//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)




extern const unsigned char gImage_pic[307208];
extern const unsigned char gImage_pic1[306248];
extern const unsigned char gImage_pic2[259200];
extern const unsigned char gImage_flag[307208] ;
extern const unsigned char gImage_guohui[307208];
extern const unsigned char gImage_lol[307208];


void LCD_init(void);

void LCD_ILI9341_CMD(u16 cmd);
void LCD_ILI9341_Parameter(u16 data);
void LCD_clear(u16 color);
void LCD_Display_Point(u16 x,u16 y,u16 color);
void LCD_Dishz(u16 x,u16 y,u16 color,u16 backcolor,const u8 *str);
void LCD_Dis24X24hz(u16 x,u16 y,u16 color,u16 backcolor,const u8 *str);

void LCD_Pic1(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_Pic2(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_Pic3(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_Pic4(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_Pic(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_flag(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_guohui(u16 x,u16 y,u16 width,u16 high,const u8 *str);
void LCD_lol(u16 x,u16 y,u16 width,u16 high,const u8 *str);
#endif
