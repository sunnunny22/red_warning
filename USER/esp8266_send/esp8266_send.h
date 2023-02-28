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

} Send_Data;				/*要发送的数据变量，这里只搞了4个*/

extern Send_Data send_data;


void esp8266_rec(void);				/*主程序中调用来进行接收，数据处理不用这个，这个只是调用*/
void data_pro(char *req);			/*接收数据进行处理*/
void data_send(void);					/*要发送的数据*/


#endif

