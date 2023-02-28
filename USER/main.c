#include "public.h"
#include  "dht11.h"
#include   "timer.h"
#include "UltrasonicCtrol.h"


int main()
{
			int timeCount = 0;	//发送间隔变量
			delay_init();
			Usart1_Init(115200);	
	//串口1，打印信息用
			Usart2_Init(115200);		
	//串口2，驱动ESP8266用
      uart3_init(115200);
	
		    GPIOCLKInit();
		  
				ESP8266_Init();			//初始化ESP8266
			while(OneNet_DevLink())	//接入OneNET
					Delayms(500);
		
			while(1)
			{
	
				if(++timeCount >= 500)									//发送间隔5s
				{
					printf("向onenet平台发送数据:\r\n");	
					
					OneNet_SendData();									//发送数据
					
					timeCount = 0;
					
					ESP8266_Clear();
				
				
				Delayms(500);
				}
											
		
				
				
				
			}
}

