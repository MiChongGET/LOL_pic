#ifndef  _KEY_H_
#define  _KEY_H_

#define  KEY_UP    1
#define  KEY_LEFT  2
#define  KEY_DOWN  3
#define  KEY_RIGTH 4

#define KEY1 (GPIOA->IDR &(1<<0))
#define KEY2 (GPIOE->IDR &(1<<2))
#define KEY3 (GPIOE->IDR &(1<<3))
#define KEY4 (GPIOE->IDR &(1<<4))


void KEY_init(void);
int Get_KeyValue(void);
int Get_key(void);
#endif
