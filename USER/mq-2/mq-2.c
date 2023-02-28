#include "mq-2.h"
#include "interface.h"
//烟雾传感器初始化
void MQ_2_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //PA1作为模拟通道输入引脚
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;               //PA1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;           //模拟输入
		GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    Adc1_Init();//初始化ADC1
}

/**************************************************************************
函数功能：获取AD转换后的值(电压值)
入口参数：无
返回  值：转换后的浓度值
说    明：获取的电压范围0~5V得到的数值为：0~4096
          采用甲烷的浓度变化范围，       5000~20000
作    者：太原联航科技---李棋
**************************************************************************/
u32 Get_MQ_2_Value(void)
{      
    u32 temp_val = 0;
	u8 t;
	for(t = 0;t < MQ_2_READ_TIMES;t++)
	{
		temp_val += Get_Adc1(ADC_Channel_1);	//读取ADC值,通道1
		Delayms(5);
	}
    
	temp_val /=MQ_2_READ_TIMES; 
	//得到平均值 
	if(temp_val > 4000) temp_val = 4000;
	return (u8)(temp_val/40);
}
