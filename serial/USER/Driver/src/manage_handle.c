/*******************************************************************************
 Copyright (C) 2010 - All Rights Reserved

 文件名称:
 软件作者:
 版权所有:
 创建日期:	2010年09月4日 14:25:43
 修改日期: 2010年05月4日 14:25:43
 软件历史:
 Version:  1.0 : 创建文件.
 *******************************************************************************/
#include "global.h"
#define UART_CMD_NUMBER	10
#ifdef CARConfig
	extern CAR_CONFIGURATION Car_Configuration;
#endif
/*******************************************************************************
 函数名称 	: void Manage_Handle(u8 vBuffer[],u8 vLength)
 描述		: 处理接收到的管理数据
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2011年10月20日 09:02:43
 *******************************************************************************/
const unsigned char *(pHelpBuffer[]) =
				{
					"help = 帮助",
					"reset = 复位",
					"bl_set 1 or 0 = 背光开启/关闭",
					"bl_level val = 背光等级 val",
					"rev_enable = 倒车开启/关闭",
					"i2c_send subaddress val = i2c调试",
					"audiomute  1 or 0 = 静音开启/关闭",

					"start_radio",
					"start_music",
					"start_video", };

void Manage_Help(void)
{
	u8 i;

	for (i = 0; i < UART_CMD_NUMBER; i++)
	{
		printf("\r\n %s", pHelpBuffer[i]);
	}

	printf("\r\n ");
}

/*******************************************************************************
 函数名称 	: u8 AscllToHex(u8 x)
 描述		: 处理接收到的管理数据
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2011年12月05日 09:02:43
 *******************************************************************************/
u8 AscllToHex(u8 x)
{
	u8 y = 0;

	if (((x > 0x60) && (x < 0x67)) || ((x >= 0x30) && (x <= 0x39)))
	{
		if ((x >= 0x30) && (x <= 0x39))
		{
			y = x & 0x0f;
		}
		else
		{
			y = x - 0x57;
		}
	}
	else
	{
		y = 0;
	}

//printf("\r\nhex= 0x%x",y);
	return y;

}
/*******************************************************************************
 函数名称 	: void Manage_Handle(u8 vBuffer[],u8 vLength)
 描述		: 处理接收到的管理数据
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2011年12月05日 09:02:43
 *******************************************************************************/
