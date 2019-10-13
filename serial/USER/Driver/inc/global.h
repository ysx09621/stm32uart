#ifndef _GLOBAL_H
#define _GLOBAL_H
#include <stdio.h>
#include "stm32f10x.h"

#include "usart.h"
#include <stdarg.h>
#include "stdlib.h"
#include "queue_api.h"
#include "manage.h"
#include "arm_receive.h"
#include "manage_handle.h"
#include "bsp.h"
#include "nvic.h"
#include "adc.h"

u16 byte_crc( u8 * crcData,u8 len);
//u16 crc16( u8 * crcData,u8 len);

void SetTimeSlickTick(void) ;

extern u8 TICK_2MS_EVENT ;
extern u8 TICK_5MS_EVENT ;
extern u8 TICK_10MS_EVENT ;
extern u8 TICK_20MS_EVENT ;
extern u8 TICK_50MS_EVENT ;
extern u8 TICK_100MS_EVENT ;
extern u8 TICK_1S_EVENT ;


#define DebugPrintf printf
#endif
