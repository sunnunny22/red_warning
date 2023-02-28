#include "esp8266_send.h"
#include  "interface.h"

Send_Data send_data;

void esp8266_rec(void)			/*主程序中调用来进行接收，数据处理不用这个，这个只是调用*/
{
	  unsigned char *dataPtr = NULL;
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
}
/*数据处理是下面这个子函数*/
void data_pro(char *req)			/*接收数据进行处理*/
{
	char *dataPtr = NULL;
	char numBuf[15];
	int  num=0 ;
	
	dataPtr = strchr(req, ':');							//搜索':'
	if(dataPtr != NULL)									//如果找到了
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//转为数值形式
		printf("得到的数据为%d\r\n",num);

		/*上面是数据处理，下面是接收的指令*/
		/*onenet上面开关指令
		红灯：
				开关开值：redled:1
				开关关值：redled:0
		绿灯：
				开关开值：greenled:1
				开关关值：greenled:0
		*/
		if(strstr((char *)req, "openfs"))				//搜索"redled"
		{
			if(num == 1)								//控制数据如果为1，代表开
			{
				send_data.Data1 = 1;
				//TIM_SetCompare2(TIM3,1945);	//占空比 （2000-1950）/2000 * 20mS=0.5mS  
					Delayms(2500);
				printf("红灯开\r\n");
					
			}
			else if(num == 0)							//控制数据如果为0，代表关
			{				
				send_data.Data1 = 0;
				__set_PRIMASK(1);
			//TIM_SetCompare2(TIM3,1750);	//占空比 （2000-1950）/2000 * 20mS=0.5mS  
				Delayms(2500);
				__set_PRIMASK(0);			
				printf("红灯关\r\n");
			}
		}
														//下同
		else if(strstr((char *)req, "opendp"))
		{
			if(num == 1)
			{
				send_data.Data2 = 1;
				printf("绿灯开\r\n");
			}
			else if(num == 0)
			{
				send_data.Data2 = 0;
				printf("绿灯关\r\n");
			}
		}
		
		
		
		
	}	
}

void data_send(void)				/*要发送的数据*/
{
	/*
		要发送的数据在onenet.c中的OneNet_FillBuf()子函数那里，这里只是说明，没有用
	*/
}

