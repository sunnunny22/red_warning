#ifndef _esp8266_send_H_
#define _esp8266_send_H_
#include "stm32f10x.h"
#include <stdio.h>
#include "string.h"
#include "usart.h"
#include "esp8266.h"
#include "onenet.h"
#include "edpkit.h"

typedef struct
{

	u8 Data1;
	u8 Data2;
	u8 Data3;
	u8 Data4;

} Send_Data;				/*Ҫ���͵����ݱ���������ֻ����4��*/

extern Send_Data send_data;


void esp8266_rec(void);				/*�������е��������н��գ����ݴ�������������ֻ�ǵ���*/
void data_pro(char *req);			/*�������ݽ��д���*/
void data_send(void);					/*Ҫ���͵�����*/


#endif

