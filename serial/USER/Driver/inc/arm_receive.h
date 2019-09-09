#ifndef _ARM_RECEIVE_H_
#define _ARM_RECEIVE_H_
#include "stm32f10x.h"
#include "queue_api.h"
#include <stdio.h>
#define ARMHEAD1 0xAA
#define ARMHEAD2 0x55
typedef enum
{
	GID_CMD = 1,
	GID_REQ,
	GID_EVT,
	GID_ERR
}ENUM_ARM_GROUP_ID;

typedef enum
{
	ARM_SYSTEM,
	ARM_VIDEO,
	ARM_RADIO,
	ARM_AUDIO,
	ARM_EQ,
	ARM_TOUCH,
	ARM_KEY,
	ARM_CAN,
}ENUM_ARM_COMMAND_ID;



typedef struct
{
  ENUM_ARM_GROUP_ID GroupID;
  ENUM_ARM_COMMAND_ID CommandID;
  u8 SubCMD;
  u8 *pData;
  u8 Length;
}ArmFrameStructure;

void PrintArmDirective(u8 vBuffer[], u8 vLength);
void HandleSetCommandFrame(ArmFrameStructure *Frame);
void HandleReqCommandFrame(ArmFrameStructure *Frame);
void HandleArmFrame(ArmFrameStructure *Frame);
void arm_receive(void);
void APP_IPC_Msg_Process(ArmFrameStructure *Frame);
#endif
