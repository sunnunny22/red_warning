#ifndef _USART_H_
#define _USART_H_


#include "stm32f10x.h"


#define USART_DEBUG		USART1		//调试打印所使用的串口组

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

#define EN_USART3_RX 			1	

void Usart1_Init(unsigned int baud);

void Usart2_Init(unsigned int baud);

void uart3_init(u32 bound);

void HMISends(char *buf1);

void HMISendb(u8 k);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif
