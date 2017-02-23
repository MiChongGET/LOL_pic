#ifndef _USART1_H_
#define _USART1_H_



void USART1_init(int band);
void Send_byte(char date);
char Receive_byte(void);
void Send_string(char *str);
void Receive_string(char *str);
void USART1_NVIC_init(void);
#endif
