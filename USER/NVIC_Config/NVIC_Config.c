#include"NVIC_Config.h"
void NVIC_Config(void)
{
	
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  //��ռ���ȼ� 1 λ,�����ȼ� 3 λ
	  NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;;   //ʹ�ܻ���ʧ��ָ���� IRQ ͨ������ǲ�һ��  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //��Ӧ���ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
		NVIC_Init(&NVIC_InitStructure); 
	
}		






