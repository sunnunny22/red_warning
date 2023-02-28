#include "sys.h"
#include "hmi.h"	
/************************************************************************
           说明：本函数库为陶晶池串口屏数据发送指令库，包含以下函数
					 
1.数值发送函数：void HMI_SendNum(USART_TypeDef* USARTx,u8 *data,u8 len,u16 Num,u8 len2)
            USART_TypeDef* USARTx： 选择串口输出，注意必须先初始化、使能该串口
            u16 *data：上位机上数字位相应的改变数值代码，如"n0.val="、"n1.val="
						u8 len：*data代码的长度。如"n0.val="长度为7。
            u16 Num：需要串口输出显示的数值，注意开头0不显示，输出数字0开头会报错
            u8 len2：需要显示的数值的位数    注意不能大于上位机上设定的位数

2.字符串发送函数：void HMI_SendText(USART_TypeDef* USARTx,u8 *data,u8 len,u8 *text,u8 len2)
            USART_TypeDef* USARTx： 选择串口输出，注意必须先初始化、使能该串口
            u16 *data：上位机上文本位相应的改变数值代码，如"t0.txt="、"t1.txt="
          	u8 len：*data代码的长度。如"t0.txt="长度为7。
            u8 *text：需要串口输出显示的文本
            u8 len2：需要显示的文本的长度，英文一个字符一字节、汉字一个字两个字节    
						         注意取的值可以比文本长度大，但不能大于上位机上设定的长度

*************************************************************************/



//10的乘方函数，用于判断位数
u32 HMI_Pow(u8 n)
{
	u32 result=1;	 
	while(n--)result*=10;    
	return result;
}	


//数值发送函数
//USART_TypeDef* USARTx： 选择串口输出，注意必须先初始化、使能串口
//u16 *data：上位机上数字位相应的改变数值代码
//u8 len：*data代码的长度。
//u16 Num：需要显示的数值，注意开头0不显示
//u8 len2：需要显示的数值的位数
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

//字符串发送函数：HMI_SendText(USART_TypeDef* USARTx,u8 *data,u8 len,u8 *text,u8 len2)
//            USART_TypeDef* USARTx： 选择串口输出，注意必须先初始化、使能该串口
//            u16 *data：上位机上文本位相应的改变数值代码，如"t0.txt="、"t1.txt="
//          	u8 len：*data代码的长度。如"t0.txt="长度为7。
//            u8 *text：需要串口输出显示的文本
//            u8 len2：需要显示的文本的长度，英文一个字符一字节、汉字一个字两个字节    

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
