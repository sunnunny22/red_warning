/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	onenet.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-05-08
	*
	*	�汾�� 		V1.1
	*
	*	˵���� 		��onenetƽ̨�����ݽ����ӿڲ�
	*
	*	�޸ļ�¼��	V1.0��Э���װ�������ж϶���ͬһ���ļ������Ҳ�ͬЭ��ӿڲ�ͬ��
	*				V1.1���ṩͳһ�ӿڹ�Ӧ�ò�ʹ�ã����ݲ�ͬЭ���ļ�����װЭ����ص����ݡ�
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "edpkit.h"

//Ӳ������
#include "usart.h"
#include "delay.h"
#include  "dht11.h"
#include "mq-2.h"
#include "UltrasonicCtrol.h"
#include  "hmi.h"
//C��
#include <string.h>
#include <stdio.h>

#include "esp8266_send.h"




extern unsigned char esp8266_buf[128];

unsigned char tick_5ms = 0;//5ms����������Ϊ�������Ļ�������

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};				//Э���

	unsigned char *dataPtr;
	
	unsigned char status = 1;
	
	UsartPrintf(USART_DEBUG, "OneNet_DevLink\r\n"
                        "DEVID: %s,     APIKEY: %s\r\n"
                        , DEVID, APIKEY);

	if(EDP_PacketConnect1(DEVID, APIKEY, 256, &edpPacket) == 0)		//����devid �� apikey��װЭ���
	{
		ESP8266_SendData(edpPacket._data, edpPacket._len);			//�ϴ�ƽ̨
		
		dataPtr = ESP8266_GetIPD(250);								//�ȴ�ƽ̨��Ӧ
		if(dataPtr != NULL)
		{
			if(EDP_UnPacketRecv(dataPtr) == CONNRESP)
			{
				switch(EDP_UnPacketConnectRsp(dataPtr))
				{
					case 0:UsartPrintf(USART_DEBUG, "Tips:	���ӳɹ�\r\n");status = 0;break;
					
					case 1:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�Э�����\r\n");break;
					case 2:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��豸ID��Ȩʧ��\r\n");break;
					case 3:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�������ʧ��\r\n");break;
					case 4:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��û�ID��Ȩʧ��\r\n");break;
					case 5:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�δ��Ȩ\r\n");break;
					case 6:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ���Ȩ����Ч\r\n");break;
					case 7:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ�������δ����\r\n");break;
					case 8:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ����豸�ѱ�����\r\n");break;
					case 9:UsartPrintf(USART_DEBUG, "WARN:	����ʧ�ܣ��ظ��������������\r\n");break;
					
					default:UsartPrintf(USART_DEBUG, "ERR:	����ʧ�ܣ�δ֪����\r\n");break;
				}
			}
		}
		
		EDP_DeleteBuffer(&edpPacket);								//ɾ��
	}
	else
		UsartPrintf(USART_DEBUG, "WARN:	EDP_PacketConnect Failed\r\n");
	
	return status;
	
}

unsigned char OneNet_FillBuf(char *buf)
{
	u8 dat1 = 21;
	u8 dat2 =53;
  u8 dat3 = 21;
	char text[128];

	memset(text, 0, sizeof(text));
	/*send_data��esp8266_send.h�ļ�����*/
	__set_PRIMASK(1);
	DHT11_Read_Data(&dat1,&dat2);
	
	__set_PRIMASK(0);
	UsartPrintf(USART_DEBUG, "%d,%d\r\n",dat1,dat2);
	  
	strcpy(buf, "{");
	
	memset(text, 0, sizeof(text));	/*����text����*/					
	sprintf(text, "\"temp\":%d,",dat1);			/*(1)*/
	strcat(buf, text);    //׷���ַ�������
	
	memset(text, 0, sizeof(text));	/*����text����*/						
	sprintf(text, "\"humi\":%d,", dat2);		/*(2)*/
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));	/*����text����*/						
  sprintf(text, "\"lsens\":%d", dat3);		/*(3)*/
	strcat(buf, text);
	
	/*
	ע�⣺���ݴ����ʽ��������ĸ�ʽ�����
				��(1)�����Ǹ�%d�����б����ţ�(2)%d����û�б��������Ҫע��
				������������������һ�������б����ţ������Ķ�Ҫ����Ȼ�Ļ����ݴ��䲻��
				Red_Led��Green_Led�����������֣�����ľ���������
	*/
	
	strcat(buf, "}");
	
	return strlen(buf);

}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(void)
{

	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};												//Э���
	
	char buf[128];
	
	short body_len = 0, i = 0;
	
	UsartPrintf(USART_DEBUG, "Tips:	OneNet_SendData-EDP\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);																	//��ȡ��ǰ��Ҫ���͵����������ܳ���
	
	if(body_len)
	{
		if(EDP_PacketSaveData(DEVID, body_len, NULL, kTypeSimpleJsonWithoutTime, &edpPacket) == 0)	//���
		{
			for(; i < body_len; i++)
				edpPacket._data[edpPacket._len++] = buf[i];
			
			ESP8266_SendData(edpPacket._data, edpPacket._len);										//�ϴ����ݵ�ƽ̨
			UsartPrintf(USART_DEBUG, "Send %d Bytes\r\n", edpPacket._len);
			
			EDP_DeleteBuffer(&edpPacket);															//ɾ��
		}
		else
			UsartPrintf(USART_DEBUG, "WARN:	EDP_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};	//Э���
	
	char *cmdid_devid = NULL;
	unsigned short cmdid_len = 0;
	char *req = NULL;
	unsigned int req_len = 0;
	unsigned char type = 0;
	
	short result = 0;
	

	
	type = EDP_UnPacketRecv(cmd);
	switch(type)										//�ж���pushdata���������·�
	{
		case CMDREQ:									//�������
			
			result = EDP_UnPacketCmd(cmd, &cmdid_devid, &cmdid_len, &req, &req_len);
			if(result == 0)								//����ɹ������������ظ������
			{
				EDP_PacketCmdResp(cmdid_devid, cmdid_len, req, req_len, &edpPacket);
				UsartPrintf(USART_DEBUG, "cmdid: %s, req: %s, req_len: %d\r\n", cmdid_devid, req, req_len);
		   
			}
			
		break;
			
		case SAVEACK:
			
			if(cmd[3] == MSG_ID_HIGH && cmd[4] == MSG_ID_LOW)
			{
				UsartPrintf(USART_DEBUG, "Tips:	Send %s\r\n", cmd[5] ? "Err" : "Ok");
			}
			else
				UsartPrintf(USART_DEBUG, "Tips:	Message ID Err\r\n");
			
		break;
			
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									//��ջ���
	
	if(result == -1)
		return;
   
	data_pro(req);			/*�������ݽ��д���*/

	
	if(type == CMDREQ && result == 0)						//���������� �� ����ɹ�
	{
		EDP_FreeBuffer(cmdid_devid);						//�ͷ��ڴ�
		EDP_FreeBuffer(req);
															//�ظ�����
		ESP8266_SendData(edpPacket._data, edpPacket._len);	//�ϴ�ƽ̨
		EDP_DeleteBuffer(&edpPacket);						//ɾ��
	}

}
