#ifndef __USART1_H_
#define	__USART1_H_


#include "stm32f10x.h"
#include <stdio.h>

/** 
  * 串口宏定义，不同的串口挂载的总线和IO不一样，移植时需要修改这几个宏
	* 1-修改总线时钟的宏，uart1挂载到apb2总线，其他uart挂载到apb1总线
	* 2-修改GPIO的宏
  */
	
// 串口1-USART1
#define  NEO_USARTx                   USART1
#define  NEO_USART_CLK                RCC_APB2Periph_USART1
#define  NEO_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  NEO_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  NEO_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  NEO_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  NEO_USART_TX_GPIO_PORT       GPIOA   
#define  NEO_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  NEO_USART_RX_GPIO_PORT       GPIOA
#define  NEO_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  NEO_USART_IRQ                USART1_IRQn
#define  NEO_USART_IRQHandler         USART1_IRQHandler

void USART1_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART_H */
