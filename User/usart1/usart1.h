#ifndef __USART1_H_
#define	__USART1_H_


#include "stm32f10x.h"
#include <stdio.h>

/** 
  * ���ں궨�壬��ͬ�Ĵ��ڹ��ص����ߺ�IO��һ������ֲʱ��Ҫ�޸��⼸����
	* 1-�޸�����ʱ�ӵĺ꣬uart1���ص�apb2���ߣ�����uart���ص�apb1����
	* 2-�޸�GPIO�ĺ�
  */
	
// ����1-USART1
#define  NEO_USARTx                   USART1
#define  NEO_USART_CLK                RCC_APB2Periph_USART1
#define  NEO_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  NEO_USART_BAUDRATE           115200

// USART GPIO ���ź궨��
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
