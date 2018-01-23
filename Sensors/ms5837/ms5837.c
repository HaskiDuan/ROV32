#include "ms5837.h"

MS5837_ValueTypeDef MS5837={0,0,0,0.03};

#define  Pa 						100.0f
#define  bar  					0.001f
#define  mbar  					1.0f
#define  fluidDensity   997.0f//淡水密度997kg/m3  ，海水1029

uint16_t C[8];
uint32_t D1, D2;
int32_t Temp;
int32_t P;


/****************************
功能：给MS5837发送复位指令
参数：None
返回值：None
****************************/
static uint8_t MS5837_Reset(void) 
{
		return MS5837_WriteByte(MS5837_ADDRESS,0x1e, 0x1e);
}


/********************************
功能：计算压力值
参数：None
返回：None
*********************************/
static void MS5837_Calculate(void) 
{
	// Given C1-C6 and D1, D2, MS5837_Calculated Temp and P
	// Do conversion first and then second order temp compensation
	
	int32_t dT;
	int64_t SENS;
	int64_t OFF;
	int32_t SENSi; 
	int32_t OFFi;  
	int32_t Ti;    
	int64_t OFF2;
	int64_t SENS2;
	
	// Terms called
	dT = D2-(uint32_t)(C[5])*256l;
	SENS = (int64_t)(C[1])*32768l+((int64_t)(C[3])*dT)/256l;
	OFF = (int64_t)(C[2])*65536l+((int64_t)(C[4])*dT)/128l;
	
	
	//Temp and P conversion
	Temp = 2000l+(int64_t)(dT)*C[6]/8388608LL;
	P = (D1*SENS/(2097152l)-OFF)/(8192l);
	
	//Second order compensation
	if((Temp/100)<20){         //Low temp
		Ti = (3*(int64_t)(dT)*(int64_t)(dT))/(8589934592LL);
		OFFi = (3*(Temp-2000)*(Temp-2000))/2;
		SENSi = (5*(Temp-2000)*(Temp-2000))/8;
		if((Temp/100)<-15){    //Very low temp
			OFFi = OFFi+7*(Temp+1500l)*(Temp+1500l);
			SENSi = SENSi+4*(Temp+1500l)*(Temp+1500l);
		}
	}
	else if((Temp/100)>=20){    //High temp
		Ti = 2*(dT*dT)/(137438953472LL);
		OFFi = (1*(Temp-2000)*(Temp-2000))/16;
		SENSi = 0;
	}
	
	OFF2 = OFF-OFFi;           //Calculate pressure and temp second order
	SENS2 = SENS-SENSi;
	
	Temp = (Temp-Ti);
	P = (((D1*SENS2)/2097152l-OFF2)/8192l);
}
/********************************
功能：得到传感器中的原始数据
参数：None
返回：None
*********************************/

static void MS5837_Getdata(void)
{
	uint8_t bufe[3];
	MS5837_WriteByte(MS5837_ADDRESS,0x48, 0x00);
	I2C_delay_ms(20);
	MS5837_ReadBuffer(MS5837_ADDRESS,bufe,0x00, 3);	
	D1=bufe[0]<<16|bufe[1]<<8|bufe[2];
	MS5837_WriteByte(MS5837_ADDRESS,0x58, 0x00);
	I2C_delay_ms(20);
	MS5837_ReadBuffer(MS5837_ADDRESS,bufe,0x00, 3);	
	D2=bufe[0]<<16|bufe[1]<<8|bufe[2];	
}


/********************************
功能：检测MS5837是否连接成功
参数：None
返回：1成功 0失败
*********************************/

uint8_t MS5837_CheckDevice(void)
{
	return I2C_CheckDevice(MS5837_ADDRESS);
}


/********************************
功能：计算压强
参数：conversion:压强单位转换权值
返回：压强
*********************************/
float MS5837_pressure(float conversion) 
{
	return ((float)P)/10.0f*conversion;
}

/********************************
功能：计算温度
参数：None
返回：温度
*********************************/
float MS5837_temperature(void) 
{
	return Temp/100.0f;
}

/********************************
功能：计算深度
参数：None
返回：深度
*********************************/
float MS5837_depth(void) 
{
	return (MS5837_pressure(Pa)-101300)/(fluidDensity*9.80665);
}

/********************************
功能：设置水深修正值
参数：修正值
返回：None
*********************************/

void MS5837_SetOffset(float offset)
{
	MS5837.offset=offset;
}


/****************************
功能：初始化水深传感器
参数：None
返回值：None
****************************/
void MS5837_Init(void) 
{
	uint8_t buf[2];
	
	I2C_GPIOconfig();//初始化模拟IIC
	MS5837_Reset();
  MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xa0, 2);
  C[0] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xa2, 2);
  C[1] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xa4, 2);
  C[2] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xa6, 2);
  C[3] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xa8, 2);
  C[4] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xaa, 2);
  C[5] = buf[0] << 8 |buf[1]; 
    MS5837_ReadBuffer(MS5837_ADDRESS,buf,0xac, 2);
  C[6] = buf[0] << 8 |buf[1];
	MS5837_Read();
	MS5837_SetOffset(MS5837.depth);
}


/********************************
功能：得到传感器中的最终数据并将值赋给MS5837结构体
参数：None
返回：None
*********************************/
void MS5837_Read(void) 
{
	MS5837_Getdata();
	MS5837_Calculate();
	MS5837.temp=MS5837_temperature();
	MS5837.depth=MS5837_depth()-MS5837.offset;
	MS5837.pressure=MS5837_pressure(Pa);
}

