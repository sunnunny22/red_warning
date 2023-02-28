#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "stm32f10x.h"

//���������� �ⲿ�жϷ��� PB14
#define Echo_PIN         GPIO_Pin_9
#define Echo_GPIO        GPIOB
#define Echo_PORTSOURCE  GPIO_PortSourceGPIOB
#define Echo_PINSOURCE   GPIO_PinSource14
#define Echo_EXITLINE    EXTI_Line14
#define Echo_IRQCH       EXTI15_10_IRQn
#define Echo             GPIO_ReadInputDataBit(Echo_GPIO, Echo_PIN)
//����IO PD8
#define Trig_PIN         GPIO_Pin_8
#define Trig_GPIO        GPIOB
#define Trig_RESET       GPIO_SetBits(Trig_GPIO , Trig_PIN)
#define Trig_SET         GPIO_ResetBits(Trig_GPIO , Trig_PIN)//5ת3.3����һ�η��� modfied by LC 2015.09.20 10:18

extern unsigned char tick_5ms;//5ms����������Ϊ�������Ļ�������
extern unsigned char tick_1ms;//1ms����������Ϊ����Ļ���������

void delay_init(void);
void Delayms(u32 Nms);
void Delay_us(u32 Nus);

void GPIOCLKInit(void);

#endif

