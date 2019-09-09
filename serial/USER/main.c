#include "global.h"

int main(void)
{  
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

	    led_toggle();
		TICK_1S_EVENT = 0;
	}

	
		arm_receive();
		manage();
		
		
  }
}




