#include "global.h"

#define DEBUG_ENABLE


void PrintArmDirective(u8 vBuffer[], u8 vLength)
{
	//打印除心跳以外所接收到的信息.
	u8 pos = 0;
	//if (!(((vBuffer[2] == 1) && (vBuffer[3] == 7)) || ((vBuffer[2] == 1) && (vBuffer[3] == 0))))
	{
		DebugPrintf("\r\n");
		DebugPrintf("\r\nARM指令>>>>>>>> ");
		while (pos < vLength)
		{
			if (pos == 2)
			{
				DebugPrintf(" [");
			}
			else if (pos == vLength - 2)
			{
				DebugPrintf(" ] ");
			}

			DebugPrintf(" %02x", vBuffer[pos]);

			if (pos == 0)
			{
				DebugPrintf("(L)");
			}
			else if (pos == 1)
			{
				DebugPrintf("(G)");
			}
			else if (pos == 2)
			{
				DebugPrintf("(CMD)");
			}
//			else if (pos == vLength - 2)
//			{
//				DebugPrintf("(CK1)");
//			}
//			else if (pos == vLength - 1)
//			{
//				DebugPrintf("(CK2)");
//			}

			pos++;
		}
//		DebugPrintf("\r\n");
	}
}

void HandleSetCommandFrame(ArmFrameStructure *Frame)
{

	switch (Frame->CommandID)
	{
		case ARM_SYSTEM:
		{
//			ARM_SystemCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}
		case ARM_VIDEO:
			break;

		case ARM_RADIO:
		{
//			ARM_RadioCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}
		case ARM_AUDIO:
		{
//			AudioCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}
		case ARM_EQ:
		{
//			EQCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}
		case ARM_TOUCH:

			break;

		case ARM_KEY:
			break;

		case ARM_CAN:
		{
//			APP_IPC_Msg_Process(Frame);
			
			
			break;
		}

		default:
			break;
	}
}

/*******************************************************************************
 函数名称 	: void HandleReqCommandFrame(u8 vBuffer[],u8 vLength)
 *******************************************************************************/
void HandleReqCommandFrame(ArmFrameStructure *Frame)
{

	switch (Frame->CommandID)
	{
		case ARM_SYSTEM:
		{
		//	ARM_SystemReqCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}

		case ARM_RADIO:
		{
//			ARM_RadioReqCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}
		case ARM_AUDIO:
		{
//			AudioReqCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}

		case ARM_EQ:
		{
//			EQReqCmdHandle(Frame->SubCMD, Frame->pData, Frame->Length);
			break;
		}

		case ARM_CAN:
		{
			if (Frame->SubCMD == 0x01)
			{
				if (Frame->pData[0] == 0x0d)	//雷达信息
				{
//				
				}
				else if (Frame->pData[0] == 0x11)	//PM2.5信息
				{
//					Send_PM25_Info();
				}
			}
			else if (Frame->SubCMD == 0x03) //空调信息
			{
//			SendACInfo();
			}
			else if (Frame->SubCMD == 0x32) //360
			{
//				SendAVMInfo();
			}
			else if (Frame->SubCMD == 0x33) //胎压
			{
//			SendTMPSInfo();
			}
			else if (Frame->SubCMD == 0x30) //氛围灯
			{
//				SendAmbientLightLevel();
			}
			break;
		}

		default:
			break;
	}
		
	
}

//add by he 1612223
void HandleArmFrame(ArmFrameStructure *Frame)
{
	switch (Frame->GroupID)
	{
		case GID_CMD:
		{
			HandleSetCommandFrame(Frame);
			break;
		}

		case GID_REQ:
		{
			HandleReqCommandFrame(Frame);
			break;
		}

		case GID_EVT:
			break;

		case GID_ERR:
			break;

		default:
		{
			DebugPrintf("\r\n (HandleArmFrame)收到未能识别的ARM数据包=%x！ \r\n", Frame->GroupID);
		}
			break;
	}
}

/*******************************************************************************
 函数名称 	: void ARM_Receive(void)
 描述		: 接收DVD的数据
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2012年07月06日 11:53:43

length = 07~crc(end)
AA 55 07(L) 03(G) [ bb(CMD) cc dd ]  aa e3
AA 55 07 03 BB CC DD AA E3
 *******************************************************************************/
void arm_receive(void)
{
	unsigned char x;
	static unsigned char mState = 0;
	static u8 mBuffer[150];
	static unsigned char mFp = 0;

	if (GetQueneValue(&Uart4ReceiveQueue, &x))
	{
		switch (mState)
		{
			case 0:
			{
				if (x == ARMHEAD1)				//检查头第一个字节
				{
					mState = 1;
				}
				else
				{
					mState = 0;
				}

				break;
			}
			case 1:
			{
				if (x == ARMHEAD2)				//检查头第二个字节
				{
					mState = 2;
					mFp = 0;
				}
				else
				{
					mState = 0;
				}

				break;
			}
			case 2:						//数据第一字节
			{
				mBuffer[mFp++] = x;
				mState = 3;
				break;

				case 3:
				//数据字节
				mBuffer[mFp++] = x;

				if (mFp >= 150)
				{
					mState = 0;
				}

				if (mFp >= (mBuffer[0]))
				{
					//DebugPrintf("\r\n接收指令的长度=%d",mFp);
					bool isCheckOK = (bool) (byte_crc(mBuffer, (mBuffer[0])) == 0);

					if (isCheckOK)
					{
#ifdef DEBUG_ENABLE
						PrintArmDirective(mBuffer, mBuffer[0]);
#endif
						//采用下面方式 更直观 add by he 161223
						ArmFrameStructure ArmFarme;
						ArmFarme.GroupID = (ENUM_ARM_GROUP_ID) mBuffer[1];
						ArmFarme.CommandID = (ENUM_ARM_COMMAND_ID) mBuffer[2];
						ArmFarme.SubCMD = mBuffer[3];
						ArmFarme.pData = &mBuffer[4];
						ArmFarme.Length = mBuffer[0] - 6;
						HandleArmFrame(&ArmFarme);
					
					}
					else
					{
						DebugPrintf("/r/n校验NG");
					}

					mState = 0;
				}

				break;
			}
			default:
			{
				mState = 0;
				break;
			}
		}
	}
}

/**
 * 数据帧CMD为0X08时候相关的指令处理 如IPC信息等等
 */
void APP_IPC_Msg_Process(ArmFrameStructure *Frame)
{
	if (Frame->SubCMD == 0x02) //IPC信息
	{
//		u8 type = Frame->pData[0];
//		u8 subType = Frame->pData[1];
//		SendHostInfoToDashBoard(type, subType, &Frame->pData[2], Frame->Length - 2); //不再采用这种方式
	}
	else if (Frame->SubCMD == 0x03) //空调信息
	{
//		u8 type = Frame->pData[0];
//		u8 cmd = Frame->pData[1];
//		u8 action = Frame->pData[2];
	}
	else if (Frame->SubCMD == 0x06) //设置信息
	{

	}
	else if (Frame->SubCMD == 0x31) //DVR
	{
		if (Frame->pData[0] == 0x01) //虚拟按键
		{
//			u8 cmd = Frame->pData[1];

		}
		else if (Frame->pData[0] == 0x02) //坐标
		{

		}
	}
	else if (Frame->SubCMD == 0x32) //360
	{
////		u8 AVM_Switch = Frame->pData[0];
//		u8 cmd = Frame->pData[1];
////		u8 action = Frame->pData[2];

	}
	else if (Frame->SubCMD == 0x36) //turn by turn 导航
	{
//		API_StringCopy(Frame->pData, (u8*) &GPS_Info, sizeof(GPS_Info));

//		SET_TURN_TYPE(GPS_Info.TurnType);
//		SET_GUIDE_TYPE(GPS_Info.GuideType);
//		SET_TURN_DISTANCE(GPS_Info.TurnDistance);
//		SET_DEST_DISTANCE(GPS_Info.DestDistance);
//		SET_DVD5_TOWARDS(GPS_Info.DVD5_Towards);
//		SET_DVD5_CLOCK_GUIDE(GPS_Info.DVD5_ClockGuide);
//		SET_DVD5_GUIDE_TYPE(GPS_Info.DVD5_GuideType);
	}
	else if (Frame->SubCMD == 0x30) //bcm氛围灯
	{
//		Set_BCM_APL_FB(Frame->pData[0]);
//		Send_BCM_Info();
	}
	else if(Frame->SubCMD == 0x26)
	{
//		AcReadyFlag = Frame->pData[0];
//		if(AcReadyFlag == 0x01)
		{
//			OnAcValidInScreenOff();
		}
	}
}







