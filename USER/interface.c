#include "interface.h"

void delay_init(void)
{
   SysTick->CTRL&=0xfffffffb;//控制寄存器，选择外部时钟即系统时钟的八分之一（HCLK/8；72M/8=9M）
}

//1us 延时函数
void Delay_us(u32 Nus)   
{   
SysTick->LOAD=Nus*9;          //时间加载    72M主频     
SysTick->CTRL|=0x01;             //开始倒数      
while(!(SysTick->CTRL&(1<<16))); //等待时间到达   
SysTick->CTRL=0X00000000;        //关闭计数器   
SysTick->VAL=0X00000000;         //清空计数器        
} 

void Delayms(u32 Nms)
{
	while(Nms--)
	{
		Delay_us(1000);
	}
}

//使能所有GPIO时钟
void GPIOCLKInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG , ENABLE);
}





