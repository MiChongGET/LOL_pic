#include "includes.h"

/*
��������BEEP_init
������������
��������ֵ����
�������ܣ�ʵ�ַ������ܽŵĳ�ʼ��
*/

void BEEP_init(void)
{
	//��PB ʱ��
	RCC->APB2ENR |=(1<<3);
	//����PB8 ������� 50M
	/*
	 4�� 4��λ����һ���ܽ�
	 ��һ��8�� ���õ��ǹܽ�8
	 �ڶ���8�� CRH�üĴ�����8�ܽſ�ʼ��
	*/
	GPIOB->CRH &=~(0XF<<4*(8-8));//����
	GPIOB->CRH |=(0X3<<4*(8-8));
}

/*
��������BEEP_water
������������
��������ֵ����
�������ܣ�ʵ�ַ�������ѭ����
*/
void BEEP_water(void)
{
	while(1)
	{
		BEEP_ON;
		//��ʱ
		  Delay_ms(1000);
		BEEP_OFF;
		//��ʱ
		  Delay_ms(1000);
		if(KEY1==0 ||KEY2 !=0 ||KEY3==0||KEY4==0)
			break;
	}
}


















