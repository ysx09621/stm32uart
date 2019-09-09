#include "global.h"
u8 TICK_2MS_EVENT = 0;
u8 TICK_5MS_EVENT = 0;
u8 TICK_10MS_EVENT = 0;
u8 TICK_20MS_EVENT = 0;
u8 TICK_50MS_EVENT = 0;
u8 TICK_100MS_EVENT = 0;
u8 TICK_1S_EVENT = 0;



#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

u8 byte_crc( u8 * crcData,u8 len)
{
	u16 crc = 0xffff;
	u8 i;
	u8 *ptr = crcData;
	while( len-- )
	{
		for(i = 0x80; i != 0; i = i >> 1)
		{
			if((crc & 0x8000) != 0)	 // 1
			{
				crc = crc << 1;
				crc = crc ^ 0x1021;
			}
			else	 // 0
			{
				crc = crc << 1;
			}
			if((*ptr & i) != 0)	// 1
			{
				crc = crc ^ 0x1021;
			} 
		}
		ptr++;
	}
	
	if( ((crc&0x00ff)== crcData[len-1]) && (  (crc&0xff00)>>8 == crcData[len-2] )  )
	{
		return 1;
	}	
	else
	{
		return 0;
	}
	
}


u16 crc16( u8 * crcData,u8 len)
{
	u16 crc = 0xffff;
	u8 i;
	u8 *ptr = crcData;
	while( len-- )
	{
		for(i = 0x80; i != 0; i = i >> 1)
		{
			if((crc & 0x8000) != 0)	 // 1
			{
				crc = crc << 1;
				crc = crc ^ 0x1021;
			}
			else	 // 0
			{
				crc = crc << 1;
			}
			if((*ptr & i) != 0)	// 1
			{
				crc = crc ^ 0x1021;
			} 
		}
		ptr++;
	}

	return crc;
}


void SetTimeSlickTick(void)
{
	u16 static count_by_1ms = 0;
	if(++count_by_1ms > 2000)
	{
		count_by_1ms = 0;		
	}
	else
	{
		if(count_by_1ms % 2 == 0)
		{
			TICK_2MS_EVENT = 1;	
		}
		if(count_by_1ms % 5 == 0)
		{
			TICK_5MS_EVENT = 1;	
		}
		if(count_by_1ms % 10 == 0)
		{
			TICK_10MS_EVENT = 1;	
		}

		if(count_by_1ms % 20 == 0)
		{
			TICK_20MS_EVENT = 1;	
		}
		
		if(count_by_1ms % 50 == 0)
		{
			TICK_50MS_EVENT = 1;	
		}

		if(count_by_1ms % 100 == 0)
		{
			TICK_100MS_EVENT = 1;	
		}
		
		if(count_by_1ms % 1000 == 0)
		{
			TICK_1S_EVENT = 1;	
		}
	}
}

