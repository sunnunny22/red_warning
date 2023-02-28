#include"GPIO_Config.h"
void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;   //����	
  SystemInit();  //ϵͳ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//���ܸ��� IO ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //USART1ʱ��
	
	/************�������������********************/
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;          //�����������  ����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;              //GPIO PA0 ��  
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/************�������������********************/
	
	/************��������***********************/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10; //����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //��������
  GPIO_Init(GPIOA,&GPIO_InitStructure);   
	/************��������***********************/
	
	//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;  //ѡ����Ҫ���õ�IO��
		/*****************APB1ʱ������************************/	
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);	//TIM2 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE); //TIM3 ʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE); //TIM4 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_WWDG ,ENABLE);  //WWDG ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);  //SPI2 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE);   //USART2 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3  ,ENABLE);  //USART3 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1  ,ENABLE);   //I2C1 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C2  ,ENABLE);   //I2C2 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USB ,ENABLE);   //USB ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_CAN  ,ENABLE);  //CAN ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_BKP  ,ENABLE);  //BKP ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_PWR   ,ENABLE);  //PWR ʱ��
	/*****************APB1ʱ������************************/
	
	/*****************APB2ʱ������************************/	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//���ܸ��� IO ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA ʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //GPIOB ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //GPIOC ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //GPIOD ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);   //GPIOE ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 ,ENABLE);  //ADC1 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 ,ENABLE);   //ADC2 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 ,ENABLE);   //TIM1 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);   //SPI1 ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 ,ENABLE);  //USART1 ʱ��
	/*****************APB2ʱ������*************************/
	
	
	/*****************GPIO����*************************/
	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;  //ѡ����Ҫ���õ�IO��

		/*****************����ģʽ*************************/
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	           //ģ������   I2c,USART���ն�
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING ;	 //��������  ADCģ��ɼ�
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	           //��������  ������ʱĬ�ϵ͵�ƽ
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU ;	         //�������� ������ʱĬ�ϸߵ�ƽ
	 /*****************����ģʽ*************************/
	 
	 /*****************���ģʽ*************************/
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	 //��©���    0���Ƶ͵�ƽ�����1�Ȳ���Ҳ���ͣ�����̫������������
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�������    �ߵ�ƽ3.3  �͵�ƽ0
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD ;	 //���ÿ�©��� IC��SMBUS
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;	 //�����������  ����
//	  /*****************���ģʽ*************************/
	
		  /*****************����ٶ�*************************/
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;	  //���������� 2MHz
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	  //���������� 10MHz
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���������� 50MHz
		  /*****************����ٶ�*************************/
	
//	GPIO_Init(GPIOC,&GPIO_InitStructure); 

  /*****************GPIO����*************************/
}
	

