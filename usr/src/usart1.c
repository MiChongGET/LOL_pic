#include "includes.h"

/*
函数名： USART1_init
函数参数：int band :开发板串口的波特率
函数返回值：无
函数功能：实现串口1的功能初始化配置
*/
void USART1_init(int band)
{
	float USARTDIV;
	int temp1;//表示USARTDIV的整数部分
	int temp2;//表示USARTDIV的小数部分
	//开PA时钟
	RCC->APB2ENR |=(1<<2);
	// PA9--USART1_TX 复用推挽输出50M 1011
	GPIOA->CRH &=~(0XF<<4*(9-8));
	GPIOA->CRH |=(0XB<<4*(9-8));
	//PA10--USART1_RX  带上拉 1000
	GPIOA->CRH &=~(0XF<<4*(10-8));
	GPIOA->CRH |=(0X8<<4*(10-8));
	//区分上下拉
	GPIOA->ODR |=(1<<10);
	//打开串口1的外设时钟
	RCC->APB2ENR |=(1<<14);
	//配置串口1的发送/接收的波特率
	USARTDIV =(float)72000000/(16*band);
	temp1 =USARTDIV;
	temp2 =(USARTDIV-temp1)*16;
	USART1->BRR = temp1<<4 |temp2;
	//CR1 控制寄存器
	//禁止奇偶校验-采用硬件CRC校验
	USART1->CR1 &=~(1<<10);
	//发送使能
	USART1->CR1 |=(1<<3);
	//接收使能
	USART1->CR1 |=(1<<2);
	//数据连续传输-不发送断开帧
	USART1->CR1 &=~(1<<0);
	//串口工作使能-一定要放在在配置功能完成后；一旦串口工作使能，串口开始工作
	USART1->CR1 |=(1<<13);	
}

/*
函数名：Send_byte
函数参数： char date 要发送的字符
函数返回值：无
函数功能：实现串口1发送一个字节
*/
void Send_byte(char date)
{
	//等待上次数据发送完
	while((USART1->SR &(1<<6))==0);
	//发送数据
	USART1->DR =date;
}

/*
函数名：Receive_byte
函数参数：无
函数返回值： char
    表示接收到的数据
函数功能：实现串口1接收一个字节
*/
char Receive_byte(void)
{
	char date;
	//等待接收到数据
	while((USART1->SR &(1<<5))==0);
	date =USART1->DR;
	return date;
}

/*
函数名：Send_string
函数参数： 字符指针 char *str
函数返回值：无
函数功能：实现字符串的发送
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
函数名：Receive_string
函数参数： char *str 字符指针
          接收到的字符串
函数返回值：无
函数功能：实现字符串的接收
*/
void Receive_string(char *str)
{
	char date;
	while(1)
	{
		date =Receive_byte();
		if(date =='\n'||date =='\r')//结束标志
			break;
		*str =date;
		str++;		
	}
	*str ='\0';
	
}



#pragma import(__use_no_semihosting_swi) //取消半主机状态

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
函数名;USART1_NVIC_init
函数参数：无
函数返回值：无
函数功能：实现串口1的接收中断NVIC配置
*/
void USART1_NVIC_init(void)
{
	u32 Priority;
	//串口1的接收中断使能
	USART1->CR1 |=(1<<5);
	/*********NVIC配置******/
	//设置分组号
	NVIC_SetPriorityGrouping(7-2);
	//确定具体的抢占值、响应值
	Priority=NVIC_EncodePriority (7-2,0,3);
	//优先级设置-把优先级的数值写入寄存器
	NVIC_SetPriority(USART1_IRQn,Priority);
	//相应的中断NVIC使能
	NVIC_EnableIRQ(USART1_IRQn);
}


//中断服务函数
void USART1_IRQHandler(void)
{
	u8 date;
	//清中断标志
	date =USART1->DR;
	Send_byte(date);
}



