

/*
//�������ҳ�Ʒ
//����ϵ�п�����Ӧ�ó���
//��ע΢�Ź��ںţ����ҵ���
//���ҿ������������� www.DoYoung.net/YT 
//������ѿ����н�ѧ��Ƶ�����ؼ������ϣ�������������
//�������ݾ��� ����������ҳ www.doyoung.net
*/

/*
���޸���־��
1-201708202309 ������


*/



#include "i2c.h"


void I2C_GPIO_Init(void){ //I2C�ӿڳ�ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); //����I2C���� 
    GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA; //ѡ��˿ں�                      
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; //ѡ��IO�ӿڹ�����ʽ       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(I2CPORT, &GPIO_InitStructure);
}

void I2C_Configuration(void){ //I2C��ʼ��
	I2C_InitTypeDef  I2C_InitStructure;
	I2C_GPIO_Init(); //������GPIO�ӿڵ�״̬
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//����ΪI2Cģʽ
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = HostAddress; //������ַ���ӻ������ô˵�ַ��
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//����Ӧ��
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //7λ��ַģʽ
	I2C_InitStructure.I2C_ClockSpeed = BusSpeed; //�����ٶ����� 	
	I2C_Init(I2C1,&I2C_InitStructure);
	I2C_Cmd(I2C1,ENABLE);//����I2C					
}

void I2C_SAND_BUFFER(u8 SlaveAddr,u8 WriteAddr,u8* pBuffer,u16 NumByteToWrite){ //I2C�������ݴ���������ַ���ڲ���ַ���Ĵ�����������
	I2C_GenerateSTART(I2C1,ENABLE);//������ʼλ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //���EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Transmitter);//����������ַ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//���EV6
	I2C_SendData(I2C1,WriteAddr); //�ڲ����ܵ�ַ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//��λ�Ĵ����ǿգ����ݼĴ����ѿգ�����EV8���������ݵ�DR��������¼�
	while(NumByteToWrite--){ //ѭ����������	
		I2C_SendData(I2C1,*pBuffer); //��������
		pBuffer++; //����ָ����λ
		while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));//���EV8
	}
	I2C_GenerateSTOP(I2C1,ENABLE);//����ֹͣ�ź�
}
void I2C_SAND_BYTE(u8 SlaveAddr,u8 writeAddr,u8 pBuffer){ //I2C����һ���ֽڣ��ӵ�ַ���ڲ���ַ�����ݣ�
	I2C_GenerateSTART(I2C1,ENABLE); //���Ϳ�ʼ�ź�
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //�ȴ����	
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); //���ʹ�������ַ��״̬��д�룩
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //�ȴ����	
	I2C_SendData(I2C1,writeAddr); //���ʹ������ڲ��Ĵ�����ַ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�ȴ����	
	I2C_SendData(I2C1,pBuffer); //����Ҫд�������
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //�ȴ����	
	I2C_GenerateSTOP(I2C1,ENABLE); //���ͽ����ź�
}
void I2C_READ_BUFFER(u8 SlaveAddr,u8 readAddr,u8* pBuffer,u16 NumByteToRead){ //I2C��ȡ���ݴ���������ַ���Ĵ������ڲ���ַ��������
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);//�����ź�
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));	//��� EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); //д��������ַ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//��� EV6
	I2C_Cmd(I2C1,ENABLE);
	I2C_SendData(I2C1,readAddr); //���Ͷ��ĵ�ַ
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //��� EV8
	I2C_GenerateSTART(I2C1,ENABLE); //�����ź�
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); //��� EV5
	I2C_Send7bitAddress(I2C1,SlaveAddr,I2C_Direction_Receiver); //��������ַ����������Ϊ��
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); //���EV6
	while(NumByteToRead){
		if(NumByteToRead == 1){ //ֻʣ�����һ������ʱ���� if ���
			I2C_AcknowledgeConfig(I2C1,DISABLE); //�����һ������ʱ�ر�Ӧ��λ
			I2C_GenerateSTOP(I2C1,ENABLE);	//���һ������ʱʹ��ֹͣλ
		}
		if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){ //��ȡ����
			*pBuffer = I2C_ReceiveData(I2C1);//���ÿ⺯��������ȡ���� pBuffer
			pBuffer++; //ָ����λ
			NumByteToRead--; //�ֽ����� 1 
		}
	}
	I2C_AcknowledgeConfig(I2C1,ENABLE);
}
u8 I2C_READ_BYTE(u8 SlaveAddr,u8 readAddr){ //I2C��ȡһ���ֽ�
	u8 a;
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Transmitter); 
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_Cmd(I2C1,ENABLE);
	I2C_SendData(I2C1,readAddr);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTART(I2C1,ENABLE);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1,SlaveAddr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	I2C_AcknowledgeConfig(I2C1,DISABLE); //�����һ������ʱ�ر�Ӧ��λ
	I2C_GenerateSTOP(I2C1,ENABLE);	//���һ������ʱʹ��ֹͣλ
	a = I2C_ReceiveData(I2C1);
	return a;
}


 
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/


/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/
