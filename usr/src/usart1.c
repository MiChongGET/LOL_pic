#include "includes.h"

/*
�������� USART1_init
����������int band :�����崮�ڵĲ�����
��������ֵ����
�������ܣ�ʵ�ִ���1�Ĺ��ܳ�ʼ������
*/
void USART1_init(int band)
{
	float USARTDIV;
	int temp1;//��ʾUSARTDIV����������
	int temp2;//��ʾUSARTDIV��С������
	//��PAʱ��
	RCC->APB2ENR |=(1<<2);
	// PA9--USART1_TX �����������50M 1011
	GPIOA->CRH &=~(0XF<<4*(9-8));
	GPIOA->CRH |=(0XB<<4*(9-8));
	//PA10--USART1_RX  ������ 1000
	GPIOA->CRH &=~(0XF<<4*(10-8));
	GPIOA->CRH |=(0X8<<4*(10-8));
	//����������
	GPIOA->ODR |=(1<<10);
	//�򿪴���1������ʱ��
	RCC->APB2ENR |=(1<<14);
	//���ô���1�ķ���/���յĲ�����
	USARTDIV =(float)72000000/(16*band);
	temp1 =USARTDIV;
	temp2 =(USARTDIV-temp1)*16;
	USART1->BRR = temp1<<4 |temp2;
	//CR1 ���ƼĴ���
	//��ֹ��żУ��-����Ӳ��CRCУ��
	USART1->CR1 &=~(1<<10);
	//����ʹ��
	USART1->CR1 |=(1<<3);
	//����ʹ��
	USART1->CR1 |=(1<<2);
	//������������-�����ͶϿ�֡
	USART1->CR1 &=~(1<<0);
	//���ڹ���ʹ��-һ��Ҫ���������ù�����ɺ�һ�����ڹ���ʹ�ܣ����ڿ�ʼ����
	USART1->CR1 |=(1<<13);	
}

/*
��������Send_byte
���������� char date Ҫ���͵��ַ�
��������ֵ����
�������ܣ�ʵ�ִ���1����һ���ֽ�
*/
void Send_byte(char date)
{
	//�ȴ��ϴ����ݷ�����
	while((USART1->SR &(1<<6))==0);
	//��������
	USART1->DR =date;
}

/*
��������Receive_byte
������������
��������ֵ�� char
    ��ʾ���յ�������
�������ܣ�ʵ�ִ���1����һ���ֽ�
*/
char Receive_byte(void)
{
	char date;
	//�ȴ����յ�����
	while((USART1->SR &(1<<5))==0);
	date =USART1->DR;
	return date;
}

/*
��������Send_string
���������� �ַ�ָ�� char *str
��������ֵ����
�������ܣ�ʵ���ַ����ķ���
*/
void Send_string(char *str)
{
	while(*str !='\0')
	{
		Send_byte(*str);
		str++;
	}
	Send_byte('\r');
	Send_byte('\n');
}

/*
��������Receive_string
���������� char *str �ַ�ָ��
          ���յ����ַ���
��������ֵ����
�������ܣ�ʵ���ַ����Ľ���
*/
void Receive_string(char *str)
{
	char date;
	while(1)
	{
		date =Receive_byte();
		if(date =='\n'||date =='\r')//������־
			break;
		*str =date;
		str++;		
	}
	*str ='\0';
	
}



#pragma import(__use_no_semihosting_swi) //ȡ��������״̬

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;

int fputc(int ch, FILE *f) {
	Send_byte(ch);
  return (ch);
}
int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  Send_byte(ch);
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}




/*
������;USART1_NVIC_init
������������
��������ֵ����
�������ܣ�ʵ�ִ���1�Ľ����ж�NVIC����
*/
void USART1_NVIC_init(void)
{
	u32 Priority;
	//����1�Ľ����ж�ʹ��
	USART1->CR1 |=(1<<5);
	/*********NVIC����******/
	//���÷����
	NVIC_SetPriorityGrouping(7-2);
	//ȷ���������ռֵ����Ӧֵ
	Priority=NVIC_EncodePriority (7-2,0,3);
	//���ȼ�����-�����ȼ�����ֵд��Ĵ���
	NVIC_SetPriority(USART1_IRQn,Priority);
	//��Ӧ���ж�NVICʹ��
	NVIC_EnableIRQ(USART1_IRQn);
}


//�жϷ�����
void USART1_IRQHandler(void)
{
	u8 date;
	//���жϱ�־
	date =USART1->DR;
	Send_byte(date);
}



