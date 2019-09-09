#include "bsp.h"
void module_init(void)
{
	SysTick_Config(72000000 / 1000);
	
	CreateQueue(&Uart1ReceiveQueue,uart1_rx_buff,1024);
	CreateQueue(&Uart4ReceiveQueue,uart4_rx_buff,1024);
	CreateQueue(&Uart4TransmitQueue,uart4_tx_buff,1024);
}

void bsp_init(void)
{
    module_init();	
	gpio_config();
	usart1_config();
	uart4_config();
	nvic_config();
	
}
