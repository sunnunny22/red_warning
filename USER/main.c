#include "public.h"
#include  "dht11.h"
#include   "timer.h"
#include "UltrasonicCtrol.h"


int main()
{
			int timeCount = 0;	//���ͼ������
			delay_init();
			Usart1_Init(115200);	
	//����1����ӡ��Ϣ��
			Usart2_Init(115200);		
	//����2������ESP8266��
      uart3_init(115200);
	
		    GPIOCLKInit();
		  
				ESP8266_Init();			//��ʼ��ESP8266
			while(OneNet_DevLink())	//����OneNET
					Delayms(500);
		
			while(1)
			{
	
				if(++timeCount >= 500)									//���ͼ��5s
				{
					printf("��onenetƽ̨��������:\r\n");	
					
					OneNet_SendData();									//��������
					
					timeCount = 0;
					
					ESP8266_Clear();
				
				
				Delayms(500);
				}
											
		
				
				
				
			}
}

