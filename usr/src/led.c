#include "includes.h"

/*
�������� LED_init
������������
��������ֵ����
�������ܣ�ʵ��LED�ƹܽ�ģʽ�ĳ�ʼ������
*/
void  LED_init(void)
{
	//�򿪹ܽŵ�ʱ�� PA PB PE
	/*
	 APB2����ʱ��ʹ�ܼĴ����ĵ�2 3 6λ д1
	*/
	RCC->APB2ENR |= (1<<2)|(1<<3)|(1<<6);
	//�ܽ�����
	// PA5 ͨ������ ������� 50M 0011
	//����  
	GPIOA->CRL &=~(0XF<<4*5);
	GPIOA->CRL |=(0X3<<4*5);
	//PA6
	GPIOA->CRL &=~(0XF<<4*6);
	GPIOA->CRL |=(0X3<<4*6);
	//PB5
	GPIOB->CRL &=~(0XF<<4*5);
	GPIOB->CRL |=(0X3<<4*5);
	//PE5
	GPIOE->CRL &=~(0XF<<4*5);
	GPIOE->CRL |=(0X3<<4*5);	
}
/*
�������� LED_ALLON
������������
��������ֵ����
�������ܣ� ʵ��4��LED��ȫ��
*/
void LED_ALLON(void)
{
	LED3_ON;
	LED4_ON;
	LED5_ON;
	LED6_ON;	
}

/*
�������� LED_ALLOFF
������������
��������ֵ����
�������ܣ� ʵ��4��LED��ȫ��
*/
void LED_ALLOFF(void)
{
	LED3_OFF;
	LED4_OFF;
	LED5_OFF;
	LED6_OFF;	
}

/*
�������� LED_water
������������
��������ֵ����
�������ܣ�ʵ��led�Ƶ�ѭ����˸
*/

void LED_water(void)
{
	while(1)
	{
		LED_ALLON();
		//��ʱ
	  Delay_ms(1000);
		LED_ALLOFF();
		Delay_ms(1000);
		if(KEY1==0 ||KEY2 !=0 ||KEY3==0||KEY4==0)
			break;
	}
}


