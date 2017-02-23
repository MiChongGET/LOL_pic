#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"

void Delay_init(void);
void Delay_us(u32 nus);
void Delay_ms(u32 nus);

#endif
