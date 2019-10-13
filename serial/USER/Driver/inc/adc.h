#ifndef _ADC_H_
#define _ADC_H_
#include "global.h"

 // ADC 宏定义
#define ADCx ADC1
#define ADC_APBxClock_FUN RCC_APB2PeriphClockCmd
#define ADC_CLK RCC_APB2Periph_ADC1

#define ADC_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define ADC_GPIOA_CLK RCC_APB2Periph_GPIOA
#define ADC_GPIOB_CLK RCC_APB2Periph_GPIOB
#define ADC_GPIOC_CLK RCC_APB2Periph_GPIOC
#define ADC_PORTC GPIOC
#define ADC_PORTB GPIOB
#define ADC_PORTA GPIOA
 // 转换通道个数
#define NOFCHANEL 16

#define ADC_PIN1 GPIO_Pin_0
#define ADC_CHANNEL1 ADC_Channel_10  //PC0

#define ADC_PIN2 GPIO_Pin_1
#define ADC_CHANNEL2 ADC_Channel_11  //PC1

#define ADC_PIN3 GPIO_Pin_2
#define ADC_CHANNEL3 ADC_Channel_12  //PC2

#define ADC_PIN4 GPIO_Pin_3
#define ADC_CHANNEL4 ADC_Channel_13  //PC3

#define ADC_PIN5 GPIO_Pin_4
#define ADC_CHANNEL5 ADC_Channel_14  //PC4

#define ADC_PIN6 GPIO_Pin_5
#define ADC_CHANNEL6 ADC_Channel_15  //PC5


#define ADC_PIN7 GPIO_Pin_0
#define ADC_CHANNEL7 ADC_Channel_0  //PA0

#define ADC_PIN8 GPIO_Pin_1
#define ADC_CHANNEL8 ADC_Channel_1  //PA1

#define ADC_PIN9 GPIO_Pin_2
#define ADC_CHANNEL9 ADC_Channel_2  //PA2

#define ADC_PIN10 GPIO_Pin_3
#define ADC_CHANNEL10 ADC_Channel_3  //PA3

#define ADC_PIN11 GPIO_Pin_4
#define ADC_CHANNEL11 ADC_Channel_4  //PA4

#define ADC_PIN12 GPIO_Pin_5
#define ADC_CHANNEL12 ADC_Channel_5  //PA5

#define ADC_PIN13 GPIO_Pin_6
#define ADC_CHANNEL13 ADC_Channel_6  //PA6

#define ADC_PIN14 GPIO_Pin_7
#define ADC_CHANNEL14 ADC_Channel_7  //PA7

#define ADC_PIN15 GPIO_Pin_0
#define ADC_CHANNEL15 ADC_Channel_8  //PB0

#define ADC_PIN16 GPIO_Pin_1
#define ADC_CHANNEL16 ADC_Channel_9  //PB1

// ADC1 对应DMA1 通道1, ADC3 对应DMA2 通道5, ADC2 没有DMA功能
#define ADC_DMA_CHANNEL DMA1_Channel1











void adc_init(void);
void printf_adc_value(void);
#endif
