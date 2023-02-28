#include "mq-2.h"
#include "interface.h"
//����������ʼ��
void MQ_2_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //PA1��Ϊģ��ͨ����������
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;               //PA1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;           //ģ������
		GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    Adc1_Init();//��ʼ��ADC1
}

/**************************************************************************
�������ܣ���ȡADת�����ֵ(��ѹֵ)
��ڲ�������
����  ֵ��ת�����Ũ��ֵ
˵    ������ȡ�ĵ�ѹ��Χ0~5V�õ�����ֵΪ��0~4096
          ���ü����Ũ�ȱ仯��Χ��       5000~20000
��    �ߣ�̫ԭ�����Ƽ�---����
**************************************************************************/
u32 Get_MQ_2_Value(void)
{      
    u32 temp_val = 0;
	u8 t;
	for(t = 0;t < MQ_2_READ_TIMES;t++)
	{
		temp_val += Get_Adc1(ADC_Channel_1);	//��ȡADCֵ,ͨ��1
		Delayms(5);
	}
    
	temp_val /=MQ_2_READ_TIMES; 
	//�õ�ƽ��ֵ 
	if(temp_val > 4000) temp_val = 4000;
	return (u8)(temp_val/40);
}
