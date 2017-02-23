#include "includes.h"

/*
函数名： USART2_init
函数参数：int band :开发板串口的波特率
函数返回值：无
函数功能：实现串口2的功能初始化配置
*/
void USART2_init(int band)
{
	float USARTDIV;
	int temp1;//表示USARTDIV的整数部分
	int temp2;//表示USARTDIV的小数部分
	//开PA时钟
	RCC->APB2ENR |=(1<<2);
	// PA2--USART2_TX 复用推挽输出50M 1011
	GPIOA->CRL &=~(0XF<<4*2);
	GPIOA->CRL |=(0XB<<4*2);
	//PA3--USART2_RX  带上拉 1000
	GPIOA->CRL &=~(0XF<<4*3);
	GPIOA->CRL |=(0X8<<4*3);
	//区分上下拉
	GPIOA->ODR |=(1<<3);
	//打开串口2的外设时钟
	RCC->APB1ENR |=(1<<17);
	//配置串口2的发送/接收的波特率
	USARTDIV =(float)36000000/(16*band);
	temp1 =USARTDIV;
	temp2 =(USARTDIV-temp1)*16;
	USART2->BRR = temp1<<4 |temp2;
	//CR1 控制寄存器
	//禁止奇偶校验-采用硬件CRC校验
	USART2->CR1 &=~(1<<10);
	//发送使能
	USART1->CR1 |=(1<<3);
	//接收使能
	USART2->CR1 |=(1<<2);
	//数据连续传输-不发送断开帧
	USART2->CR1 &=~(1<<0);
	//串口工作使能-一定要放在在配置功能完成后；一旦串口工作使能，串口开始工作
	USART2->CR1 |=(1<<13);	
}

/*
函数名：Send_byte
函数参数： char date 要发送的字符
函数返回值：无
函数功能：实现串口1发送一个字节
*/
void Send_byte2(char date)
{
	//等待上次数据发送完
	while((USART2->SR &(1<<6))==0);
	//发送数据
	USART2->DR =date;
}

/*
函数名：Receive_byte
函数参数：无
函数返回值： char
    表示接收到的数据
函数功能：实现串口1接收一个字节
*/
char Receive_byte2(void)
{
	char date;
	//等待接收到数据
	while((USART2->SR &(1<<5))==0);
	date =USART2->DR;
	return date;
}

/*
函数名：Send_string
函数参数： 字符指针 char *str
函数返回值：无
函数功能：实现字符串的发送
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
函数名：Receive_string
函数参数： char *str 字符指针
          接收到的字符串
函数返回值：无
函数功能：实现字符串的接收
*/
void Receive_string2(char *str)
{
	char date;
	while(1)
	{
		date =Receive_byte2();
		if(date =='\n'||date =='\r')//结束标志
			break;
		*str =date;
		str++;		
	}
	*str ='\0';
	
}







