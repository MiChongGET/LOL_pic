#ifndef _BEEP_H_
#define _BEEP_H_

#define  BEEP_ON   GPIOB->ODR |=(1<<8)
#define  BEEP_OFF  GPIOB->ODR &=~(1<<8)


void BEEP_init(void);
void BEEP_water(void);
#endif
