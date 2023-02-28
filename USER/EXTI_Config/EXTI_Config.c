#include"EXTI_Config.h"
void EXTI_Config(void)
{
  	EXTI_InitTypeDef EXTI_InitStructure; 
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); //�ж�������0
	
	 /**************EXTI����*********************/ 
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;    //PA0��������PE0  
	  EXTI_InitStructure.EXTI_LineCmd=ENABLE;      //����ʹ��
	
	 /**************�ж�ģʽ*********************/ 
	  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;  //���� EXTI ��·Ϊ�ж�����
//	  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Event;  //  ���� EXTI ��·Ϊ�¼�����
	/**************�ж�ģʽ*********************/ 
	
		/**************����ģʽ*********************/ 
	  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;//����������·������Ϊ�ж�����
//	  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling ;//����������·�½���Ϊ�ж�����
//	  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling ;//����������·�����غ��½���Ϊ�ж�����
	  /**************����ģʽ*********************/ 
	
	
	  EXTI_Init(&EXTI_InitStructure);
	/**************EXTI����*********************/
}
void EXTI_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;   //����	
  SystemInit();  //ϵͳ����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//���ܸ��� IO ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC ʱ��
	
	/************�ж����������********************/
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;          //��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;              //GPIO PA0 ��    
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/************�ж����������********************/
	
		/************��********************/
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All; //�������ж˿ڵ�����  
   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//�������ٶ�50MHZ	
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�������ģʽ
   GPIO_Init(GPIOC,&GPIO_InitStructure);     //��ʼ������Ķ˿�
   GPIO_SetBits(GPIOC,GPIO_Pin_All);
}
void EXTI_NVIC_Config(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
	  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  //��ռ���ȼ� 1 λ,�����ȼ� 3 λ
	  NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;   //ʹ�ܻ���ʧ��ָ���� IRQ ͨ������ǲ�һ��  
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //��Ӧ���ȼ�Ϊ0
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //ʹ��
		NVIC_Init(&NVIC_InitStructure); 
	
}
void EXTI_INIT(void)
{
   EXTI_GPIO_Config();	
   EXTI_Config();
   EXTI_NVIC_Config();
}

