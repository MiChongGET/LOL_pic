#ifndef _USART2_H_
#define _USART2_H_



void USART2_init(int band);
void Send_byte2(char date);
char Receive_byte2(void);
void Send_string2(char *str);
void Receive_string2(char *str);

#endif
