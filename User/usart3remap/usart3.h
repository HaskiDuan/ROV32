#ifndef _USART3_H_
#define _USART3_H_

#include "STM32F10x.h"

// 串口3-USART3重映射
#define  JY_USARTx                   USART3
#define  JY_USART_CLK                RCC_APB1Periph_USART3
#define  JY_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  JY_USART_BAUDRATE           9600

//AFIO宏定义
#define  JY_USART_AF_CLK             RCC_APB2Periph_AFIO
#define  JY_USART_AF_APBxClkCmd      RCC_APB2PeriphClockCmd


// USART GPIO 引脚宏定义
#define  JY_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  JY_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  JY_USART_TX_GPIO_PORT       GPIOC   
#define  JY_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  JY_USART_RX_GPIO_PORT       GPIOC
#define  JY_USART_RX_GPIO_PIN        GPIO_Pin_11

void JY_USART3_Remap_Config(void);

#endif

