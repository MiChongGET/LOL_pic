#include "includes.h"
int i,j;
void Delay(int time)
{
	while(time--);
}


int main()
{
	//滴答时钟初始化
	Delay_init();
	//LED初始化
	LED_init();
	//LED全亮
	//蜂鸣器初始化
	BEEP_init();
	//按键初始化
	KEY_init();
  LED_ALLOFF();
  USART1_init(9600);
  USART1_NVIC_init();
	USART2_init(115200);
	//LCD屏初始化
	LCD_init();
	
	
	
	
		
	
	  
		
		while(1)
		{
//			LCD_Pic(0,0,320,480,gImage_flag);
//			Delay(5000000);
			LCD_Pic(0,0,320,480,gImage_lol);
    }
		

	
}
