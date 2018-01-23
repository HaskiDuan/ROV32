#include "stm32f10x.h"
#include "usart1.h"
#include "usart3.h"
#include "iic.h"
#include "ms5837.h"
#include "JY901.h"
#include "tim3.h"
#include "mavlink.h"


int main(void)
{	
  char str[100];
	/*初始化USART 115200 8-N-1，中断接收*/
  USART1_Config();
	I2C_GPIOconfig();
	JY_USART3_Remap_Config();
	TIM3_Init();
		
	TIM_SetCompare1(GENERAL_TIM, 100);
	TIM_SetCompare2(GENERAL_TIM, 20);
	TIM_SetCompare3(GENERAL_TIM, 40);
	TIM_SetCompare4(GENERAL_TIM, 2);
	
	while(!(MS5837_CheckDevice()))
	{
		sprintf(str,"MS5837 disconnected\n");
		Usart_SendString(NEO_USARTx,str);
	}
	
	sprintf(str,"MS5837 connected\n");
	Usart_SendString(NEO_USARTx,str);

	MS5837_Init();
		
  while(1)
	{	
		MS5837_Read();
		sprintf(str,"temp=%f,depth=%f,pressure=%f,offset=%f\n",MS5837.temp,MS5837.depth,MS5837.pressure,MS5837.offset);
		Usart_SendString(NEO_USARTx,str);
		
		sprintf(str,"Gyro:%.3f %.3f %.3f\r\n",(float)JY901_Gyro.w[0]/32768*2000,(float)JY901_Gyro.w[1]/32768*2000,(float)JY901_Gyro.w[2]/32768*2000);
		Usart_SendString(NEO_USARTx,str);
		
		sprintf(str,"Angle:%.3f %.3f %.3f\r\n",(float)JY901_Angle.Angle[0]/32768*180,(float)JY901_Angle.Angle[1]/32768*180,(float)JY901_Angle.Angle[2]/32768*180);
		Usart_SendString(NEO_USARTx,str);
		
		I2C_delay_ms(2000);
	}	
}

