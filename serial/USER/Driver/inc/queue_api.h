#ifndef QUEUE_API_H
#define QUEUE_API_H
#include "stm32f10x.h"
#include <stdio.h>
typedef struct
{
	u8 * pBase;
	u32 front;
	u32 rear;
	u32 maxsize;
	u32 max_frame_length;
	u8  valid_frame_length[1024]; 
}QUEUE,*PQUEUE;
extern QUEUE Uart1ReceiveQueue;;
extern u8 uart1_rx_buff[1024];
extern QUEUE Uart4ReceiveQueue;;
extern QUEUE Uart4TransmitQueue;;
extern u8 uart4_rx_buff[1024];
extern u8 uart4_tx_buff[1024];

void API_StringCopy(unsigned char *pSrc, unsigned char *pTarg, unsigned char cSize);
	
void CreateQueue(PQUEUE Q, u8 array[], u16 size);

/***********************************************
 Function: Print the stack element;
 ************************************************/
void TraverseQueue(PQUEUE Q);


bool IsQueueFull(PQUEUE Q);


bool IsQueueEmpty(PQUEUE Q);


void ClearQueue(PQUEUE Q);


/*******************************************************************************
 �������� 	: u8 InsertQueueValue
 ����		: �����в���ֵ
 ����      : Q ��������Ķ��е�ַ val : Ҫ�����ֵ
 ���      : None
 ����      : true:����ɹ� false:����ʧ��
 *******************************************************************************/
bool InsertQueueValue(PQUEUE Q, u8 val);


/*******************************************************************************
 �������� 	: u8 GetQueneValue
 ����		: �Ӷ���ȡֵ
 ����      : Q �����е�ַ
 ���      : val : ȡ����ֵ
 ����      : true:�ɹ� false:ʧ��
 *******************************************************************************/
bool GetQueneValue(PQUEUE Q, u8 *val);


void CreateQueueForArray(PQUEUE Q, u8 *p_array, u16 depth, u16 max_frame_length);


/*******************************************************************************
 �������� 	: u8 InsertQueueValue
 ����		: �����в���ֵ
 ����      : Q ��������Ķ��е�ַ val : Ҫ�����ֵ
 ���      : None
 ����      : true:����ɹ� false:����ʧ��
 *******************************************************************************/
bool InsertQueueArray(PQUEUE Q, u8 *p_array, u8 size);


/*******************************************************************************
 �������� 	: u8 GetQueneValue
 ����		: �Ӷ���ȡֵ
 ����      : Q �����е�ַ
 ���      : val : ȡ����ֵ
 ����      : true:�ɹ� false:ʧ��
 *******************************************************************************/
bool GetQueneArray(PQUEUE Q, u8 *p_array, u8 *size);

#endif
