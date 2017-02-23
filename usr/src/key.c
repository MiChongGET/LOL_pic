#include "includes.h"

/*
��������KEY_init
������������
��������ֵ����
�������ܣ�ʵ�ְ����ܽ�ģʽ�ĳ�ʼ��
*/
void KEY_init(void)
{
	//��ʱ��  PA PE
	RCC->APB2ENR |=(1<<2)|(1<<6);
	//AP0 �������� 0100
	GPIOA->CRL &=~(0XF<<4*0);
	GPIOA->CRL |=(0X4<<4*0);
	//PE2
	GPIOE->CRL &=~(0XF<<4*2);
	GPIOE->CRL |=(0X4<<4*2);
	//PE3
	GPIOE->CRL &=~(0XF<<4*3);
	GPIOE->CRL |=(0X4<<4*3);
	//PE4
	GPIOE->CRL &=~(0XF<<4*4);
	GPIOE->CRL |=(0X4<<4*4);
	
}


/*
�������� Get_KeyValue
������������
��������ֵ�� int 
�������ܣ������°����õ���ֵ����
*/
int Get_KeyValue(void)
{
	if(KEY1==0)//PA0����
	{
		  Delay_ms(10);//����
		if(KEY1==0)//PA0��İ���
		{
			return 1;
		}
	}
	if(KEY2!=0)//PE2����
	{
		Delay_ms(10);//����
		if(KEY2!=0)//PE2��İ���
		{
			return 2;
		}
	}
	if(KEY3==0)//PE3����
	{
		Delay_ms(10);//����
		if(KEY3==0)//PE3��İ���
		{
			return 3;
		}
	}
	if(KEY4==0)//PE4����
	{
		Delay_ms(10);//����
		if(KEY4==0)//PE4��İ���
		{
			return 4;
		}
	}
}


/*
��������Get_key
������������
��������ֵ�� int 
�������ܣ������°����õ���ֵ����
*/
int Get_key(void)
{
	static int  value=1;//��ʾ�а�������
	// value==1 ����  value ==0 �ް���
	if((value==1)&&(KEY1==0 ||KEY2 !=0 ||KEY3==0||KEY4==0))//�а�������
	{
		Delay_ms(10);//����
		if(KEY1==0) return 1;
		if(KEY2!=0) return 2;
		if(KEY3==0) return 3;
		if(KEY4==0) return 4;
	}
	else if (KEY1!=0 &&KEY2 ==0 &&KEY3!=0&&KEY4!=0)
	{
		value=0;//�ް�������
	}
	
}
