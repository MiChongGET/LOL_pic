#include "includes.h"

/*
�������� USART2_init
����������int band :�����崮�ڵĲ�����
��������ֵ����
�������ܣ�ʵ�ִ���2�Ĺ��ܳ�ʼ������
*/
void USART2_init(int band)
{
	float USARTDIV;
	int temp1;//��ʾUSARTDIV����������
	int temp2;//��ʾUSARTDIV��С������
	//��PAʱ��
	RCC->APB2ENR |=(1<<2);
	// PA2--USART2_TX �����������50M 1011
	GPIOA->CRL &=~(0XF<<4*2);
	GPIOA->CRL |=(0XB<<4*2);
	//PA3--USART2_RX  ������ 1000
	GPIOA->CRL &=~(0XF<<4*3);
	GPIOA->CRL |=(0X8<<4*3);
	//����������
	GPIOA->ODR |=(1<<3);
	//�򿪴���2������ʱ��
	RCC->APB1ENR |=(1<<17);
	//���ô���2�ķ���/���յĲ�����
	USARTDIV =(float)36000000/(16*band);
	temp1 =USARTDIV;
	temp2 =(USARTDIV-temp1)*16;
	USART2->BRR = temp1<<4 |temp2;
	//CR1 ���ƼĴ���
	//��ֹ��żУ��-����Ӳ��CRCУ��
	USART2->CR1 &=~(1<<10);
	//����ʹ��
	USART1->CR1 |=(1<<3);
	//����ʹ��
	USART2->CR1 |=(1<<2);
	//������������-�����ͶϿ�֡
	USART2->CR1 &=~(1<<0);
	//���ڹ���ʹ��-һ��Ҫ���������ù�����ɺ�һ�����ڹ���ʹ�ܣ����ڿ�ʼ����
	USART2->CR1 |=(1<<13);	
}

/*
��������Send_byte
���������� char date Ҫ���͵��ַ�
��������ֵ����
�������ܣ�ʵ�ִ���1����һ���ֽ�
*/
void Send_byte2(char date)
{
	//�ȴ��ϴ����ݷ�����
	while((USART2->SR &(1<<6))==0);
	//��������
	USART2->DR =date;
}

/*
��������Receive_byte
������������
��������ֵ�� char
    ��ʾ���յ�������
�������ܣ�ʵ�ִ���1����һ���ֽ�
*/
char Receive_byte2(void)
{
	char date;
	//�ȴ����յ�����
	while((USART2->SR &(1<<5))==0);
	date =USART2->DR;
	return date;
}

/*
��������Send_string
���������� �ַ�ָ�� char *str
��������ֵ����
�������ܣ�ʵ���ַ����ķ���
*/
void Send_string2(char *str)
{
	while(*str !='\0')
	{
		Send_byte2(*str);
		str++;
	}
	Send_byte2('\r');
	Send_byte2('\n');
}

/*
��������Receive_string
���������� char *str �ַ�ָ��
          ���յ����ַ���
��������ֵ����
�������ܣ�ʵ���ַ����Ľ���
*/
void Receive_string2(char *str)
{
	char date;
	while(1)
	{
		date =Receive_byte2();
		if(date =='\n'||date =='\r')//������־
			break;
		*str =date;
		str++;		
	}
	*str ='\0';
	
}