void Manage_Handle_perform(char const vCommand[], u8 vParameter[], u8 vValue[])
{
	u8 x;
	u8 mBuffer[] =
					{ 0x00, 0x50 };

	if (strcmp(vCommand, "armreset") == 0)
	{
//		OnRestoreFactorySettings(0);
		return;
	}

	if (strcmp(vCommand, "bl_level") == 0)
	{
//		SetBackLightLevel(vParameter[0] - '0');
		return;
	}

	if (strcmp(vCommand, "beep") == 0)
	{
//		BeepSwitch((ENUM_ON_OFF)(vParameter[0] - '0'));
		return;
	}

	if (strcmp(vCommand, "bl_set") == 0)
	{
//		BackLightEnable(vParameter[0] - '0' != 0 ? 1 : 0);
		return;
	}

	if (strcmp(vCommand, "rev_enable") == 0)
	{
//		Reverse_DetStructure.isValid = vParameter[0] - '0' != 0 ? TRUE : FALSE;
		return;
	}

	if (strcmp(vCommand, "i2c_send") == 0)
	{
		//printf("\r\nvParameter= 0x%x,0x%x",vParameter[0],vParameter[1]);
		x = AscllToHex(vParameter[0]);
		x = (x << 4) | AscllToHex(vParameter[1]);
		mBuffer[0] = x;

		//printf("\r\nvValue= 0x%x,0x%x",vValue[0],vValue[1]);
		x = AscllToHex(vValue[0]);
		x = (x << 4) | AscllToHex(vValue[1]);
		mBuffer[1] = x;

		printf("\r\ni2c2= 0x%x,0x%x", mBuffer[0], mBuffer[1]);
//		I2C2_SendData(0x88, mBuffer, 2);
		printf("\r\n发送7419写指令");
		return;
	}

	if (strcmp(vCommand, "reset") == 0)
	{
//		MCU_SoftReset();
		 
		
		return;
	}

	if (strcmp(vCommand, "audiomute") == 0)
	{
//		AudioSoftMute(vParameter[0] - '0');
		return;
	}

	if (strcmp(vCommand, "help") == 0)
	{
    u8 buf[24] = {0};
		u8 i = 0;
		u16 crc = 0;
	//55 AA 07 03 BB CC DD AA E3
		Manage_Help();
		buf[i++] = 0x07;
		buf[i++] = 0x03;
		buf[i++] = 0xBB;
		buf[i++] = 0xCC;
		buf[i++] = 0xDD;
		crc = byte_crc(buf,i) ;
		buf[i++] = (crc & 0xFF00)>>8;
		buf[i++] = (crc & 0x00FF);
		uart4_send_byte(buf,i);
		return;
	}

	if (strcmp(vCommand, "AC") == 0)
	{
		//ACCmd = AC_CMD_AC;
//		currentACInfo.Switch = 1;
//		currentACInfo.AC= 1;


		return;
	}
	if (strcmp(vCommand, "ac") == 0)
	{
		//ACCmd = AC_CMD_AC;
//		currentACInfo.Switch = 0;
//		currentACInfo.AC= 0;


		return;
	}
	if (strcmp(vCommand, "usb") == 0)
	{
//		Key.CMD = CMD_START_MUSIC;
		return;
	}

	if (strcmp(vCommand, "radio") == 0)
	{
//		Key.CMD = CMD_START_RADIO;
		return;
	}

	if (strcmp(vCommand, "navi") == 0)
	{
//		Key.CMD = CMD_START_NAVI;
		return;
	}

	if (strcmp(vCommand, "cont") == 0)
	{
//		Key.CMD = CMD_START_BT_CONTACT;
		return;
	}

	if (strcmp(vCommand, "boot") == 0)
	{
//		SetArmBootProgress(ARM_TOTALLY_READY);
		return;
	}

	if (strcmp(vCommand, "logon") == 0)
	{
		return;
	}
	if (strcmp(vCommand, "logon") == 0)
	{
		return;
	}
	if (strcmp(vCommand, "reverseon") == 0)
	{
		
		return;
	}
	if (strcmp(vCommand, "reverseoff") == 0)
	{
		
		return;
	}
	if (strcmp(vCommand, "ww1") == 0)
	{
//		Car_Configuration.naviflag = 0x01;
//		SendCarConfigurationToApp();

		return;
	}
	if (strcmp(vCommand, "ww0") == 0)
	{
//		Car_Configuration.naviflag = 0x00;
//		SendCarConfigurationToApp();

		return;
	}
	
	if (strcmp(vCommand, "tftreset") == 0)
	{
//		CoreBoardPower_Reset();
		return;
	}
	if (strlen(vCommand) > 0)
	{
		printf("\r\n\r\n 无此 '%s' 命令，请核对命令输入！\r\n", vCommand);
	}
}

/*******************************************************************************
 函数名称 	: void Manage_Handle(u8 vBuffer[],u8 vLength)
 描述		: 处理接收到的管理数据
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2011年09月26日 09:02:43
 *******************************************************************************/
void Manage_Handle(u8 vBuffer[], u8 vLength)
{
	u8 mType = 0;
	u8 i, j;
	char mCommand[32];
	u8 mParameter[32];
	u8 mValue[32];
	u8 mState = 0;

	for (i = 0; i < 32; i++)
	{
		mCommand[i] = 0;
		mParameter[i] = 0;
		mValue[i] = 0;
	}

	for (i = 0, j = 0; i < vLength; i++)
	{
		switch (mType)
		{
			case 0:
			if ((vBuffer[i] == ' '))
			{
				mType++;
				mState = 1;
				j = 0;
			}
			else
			{
				mCommand[j++] = vBuffer[i];
			}

				break;

			case 1:
			if ((vBuffer[i] == ' ') && (mState == 0))
			{
				mType++;
				mState = 1;
				j = 0;
			}
			else
			{
				if (vBuffer[i] != ' ')
				{
					mParameter[j++] = vBuffer[i];
					mState = 0;
				}
			}

				break;

			case 2:
			if ((vBuffer[i] == ' ') && (mState == 0))
			{
				mType++;
				mState = 1;
				break;
			}
			else
			{
				if (vBuffer[i] != ' ')
				{
					mValue[j++] = vBuffer[i];
					mState = 0;
				}
			}

				break;

			case 3:
			if ((vBuffer[i] == ' ') && (mState == 0))
			{
				mState = 4;
			}

				break;
		}

		if (mState == 4)
		{
			break;
		}
	}

	printf("\r\n");
	Manage_Handle_perform(mCommand, mParameter, mValue);
	printf("\r\n MCU > ");
}

/******************* (C) COPYRIGHT 2010 UNINEW *****END OF FILE****/
