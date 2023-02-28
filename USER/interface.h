#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "stm32f10x.h"

//超声波控制 外部中断返回 PB14
#define Echo_PIN         GPIO_Pin_9
#define Echo_GPIO        GPIOB
#define Echo_PORTSOURCE  GPIO_PortSourceGPIOB
#define Echo_PINSOURCE   GPIO_PinSource14
#define Echo_EXITLINE    EXTI_Line14
#define Echo_IRQCH       EXTI15_10_IRQn
#define Echo             GPIO_ReadInputDataBit(Echo_GPIO, Echo_PIN)
//触发IO PD8
#define Trig_PIN         GPIO_Pin_8
#define Trig_GPIO        GPIOB
#define Trig_RESET       GPIO_SetBits(Trig_GPIO , Trig_PIN)
#define Trig_SET         GPIO_ResetBits(Trig_GPIO , Trig_PIN)//5转3.3做了一次反相 modfied by LC 2015.09.20 10:18

extern unsigned char tick_5ms;//5ms计数器，作为主函数的基本周期
extern unsigned char tick_1ms;//1ms计数器，作为电机的基本计数器

void delay_init(void);
void Delayms(u32 Nms);
void Delay_us(u32 Nus);

void GPIOCLKInit(void);

#endif

