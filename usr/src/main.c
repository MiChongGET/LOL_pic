#include "includes.h"
int i,j;
void Delay(int time)
{
	while(time--);
}


int main()
{
	//�δ�ʱ�ӳ�ʼ��
	Delay_init();
	//LED��ʼ��
	LED_init();
	//LEDȫ��
	//��������ʼ��
	BEEP_init();
	//������ʼ��
	KEY_init();
  LED_ALLOFF();
  USART1_init(9600);
  USART1_NVIC_init();
	USART2_init(115200);
	//LCD����ʼ��
	LCD_init();
	
	
	
	
		
	
	  
		
		while(1)
		{
//			LCD_Pic(0,0,320,480,gImage_flag);
//			Delay(5000000);
			LCD_Pic(0,0,320,480,gImage_lol);
    }
		

	
}
