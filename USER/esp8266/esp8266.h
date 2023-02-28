#ifndef _ESP8266_H_
#define _ESP8266_H_

/*��������ֻҪ�滻����������*/
#define DEVID	"1030498131"

#define APIKEY	"9zMCZEBjzCmFog6qJROojgpFyWs="
                                         /*wifi����       wifi����*/
#define ESP8266_WIFI_INFO		"AT+CWJAP=\"MyWifi\",\"12345678\"\r\n"

/*��������ֻҪ�滻����������*/


#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.39\",876\r\n"   //  



#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־


void ESP8266_Init(void);

void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);


#endif
