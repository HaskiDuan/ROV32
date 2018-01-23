/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart1.h"
#include "JY901.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0; 

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

// 串口中断服务函数
void NEO_USART_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(NEO_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(NEO_USARTx);
    USART_SendData(NEO_USARTx,ucTemp);    
	}	 
		
//	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
//  {   
//    USART_SendData(USART1, TxBuffer[TxCounter++]); 
//    if(TxCounter == count) 
//		{
//			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// 全部发送完成
//		}
//    USART_ClearITPendingBit(USART1, USART_IT_TXE); 
//  }
//	else if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  {
//		GetDataFromJY901((unsigned char)USART1->DR);//处理数据
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//  }
//	USART_ClearITPendingBit(USART1,USART_IT_ORE);

}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART3, TxBuffer[TxCounter++]); 
    if(TxCounter == count) 
		{
			USART_ITConfig(USART3, USART_IT_TXE, DISABLE);// 全部发送完成
		}
    USART_ClearITPendingBit(USART3, USART_IT_TXE); 
  }
	else if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
		GetDataFromJY901((unsigned char)USART3->DR);//处理数据
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART3,USART_IT_ORE);

}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
