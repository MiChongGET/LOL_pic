#include "includes.h"

/*
函数名： LED_init
函数参数：无
函数返回值：无
函数功能：实现LED灯管脚模式的初始化配置
*/
void  LED_init(void)
{
	//打开管脚的时钟 PA PB PE
	/*
	 APB2外设时钟使能寄存器的第2 3 6位 写1
	*/
	RCC->APB2ENR |= (1<<2)|(1<<3)|(1<<6);
	//管脚配置
	// PA5 通用推挽 输出速率 50M 0011
	//清零  
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
函数名： LED_ALLON
函数参数：无
函数返回值：无
函数功能： 实现4个LED灯全亮
*/
void LED_ALLON(void)
{
	LED3_ON;
	LED4_ON;
	LED5_ON;
	LED6_ON;	
}

/*
函数名： LED_ALLOFF
函数参数：无
函数返回值：无
函数功能： 实现4个LED灯全灭
*/
void LED_ALLOFF(void)
{
	LED3_OFF;
	LED4_OFF;
	LED5_OFF;
	LED6_OFF;	
}

/*
函数名： LED_water
函数参数：无
函数返回值：无
函数功能：实现led灯的循环闪烁
*/

void LED_water(void)
{
	while(1)
	{
		LED_ALLON();
		//延时
	  Delay_ms(1000);
		LED_ALLOFF();
		Delay_ms(1000);
		if(KEY1==0 ||KEY2 !=0 ||KEY3==0||KEY4==0)
			break;
	}
}


