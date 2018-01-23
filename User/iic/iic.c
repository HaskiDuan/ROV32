#include "iic.h"

void I2C_GPIOconfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_I2C_Port, ENABLE);	/* ��GPIOʱ�� */

	GPIO_InitStructure.GPIO_Pin = I2C_SCL_Pin	 | I2C_SDA_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	/* ��©��� */
	GPIO_Init(I2C_Port, &GPIO_InitStructure);

	
}


void I2C_delay_ms(uint16_t ms)
{
		
   uint32_t i=5000*ms;  
   while(i) 
   { 
     i--; 
   }  
}


void I2C_delay(void)
{
		
   u8 i=5; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   }  
}

void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}  

void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
} 

uint8_t I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return 0;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;
	I2C_delay();
	if(SDA_read) return 0;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L;
	I2C_delay();
	return 1;
}

void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
} 

uint8_t I2C_WaitAck(void) 	 //����Ϊ:=1��ACK,=0��ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
	  I2C_delay();
      return 0;
	}
	SCL_L;
	I2C_delay();
	return 1;

}

void I2C_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}  

uint8_t I2C_ReadByte(void)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 

/*
�ɹ�����1
ʧ�ܷ���0
*/

uint8_t I2C_Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start())return 0;
    I2C_SendByte((SlaveAddress)|I2C_WR);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck()){I2C_Stop(); return 0;}
    I2C_SendByte(REG_Address);   //���õ���ʼ��ַ      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    I2C_delay_ms(1);
    return 1;
		
		
}

uint8_t I2C_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   
	unsigned char REG_data;     	
	if(!I2C_Start())return 0;
	I2C_SendByte(SlaveAddress|I2C_WR); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
	if(!I2C_WaitAck()){I2C_Stop(); return 0;}
	I2C_SendByte((u8) REG_Address);   //���õ���ʼ��ַ      
		
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return 0;
	}
		
	I2C_Start();
	I2C_SendByte(SlaveAddress|I2C_RD);
		
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return 0;
	}

	REG_data= I2C_ReadByte();
	I2C_NoAck();
	I2C_Stop();
	//return TRUE;
	return REG_data;
}		



uint8_t I2C_CheckDevice(uint8_t address)//1�ɹ� 0ʧ��
{
	uint8_t ack;
	if(!I2C_Start())
		return 0;
	I2C_SendByte((address)|I2C_WR);
	ack=I2C_WaitAck();
	I2C_Stop();
	return ack;
}

/*
����д��
�ɹ�����1��ʧ�ܷ���0

*/

uint8_t I2C_WriteBuffer(uint8_t addr, uint8_t * data,uint8_t len)
{
	uint8_t i;
	I2C_Start();
	I2C_SendByte(addr|I2C_WR);
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return 0;
	}
  for (i = 0; i < len; i++)
	{
			I2C_SendByte(data[i]);
			if(!I2C_WaitAck())
			{
				I2C_Stop();
				return 0;
			}
	}
	I2C_Stop();
    return 1;
}


uint8_t I2C_ReadBuffer(uint8_t addr, uint8_t* pBuffer, uint8_t readAddr, u16 NumByteToRead)
{
	
	if(!I2C_Start())return 0;
	
	I2C_SendByte(addr| I2C_WR);
	if (!I2C_WaitAck())
			{
				I2C_Stop();
				return 0;	/* MPU��Ӧ�� */
			}
			
	I2C_SendByte(readAddr);
			
	if (!I2C_WaitAck())
	{
		I2C_Stop();
		return 0;	/* MPU��Ӧ�� */
	}
	
	I2C_Start();
	
	I2C_SendByte(addr| I2C_RD);
	
	if (!I2C_WaitAck())
	{
		I2C_Stop();
		return 0;	
	}
	
	 while(NumByteToRead)
  {

		*pBuffer = I2C_ReadByte();
		pBuffer++;
		if(NumByteToRead > 1)
			I2C_Ack();
		else
    {
			I2C_NoAck();
			I2C_Stop();
    }
		NumByteToRead--;
  }
		I2C_Stop();
	return 1;
	
}


