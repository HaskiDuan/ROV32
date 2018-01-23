#include "usart3.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_USART3_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}


void JY_USART3_Remap_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* enabel GPIO clock */
	JY_USART_GPIO_APBxClkCmd(JY_USART_GPIO_CLK,ENABLE);
	
	/* config USART3 clock */
	JY_USART_APBxClkCmd(JY_USART_CLK,ENABLE);
	
	/* enable remap clock */
	JY_USART_AF_APBxClkCmd(JY_USART_AF_CLK,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	
	/* USART3 partial remap GPIO cofig*/
	GPIO_InitStructure.GPIO_Pin = JY_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(JY_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = JY_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(JY_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = JY_USART_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(JY_USARTx, &USART_InitStructure);
	
	NVIC_USART3_Configuration();
	
	USART_ITConfig(JY_USARTx, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(JY_USARTx, ENABLE);
}


