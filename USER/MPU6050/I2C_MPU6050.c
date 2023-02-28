/******************** (C) COPYRIGHT 2012  **************************

 * 硬件连接：-----------------
 *          |                 |
 *          |  PB6-I2C1_SCL		|
 *          |  PB7-I2C1_SDA   |
 *          |                 |
 *           -----------------
 * 库版本  ：ST3.5.0
 * 作者    ： Orange 
**********************************************************************************/
#include "I2C_MPU6050.h"

/*
 * 函数名：I2C_GPIO_Config
 * 描述  ：I2C1 I/O配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
		/* 使能与 I2C1 有关的时钟 */
	RCC_APB2PeriphClockCmd  (RCC_APB2Periph_GPIOB,ENABLE ); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);  

	 /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
}


/*
 * 函数名：I2C_Mode_Config
 * 描述  ：I2C 工作模式配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_Mode_Config(void)
{
	 /* Initialize the I2C1 according to the I2C_InitStructure members */ 
	I2C_InitTypeDef I2C_InitStructure; 
	 
	  /* I2C 配置 */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C ; 
	//I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; 
	//I2C_InitStructure.I2C_OwnAddress1 = SlaveAddress; 
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; 
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; 
	I2C_InitStructure.I2C_ClockSpeed = 50000; 


	/* I2C1 初始化 */
	I2C_Init(I2C1, &I2C_InitStructure);	   
	
	/* 使能 I2C1 */
	I2C_Cmd  (I2C1,ENABLE); 
	/*允许应答模式*/
	I2C_AcknowledgeConfig(I2C1, ENABLE);   
}
/***************************************************************************************/
/*
 * 函数名：I2C_MMA_Init
 * 描述  ：I2C 外设(MMA7455)初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void I2C_MPU6050_Init(void)
{	   
 	I2C_GPIO_Config();
	I2C_Mode_Config();
}  

/*
 * 函数名：I2C_ByteWrite
 * 描述  ：写一个字节到I2C设备寄存器中
 * 输入  ：REG_Address 接收数据的IIC设备寄存器的地址 
 *         REG_data 待写入的数据
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用
 */	
void I2C_ByteWrite(uint8_t REG_Address,uint8_t REG_data)
{

I2C_GenerateSTART(I2C1,ENABLE);

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Transmitter);

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

I2C_SendData(I2C1,REG_Address);

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

I2C_SendData(I2C1,REG_data);

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

I2C_GenerateSTOP(I2C1,ENABLE);

}


/*
 * 函数名：I2C_ByteRead
 * 描述  ：从IIC设备寄存器中读取一个字节
 * 输入  ：REG_Address 读取数据的寄存器的地址 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：内部调用 
*/
uint8_t I2C_ByteRead(uint8_t REG_Address)
{
uint8_t REG_data;

while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));

I2C_GenerateSTART(I2C1,ENABLE);//起始信号

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Transmitter);//发送设备地址+写信号

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));//

I2C_Cmd(I2C1,ENABLE);

I2C_SendData(I2C1,REG_Address);//发送存储单元地址，从0开始

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

I2C_GenerateSTART(I2C1,ENABLE);//起始信号

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

I2C_Send7bitAddress(I2C1,SlaveAddress,I2C_Direction_Receiver);//发送设备地址+读信号

while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

I2C_AcknowledgeConfig(I2C1,DISABLE);

I2C_GenerateSTOP(I2C1,ENABLE);

while(!(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)));

REG_data=I2C_ReceiveData(I2C1);//读出寄存器数据

return REG_data;

}

/*
 * 函数名：void InitMPU6050(void)
 * 描述  ：初始化Mpu6050
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void InitMPU6050(void)
{
	I2C_ByteWrite(PWR_MGMT_1,0x00);//解除休眠状态
	I2C_ByteWrite(SMPLRT_DIV,0x07);
	I2C_ByteWrite(CONFIG,0x06);
	I2C_ByteWrite(GYRO_CONFIG,0x18);
	I2C_ByteWrite(ACCEL_CONFIG,0x01);

}


/*
 * 函数名：GetData
 * 描述  ：获得16位数据
 * 输入  ：REG_Address 寄存器地址
 * 输出  ：返回寄存器数据
 * 调用  ：外部调用
 */

unsigned int GetData(unsigned char REG_Address)
{
	char H,L;
	H=I2C_ByteRead(REG_Address);
	L=I2C_ByteRead(REG_Address+1);
	return (H<<8)+L;   //合成数据
}

/******************* (C) COPYRIGHT 2012  *****END OF FILE************/








