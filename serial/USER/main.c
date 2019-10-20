#include "global.h"
#define FLASH_BASE            ((uint32_t)0x08000000) 
int main(void)
{ 
SCB->VTOR = FLASH_BASE | 0x7000; /* Vector Table Relocation in Internal FLASH. */	
   SystemInit();	//配置系统时钟为 72M  
	bsp_init();

  while (1)
  {	 		
    if(TICK_2MS_EVENT == 1)
   	{

		TICK_2MS_EVENT = 0;
	}

	if(TICK_5MS_EVENT == 1)
   	{

		TICK_5MS_EVENT = 0;
	}

	if(TICK_10MS_EVENT == 1)
   	{

		TICK_10MS_EVENT = 0;
	}
		
	if(TICK_20MS_EVENT == 1)
	{
	
		TICK_20MS_EVENT = 0;
	}
			
	if(TICK_50MS_EVENT == 1)
	{
	
		TICK_50MS_EVENT = 0;
	}
				
	if(TICK_100MS_EVENT == 1)
	{
	  
		TICK_100MS_EVENT = 0;
	}
	
	if(TICK_1S_EVENT == 1)
	{
      printf_adc_value();
	    led_toggle();
		TICK_1S_EVENT = 0;
	}

	
		arm_receive();
		manage();
		
		
  }
}




