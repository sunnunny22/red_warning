#ifndef __HMI_H
#define __HMI_H
#include "sys.h"


void HMI_SendNum(USART_TypeDef* USARTx,u8 *data,u8 len,u16 Num,u8 len2);
void HMI_SendText(USART_TypeDef* USARTx,u8 *data,u8 len,u8 *text,u8 len2);


#endif
