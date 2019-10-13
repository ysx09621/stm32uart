#include "global.h"

uint16_t ADC_ConvertedValue[16] = {0};
float ADC_ConvertedValueLocal[16] = {0};

 static void ADCx_GPIO_Config(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;

 // 打开 ADC IO 端口时钟
   ADC_GPIO_APBxClock_FUN ( ADC_GPIOA_CLK, ENABLE );
	 ADC_GPIO_APBxClock_FUN ( ADC_GPIOB_CLK, ENABLE );
	 ADC_GPIO_APBxClock_FUN ( ADC_GPIOC_CLK, ENABLE );
 
  GPIO_InitStructure.GPIO_Pin = ADC_PIN1 |ADC_PIN2|ADC_PIN3|ADC_PIN4|ADC_PIN5|ADC_PIN6;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
  GPIO_Init(ADC_PORTC, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = ADC_PIN7|ADC_PIN8|ADC_PIN9|ADC_PIN10|ADC_PIN11|ADC_PIN12|ADC_PIN13|ADC_PIN14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(ADC_PORTB, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = ADC_PIN15|ADC_PIN16;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(ADC_PORTB, &GPIO_InitStructure);
 }
 
 
static void ADCx_Mode_Config(void)
{
 DMA_InitTypeDef DMA_InitStructure;
 ADC_InitTypeDef ADC_InitStructure;


  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
  ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
  
  DMA_DeInit(ADC_DMA_CHANNEL);
  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&( ADCx->DR ));
  
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
  
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  
  DMA_InitStructure.DMA_BufferSize = NOFCHANEL;
  
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  
  DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
  
  DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
  
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  
  ADC_InitStructure.ADC_ScanConvMode = ENABLE ;
  
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  
  ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;
  
  ADC_Init(ADCx, &ADC_InitStructure);
  
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL5, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL6, 6, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL7, 7, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL8, 8, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL9, 9, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL10, 10, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL11, 11, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL12, 12, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL13, 13, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL14, 14, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL15, 15, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL16, 16, ADC_SampleTime_55Cycles5);
	
  ADC_DMACmd(ADCx, ENABLE);
  
  ADC_Cmd(ADCx, ENABLE);
  
  ADC_ResetCalibration(ADCx);
  
  while (ADC_GetResetCalibrationStatus(ADCx));
  
  ADC_StartCalibration(ADCx);
  
  while (ADC_GetCalibrationStatus(ADCx));
  
  ADC_SoftwareStartConvCmd(ADCx, ENABLE);
 }

 void adc_init()
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}

void printf_adc_value(void)
{
	ADC_ConvertedValueLocal[0] =(float)  ADC_ConvertedValue[0]/4096*3.3;
  ADC_ConvertedValueLocal[1] =(float)  ADC_ConvertedValue[1]/4096*3.3;
  ADC_ConvertedValueLocal[2] =(float)  ADC_ConvertedValue[2]/4096*3.3;
  ADC_ConvertedValueLocal[3] =(float)  ADC_ConvertedValue[3]/4096*3.3;
  ADC_ConvertedValueLocal[4] =(float)  ADC_ConvertedValue[4]/4096*3.3;
	ADC_ConvertedValueLocal[5] =(float)  ADC_ConvertedValue[5]/4096*3.3;
  ADC_ConvertedValueLocal[6] =(float)  ADC_ConvertedValue[6]/4096*3.3;
  ADC_ConvertedValueLocal[7] =(float)  ADC_ConvertedValue[7]/4096*3.3;
  ADC_ConvertedValueLocal[8] =(float)  ADC_ConvertedValue[8]/4096*3.3;
  ADC_ConvertedValueLocal[9] =(float)  ADC_ConvertedValue[9]/4096*3.3;
	ADC_ConvertedValueLocal[10] =(float)  ADC_ConvertedValue[10]/4096*3.3;
  ADC_ConvertedValueLocal[11] =(float)  ADC_ConvertedValue[11]/4096*3.3;
  ADC_ConvertedValueLocal[12] =(float)  ADC_ConvertedValue[12]/4096*3.3;
  ADC_ConvertedValueLocal[13] =(float)  ADC_ConvertedValue[13]/4096*3.3;
  ADC_ConvertedValueLocal[14] =(float)  ADC_ConvertedValue[14]/4096*3.3;
  ADC_ConvertedValueLocal[15] =(float)  ADC_ConvertedValue[15]/4096*3.3;
  printf("\r\n CH1 value = %f V ",ADC_ConvertedValueLocal[0]);
  printf("\r\n CH2 value = %f V ",ADC_ConvertedValueLocal[1]);
  printf("\r\n CH3 value = %f V ",ADC_ConvertedValueLocal[2]);
  printf("\r\n CH4 value = %f V ",ADC_ConvertedValueLocal[3]);
  printf("\r\n CH5 value = %f V ",ADC_ConvertedValueLocal[4]);
  printf("\r\n CH6 value = %f V ",ADC_ConvertedValueLocal[5]);
  printf("\r\n CH7 value = %f V ",ADC_ConvertedValueLocal[6]);
  printf("\r\n CH8 value = %f V ",ADC_ConvertedValueLocal[7]);
  printf("\r\n CH9 value = %f V ",ADC_ConvertedValueLocal[8]);
  printf("\r\n CH10 value = %f V ",ADC_ConvertedValueLocal[9]);
  printf("\r\n CH11 value = %f V ",ADC_ConvertedValueLocal[10]);
  printf("\r\n CH12 value = %f V ",ADC_ConvertedValueLocal[11]);
  printf("\r\n CH13 value = %f V ",ADC_ConvertedValueLocal[12]);
  printf("\r\n CH14 value = %f V ",ADC_ConvertedValueLocal[13]);
  printf("\r\n CH15 value = %f V ",ADC_ConvertedValueLocal[14]);
	printf("\r\n CH16 value = %f V ",ADC_ConvertedValueLocal[15]);
 
  printf("\r\n\r\n");
}
