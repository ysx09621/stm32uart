/*******************************************************************************
 Copyright (C) 2010 - All Rights Reserved

 �ļ�����:
 �������:
 ��Ȩ����:
 ��������:	2010��09��4�� 14:25:43
 �޸�����: 2010��05��4�� 14:25:43
 �����ʷ:
 Version:  1.0 : �����ļ�.
 *******************************************************************************/
#include "manage.h"
/*******************************************************************************
 �������� 	: void Manage_Receive(void)
 ����		: �������ݽ���
 ����      : None
 ���      : None
 ����      : None
 �޸�ʱ��	��2011��10��22�� 16:02:43
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
						if (x == 0x08)						//ɾ������
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
 �������� 	: void Manage(void)
 ����		: ����
 ����      : None
 ���      : None
 ����      : None
 �޸�ʱ��	��2011��09��26�� 09:02:43
 *******************************************************************************/

void manage(void)
{
	manage_receive();
}

/******************* (C) COPYRIGHT 2010 UNINEW *****END OF FILE****/
