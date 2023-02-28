#include "sys.h"
#include "hmi.h"	
/************************************************************************
           ˵������������Ϊ�վ��ش��������ݷ���ָ��⣬�������º���
					 
1.��ֵ���ͺ�����void HMI_SendNum(USART_TypeDef* USARTx,u8 *data,u8 len,u16 Num,u8 len2)
            USART_TypeDef* USARTx�� ѡ�񴮿������ע������ȳ�ʼ����ʹ�ܸô���
            u16 *data����λ��������λ��Ӧ�ĸı���ֵ���룬��"n0.val="��"n1.val="
						u8 len��*data����ĳ��ȡ���"n0.val="����Ϊ7��
            u16 Num����Ҫ���������ʾ����ֵ��ע�⿪ͷ0����ʾ���������0��ͷ�ᱨ��
            u8 len2����Ҫ��ʾ����ֵ��λ��    ע�ⲻ�ܴ�����λ�����趨��λ��

2.�ַ������ͺ�����void HMI_SendText(USART_TypeDef* USARTx,u8 *data,u8 len,u8 *text,u8 len2)
            USART_TypeDef* USARTx�� ѡ�񴮿������ע������ȳ�ʼ����ʹ�ܸô���
            u16 *data����λ�����ı�λ��Ӧ�ĸı���ֵ���룬��"t0.txt="��"t1.txt="
          	u8 len��*data����ĳ��ȡ���"t0.txt="����Ϊ7��
            u8 *text����Ҫ���������ʾ���ı�
            u8 len2����Ҫ��ʾ���ı��ĳ��ȣ�Ӣ��һ���ַ�һ�ֽڡ�����һ���������ֽ�    
						         ע��ȡ��ֵ���Ա��ı����ȴ󣬵����ܴ�����λ�����趨�ĳ���

*************************************************************************/



//10�ĳ˷������������ж�λ��
u32 HMI_Pow(u8 n)
{
	u32 result=1;	 
	while(n--)result*=10;    
	return result;
}	


//��ֵ���ͺ���
//USART_TypeDef* USARTx�� ѡ�񴮿������ע������ȳ�ʼ����ʹ�ܴ���
//u16 *data����λ��������λ��Ӧ�ĸı���ֵ����
//u8 len��*data����ĳ��ȡ�
//u16 Num����Ҫ��ʾ����ֵ��ע�⿪ͷ0����ʾ
//u8 len2����Ҫ��ʾ����ֵ��λ��
void HMI_SendNum(USART_TypeDef* USARTx,u8 *data,u8 len,u16 Num,u8 len2)
{
		u8 t;
 for(t=0;t<len;t++)
        {	
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,data[t]); 					
        }
for(t=0;t<len2;t++)	
{
           while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
           USART_SendData(USARTx,'0'+(Num/HMI_Pow(len2-t-1))%10); 


}
				
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0XFF);
              
       	
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0XFF);
             
       	
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0XFF);

}

//�ַ������ͺ�����HMI_SendText(USART_TypeDef* USARTx,u8 *data,u8 len,u8 *text,u8 len2)
//            USART_TypeDef* USARTx�� ѡ�񴮿������ע������ȳ�ʼ����ʹ�ܸô���
//            u16 *data����λ�����ı�λ��Ӧ�ĸı���ֵ���룬��"t0.txt="��"t1.txt="
//          	u8 len��*data����ĳ��ȡ���"t0.txt="����Ϊ7��
//            u8 *text����Ҫ���������ʾ���ı�
//            u8 len2����Ҫ��ʾ���ı��ĳ��ȣ�Ӣ��һ���ַ�һ�ֽڡ�����һ���������ֽ�    

void HMI_SendText(USART_TypeDef* USARTx,u8 *data,u8 len,u8 *text,u8 len2)
{
		u8 t;
    for(t=0;t<len;t++)
        {	
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,data[t]); 					
        }
				    while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0X22); 
   for(t=0;t<len2;t++)	
       {
           while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
           USART_SendData(USARTx,text[t]); 


       }
			 			while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0X22); 
				
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0XFF);
              
       	
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0XFF);
             
       	
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);
            USART_SendData(USARTx,0XFF);




}
