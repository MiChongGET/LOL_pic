#include "includes.h"

/*
时钟：f=9M HZ 频率：每秒产生9M个波形
    每秒晶振震荡9M次，一次一个脉冲
定时时间= 计数值*计一个数所需时间
一个脉冲--计数器数值变化一次
一个脉冲时间==周期 T=1/f=1/9M (s)
定时1s:计数器值变化9M次
定时1ms: ---------9000次
定时1us:----------9次
*/

u16 sys_ms=9000 ;//表示在9MHZ时钟下延时1ms所需的计数值
u8  sys_us =9;//表示在9MHZ时钟下延时1us所需的计数值

/*
函数名;Delay_init
函数参数：无
函数返回值：无
函数功能：实现滴答时钟的初始化
*/
void Delay_init(void)
{
	//计数到0时不进中断
	SysTick->CTRL &=~(1<<1);
	//选择外部时钟 9M HZ
	SysTick->CTRL &=~(1<<2);
	
}

/*
函数名;Delay_ms
函数参数： u32 nms
         要延时的毫秒数
函数返回值：无
函数功能：实现毫秒级别的延时
*/
void Delay_ms(u32 nms)
{
	//把所需的计数值写入到重装载寄存器中
	// 公式：重装载值=nms *延时1ms所需的计数值
  SysTick->LOAD =nms*sys_ms;
	//清空当前值计数器
	SysTick->VAL =0;
	//打开滴答定时器
	SysTick->CTRL |=(1<<0);
	//等待计数器的数值递减到0
	while((SysTick->CTRL &(1<<16))==0);
	//关闭滴答定时器
	SysTick->CTRL &=~(1<<0);
}

/*
函数名;Delay_us
函数参数： u32 nus
         要延时的微秒数
函数返回值：无
函数功能：实现微秒级别的延时
*/
void Delay_us(u32 nus)
{
	//把所需的计数值写入到重装载寄存器中
	// 公式：重装载值=nus *延时1us所需的计数值
  SysTick->LOAD =nus*sys_us;
	//清空当前值计数器
	SysTick->VAL =0;
	//打开滴答定时器
	SysTick->CTRL |=(1<<0);
	//等待计数器的数值递减到0
	while((SysTick->CTRL &(1<<16))==0);
	//关闭滴答定时器
	SysTick->CTRL &=~(1<<0);
}







