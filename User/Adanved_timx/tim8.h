#ifndef _TIM8_H_
#define _TIM8_H_

#include "stm32f10x.h"

/************�߼���ʱ��TIM�������壬ֻ��TIM1��TIM8************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������ʹ�ø߼����ƶ�ʱ��TIM1

#define            ADVANCE_TIM                   TIM8
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM8
// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            ADVANCE_TIM_PERIOD            (100-1)
#define            ADVANCE_TIM_PSC               (72-1)

#define            ADVANCE_TIM_IRQ               TIM8_UP_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM8_UP_IRQHandler

// TIM8 ����Ƚ�ͨ��CH1
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            ADVANCE_TIM_CH1_PORT          GPIOC
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_6

// TIM8 ����Ƚ�ͨ��CH2
#define            ADVANCE_TIM_CH2_PORT          GPIOC
#define            ADVANCE_TIM_CH2_PIN           GPIO_Pin_7

// TIM8 ����Ƚ�ͨ��CH3
#define            ADVANCE_TIM_CH3_PORT          GPIOC
#define            ADVANCE_TIM_CH3_PIN           GPIO_Pin_8

// TIM8 ����Ƚ�ͨ��CH4
#define            ADVANCE_TIM_CH4_PORT          GPIOC
#define            ADVANCE_TIM_CH4_PIN           GPIO_Pin_9

// TIM8 ����Ƚ�ͨ����ɲ��ͨ��
#define            ADVANCE_TIM_BKIN_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_BKIN_PORT          GPIOA
#define            ADVANCE_TIM_BKIN_PIN           GPIO_Pin_6

/**************************��������********************************/
void TIM8_Init(void);

#endif

