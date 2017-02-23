#include "includes.h"

/*
函数名：KEY_init
函数参数：无
函数返回值：无
函数功能：实现按键管脚模式的初始化
*/
void KEY_init(void)
{
	//开时钟  PA PE
	RCC->APB2ENR |=(1<<2)|(1<<6);
	//AP0 浮空输入 0100
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
函数名： Get_KeyValue
函数参数：无
函数返回值： int 
函数功能：将按下按键得到的值返回
*/
int Get_KeyValue(void)
{
	if(KEY1==0)//PA0按下
	{
		  Delay_ms(10);//消抖
		if(KEY1==0)//PA0真的按下
		{
			return 1;
		}
	}
	if(KEY2!=0)//PE2按下
	{
		Delay_ms(10);//消抖
		if(KEY2!=0)//PE2真的按下
		{
			return 2;
		}
	}
	if(KEY3==0)//PE3按下
	{
		Delay_ms(10);//消抖
		if(KEY3==0)//PE3真的按下
		{
			return 3;
		}
	}
	if(KEY4==0)//PE4按下
	{
		Delay_ms(10);//消抖
		if(KEY4==0)//PE4真的按下
		{
			return 4;
		}
	}
}


/*
函数名：Get_key
函数参数：无
函数返回值： int 
函数功能：将按下按键得到的值返回
*/
int Get_key(void)
{
	static int  value=1;//表示有按键按下
	// value==1 按下  value ==0 无按下
	if((value==1)&&(KEY1==0 ||KEY2 !=0 ||KEY3==0||KEY4==0))//有按键按下
	{
		Delay_ms(10);//消抖
		if(KEY1==0) return 1;
		if(KEY2!=0) return 2;
		if(KEY3==0) return 3;
		if(KEY4==0) return 4;
	}
	else if (KEY1!=0 &&KEY2 ==0 &&KEY3!=0&&KEY4!=0)
	{
		value=0;//无按键按下
	}
	
}
