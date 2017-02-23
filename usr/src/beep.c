#include "includes.h"

/*
函数名：BEEP_init
函数参数：无
函数返回值：无
函数功能：实现蜂鸣器管脚的初始化
*/

void BEEP_init(void)
{
	//开PB 时钟
	RCC->APB2ENR |=(1<<3);
	//配置PB8 推挽输出 50M
	/*
	 4： 4个位配置一个管脚
	 第一个8： 配置的是管脚8
	 第二个8： CRH该寄存器从8管脚开始的
	*/
	GPIOB->CRH &=~(0XF<<4*(8-8));//清零
	GPIOB->CRH |=(0X3<<4*(8-8));
}

/*
函数名：BEEP_water
函数参数：无
函数返回值：无
函数功能：实现蜂鸣器的循环响
*/
void BEEP_water(void)
{
	while(1)
	{
		BEEP_ON;
		//延时
		  Delay_ms(1000);
		BEEP_OFF;
		//延时
		  Delay_ms(1000);
		if(KEY1==0 ||KEY2 !=0 ||KEY3==0||KEY4==0)
			break;
	}
}


















