#ifndef _IIC_H_
#define _IIC_H_
#include "STM32F10x.h"

#define I2C_Port     	GPIOB			/* GPIO端口 */
#define RCC_I2C_Port 	RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define I2C_SCL_Pin		GPIO_Pin_6			/* 连接到SCL时钟线的GPIO */
#define I2C_SDA_Pin		GPIO_Pin_7			/* 连接到SDA数据线的GPIO */

#define SCL_H         I2C_Port->BSRR = I2C_SCL_Pin 
#define SCL_L         I2C_Port->BRR  = I2C_SCL_Pin 

#define SDA_H         I2C_Port->BSRR = I2C_SDA_Pin
#define SDA_L         I2C_Port->BRR =  I2C_SDA_Pin

#define SCL_read      I2C_Port->IDR  & I2C_SCL_Pin
#define SDA_read      I2C_Port->IDR  & I2C_SDA_Pin

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

void I2C_GPIOconfig(void);
void I2C_delay(void);
void I2C_delay_ms(uint16_t ms);
void I2C_Ack(void);
void I2C_NoAck(void);
uint8_t I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
uint8_t I2C_ReadByte(void);
uint8_t I2C_Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
uint8_t I2C_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);
uint8_t I2C_CheckDevice(uint8_t adress);
uint8_t I2C_WriteBuffer(uint8_t addr, uint8_t * data,uint8_t len);
uint8_t I2C_ReadBuffer(uint8_t addr, uint8_t* pBuffer, uint8_t readAddr, u16 NumByteToRead);

#endif
