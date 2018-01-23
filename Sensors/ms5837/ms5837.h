#ifndef  MS5837_H
#define  MS5837_H
#include "stm32f10x.h"
#include "iic.h"


#define     MS5837_ADDRESS		    0xec                      //0x76左移一位，写地址

#define 		MS5837_ReadBuffer			I2C_ReadBuffer
#define			MS5837_WriteBuffer		I2C_WriteBuffer
#define			MS5837_ReadByte				I2C_Single_Read
#define			MS5837_WriteByte			I2C_Single_Write

typedef struct 
{
	float depth;
	float temp;
	float pressure;
	float offset;
}MS5837_ValueTypeDef;


extern MS5837_ValueTypeDef MS5837;   //外部传感器数据

uint8_t MS5837_CheckDevice(void);//1成功 0失败
void MS5837_Init(void) ;
void MS5837_Read(void) ;
float MS5837_pressure(float conversion) ;
float MS5837_temperature(void) ;
float MS5837_depth(void) ;
void MS5837_SetOffset(float offset);
#endif

