#ifndef  _LED_H_
#define  _LED_H_

#define LED3_ON GPIOB->ODR &=~(1<<5)
                 //GPIOB->BSRR =(1<<(16+5))
								 //GPIOB->BRR =(1<<5)
#define LED4_ON GPIOE->ODR &=~(1<<5)
#define LED5_ON GPIOA->ODR &=~(1<<5)
#define LED6_ON GPIOA->ODR &=~(1<<6)


#define LED3_OFF GPIOB->ODR |=(1<<5)
                //GPIOB->BSRR =(1<<5)
#define LED4_OFF GPIOE->ODR |=(1<<5)
#define LED5_OFF GPIOA->ODR |=(1<<5)
#define LED6_OFF GPIOA->ODR |=(1<<6)


void  LED_init(void);
void LED_ALLON(void);
void LED_ALLOFF(void);

void LED_water(void);
#endif

