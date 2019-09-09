#ifndef _MANAGE_HANDLE_H_
#define _MANAGE_HANDLE_H_
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#define UART_CMD_NUMBER	10
#ifdef CARConfig
	extern CAR_CONFIGURATION Car_Configuration;
#endif

void Manage_Help(void);
u8 AscllToHex(u8 x);
void Manage_Handle_perform(char const vCommand[], u8 vParameter[], u8 vValue[]);
void Manage_Handle(u8 vBuffer[], u8 vLength);

#endif
