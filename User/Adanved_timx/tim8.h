#ifndef _TIM8_H_
#define _TIM8_H_

#include "stm32f10x.h"

/************高级定时器TIM参数定义，只限TIM1和TIM8************/
// 当使用不同的定时器的时候，对应的GPIO是不一样的，这点要注意
// 这里我们使用高级控制定时器TIM1

#define            ADVANCE_TIM                   TIM8
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM8
// PWM 信号的频率 F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            ADVANCE_TIM_PERIOD            (100-1)
#define            ADVANCE_TIM_PSC               (72-1)

#define            ADVANCE_TIM_IRQ               TIM8_UP_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM8_UP_IRQHandler

// TIM8 输出比较通道CH1
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            ADVANCE_TIM_CH1_PORT          GPIOC
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_6

// TIM8 输出比较通道CH2
#define            ADVANCE_TIM_CH2_PORT          GPIOC
#define            ADVANCE_TIM_CH2_PIN           GPIO_Pin_7

// TIM8 输出比较通道CH3
#define            ADVANCE_TIM_CH3_PORT          GPIOC
#define            ADVANCE_TIM_CH3_PIN           GPIO_Pin_8

// TIM8 输出比较通道CH4
#define            ADVANCE_TIM_CH4_PORT          GPIOC
#define            ADVANCE_TIM_CH4_PIN           GPIO_Pin_9

// TIM8 输出比较通道的刹车通道
#define            ADVANCE_TIM_BKIN_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_BKIN_PORT          GPIOA
#define            ADVANCE_TIM_BKIN_PIN           GPIO_Pin_6

/**************************函数声明********************************/
void TIM8_Init(void);

#endif

