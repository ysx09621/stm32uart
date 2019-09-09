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
#include "manage.h"
/*******************************************************************************
 函数名称 	: void Manage_Receive(void)
 描述		: 管理数据接收
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2011年10月22日 16:02:43
 *******************************************************************************/

void manage_receive(void)
{
	unsigned char x;

//	static unsigned char mBuffer[UsartLength][BufferLength];
	static unsigned char mBuffer[UART_SEND_BUFFER_LENGTH];
	static unsigned char mFp = 0;
	static u8 mLength = 0;
	static u8 mState = 0;

	if (GetQueneValue(&Uart1ReceiveQueue, &x))
	{
		if (x == 0x0d)
		{
			Manage_Handle(mBuffer, mLength);
			mFp = 0;
			mLength = 0;
			mState = 0;
		}
		else
		{
			switch (mState)
			{
				case 0:
					if (x == 0x1b)
					{
						mState = 0x1b;
					}
					else
					{
						if (x == 0x08)						//删除操作
						{
							if (mFp > 0)
							{
								mFp--;
								mLength--;
								printf("%c%c%c", 0x1b, 0x5b, 0x44);
								printf(" ");
								printf("%c%c%c", 0x1b, 0x5b, 0x44);
							}
						}
						else
						{
							mBuffer[mFp++] = x;

							if (mFp > mLength)
							{
								mLength = mFp;
							}

							if (mFp >= UART_SEND_BUFFER_LENGTH)
							{
								mFp = 0;
								mLength = 0;
								mState = 0;
							}
							else
							{
								printf("%c", x);
							}
						}

					}

					break;

				case 0x1b:
					if (x == 0x5b)
					{
						mState = 0x5b;
					}
					else
					{
						mState = 0;
						mLength = 0;
						mFp = 0;
					}

					break;

				case 0x5b:
					switch (x)
					{
						case 0x44:
							if (mFp > 0)
							{
								mFp--;
								printf("%c%c%c", 0x1b, 0x5b, 0x44);
								mState = 0;
							}

							break;

						case 0x41:
						case 0x42:
						case 0x43:
							mState = 0;
							break;

						default:
							mState = 0;
							mLength = 0;
							mFp = 0;
							break;
					}

					break;
			}

		}

	}
}

/*******************************************************************************
 函数名称 	: void Manage(void)
 描述		: 管理
 输入      : None
 输出      : None
 返回      : None
 修改时间	：2011年09月26日 09:02:43
 *******************************************************************************/

void manage(void)
{
	manage_receive();
}

/******************* (C) COPYRIGHT 2010 UNINEW *****END OF FILE****/
