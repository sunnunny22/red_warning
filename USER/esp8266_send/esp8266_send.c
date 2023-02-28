#include "esp8266_send.h"
#include  "interface.h"

Send_Data send_data;

void esp8266_rec(void)			/*�������е��������н��գ����ݴ�������������ֻ�ǵ���*/
{
	  unsigned char *dataPtr = NULL;
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
}
/*���ݴ�������������Ӻ���*/
void data_pro(char *req)			/*�������ݽ��д���*/
{
	char *dataPtr = NULL;
	char numBuf[15];
	int  num=0 ;
	
	dataPtr = strchr(req, ':');							//����':'
	if(dataPtr != NULL)									//����ҵ���
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//תΪ��ֵ��ʽ
		printf("�õ�������Ϊ%d\r\n",num);

		/*���������ݴ��������ǽ��յ�ָ��*/
		/*onenet���濪��ָ��
		��ƣ�
				���ؿ�ֵ��redled:1
				���ع�ֵ��redled:0
		�̵ƣ�
				���ؿ�ֵ��greenled:1
				���ع�ֵ��greenled:0
		*/
		if(strstr((char *)req, "openfs"))				//����"redled"
		{
			if(num == 1)								//�����������Ϊ1������
			{
				send_data.Data1 = 1;
				//TIM_SetCompare2(TIM3,1945);	//ռ�ձ� ��2000-1950��/2000 * 20mS=0.5mS  
					Delayms(2500);
				printf("��ƿ�\r\n");
					
			}
			else if(num == 0)							//�����������Ϊ0�������
			{				
				send_data.Data1 = 0;
				__set_PRIMASK(1);
			//TIM_SetCompare2(TIM3,1750);	//ռ�ձ� ��2000-1950��/2000 * 20mS=0.5mS  
				Delayms(2500);
				__set_PRIMASK(0);			
				printf("��ƹ�\r\n");
			}
		}
														//��ͬ
		else if(strstr((char *)req, "opendp"))
		{
			if(num == 1)
			{
				send_data.Data2 = 1;
				printf("�̵ƿ�\r\n");
			}
			else if(num == 0)
			{
				send_data.Data2 = 0;
				printf("�̵ƹ�\r\n");
			}
		}
		
		
		
		
	}	
}

void data_send(void)				/*Ҫ���͵�����*/
{
	/*
		Ҫ���͵�������onenet.c�е�OneNet_FillBuf()�Ӻ����������ֻ��˵����û����
	*/
}

