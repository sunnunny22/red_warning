#include "stm32f10x_it.h"
#include"public.h"

/****************�����ж�*******************************/
//void USART1_IRQHandler()
//{
//	static u8 k;
//  USART_ClearFlag(USART1,USART_FLAG_TC);
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=Bit_RESET)//���ָ����USART�жϷ������
//	{
//		k=USART_ReceiveData(USART1);
//		k++;	
//		USART_SendData(USART1,k);//ͨ������USARTx���͵�������
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==Bit_RESET);	
//	}
//}  
/****************�����ж�*******************************/

/****************�����ж�*******************************/
/*void EXTI0_IRQHandler()  //�ж���·0
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET) //�����⵽�ж�
	{
  EXTI_ClearITPendingBit(EXTI_Line0);   //����ж�
	delay_ms(10);   //������Ҫ
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1) //��ȡA0�����Ϊ1���������¾�ִ�������
	{
    delay_ms(10);     
			if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_1)==0)   //�Ƶ�ת��
			{
			   GPIO_SetBits(GPIOC,GPIO_Pin_1);	
			}
			else
			{
				GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			}		 
	}
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1);   //�ȴ������뿪
 }
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
}*/
/****************�����ж�*******************************/



