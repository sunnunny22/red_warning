#ifndef _ESP8266_H_
#define _ESP8266_H_

/*完整程序只要替换着三个即可*/
#define DEVID	"1030498131"

#define APIKEY	"9zMCZEBjzCmFog6qJROojgpFyWs="
                                         /*wifi名字       wifi密码*/
#define ESP8266_WIFI_INFO		"AT+CWJAP=\"MyWifi\",\"12345678\"\r\n"

/*完整程序只要替换着三个即可*/


#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.39\",876\r\n"   //  



#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志


void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);


#endif
