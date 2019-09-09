/*******************************************************************************
 by hesheng
 *******************************************************************************/
#include "global.h"
#define DebugPrintf printf


QUEUE Uart1ReceiveQueue;

QUEUE Uart4TransmitQueue;
QUEUE Uart4ReceiveQueue;
u8 uart1_rx_buff[1024];
u8 uart4_rx_buff[1024];
u8 uart4_tx_buff[1024];

void API_StringCopy(unsigned char *pSrc, unsigned char *pTarg, unsigned char cSize)
{
	unsigned char i;

	for (i = 0; i < cSize; i++)
	{
		(*pTarg++) = ((*pSrc++));
	}
}

void CreateQueue(PQUEUE Q, u8 array[], u16 size)
{
	Q->pBase = array;

	if (NULL == Q->pBase)
	{
		DebugPrintf("Memory allocation failure");
	}

	Q->front = 0;         //��ʼ������
	Q->rear = 0;
	Q->maxsize = size;
}

/***********************************************
 Function: Print the stack element;
 ************************************************/
void TraverseQueue(PQUEUE Q)
{
	int i = Q->front;
	DebugPrintf("���е�Ԫ����:\n");
	while (i % Q->maxsize != Q->rear)
	{
		DebugPrintf("%d ", Q->pBase[i]);
		i++;
	}
	DebugPrintf("\n");
}

bool IsQueueFull(PQUEUE Q)
{
	if (Q->front == (Q->rear + 1) % Q->maxsize)    //�ж�ѭ�������Ƿ�������һ��Ԥ���ռ䲻��
		return TRUE;
	else
		return FALSE;
}

bool IsQueueEmpty(PQUEUE Q)
{
	if (Q->front == Q->rear)    //�ж��Ƿ�Ϊ��
		return TRUE;
	else
		return FALSE;
}

void ClearQueue(PQUEUE Q)
{
	Q->front = Q->rear = 0;
}

/*******************************************************************************
 �������� 	: u8 InsertQueueValue
 ����		: �����в���ֵ
 ����      : Q ��������Ķ��е�ַ val : Ҫ�����ֵ
 ���      : None
 ����      : true:����ɹ� false:����ʧ��
 *******************************************************************************/
bool InsertQueueValue(PQUEUE Q, u8 val)
{
	if (IsQueueFull(Q))
	{
		DebugPrintf("\r\n ���в�������ʧ��");
		return FALSE;
	}
	else
	{
		Q->pBase[Q->rear] = val;
		Q->rear = (Q->rear + 1) % Q->maxsize;
		return TRUE;
	}
}

/*******************************************************************************
 �������� 	: u8 GetQueneValue
 ����		: �Ӷ���ȡֵ
 ����      : Q �����е�ַ
 ���      : val : ȡ����ֵ
 ����      : true:�ɹ� false:ʧ��
 *******************************************************************************/
bool GetQueneValue(PQUEUE Q, u8 *val)
{
	if (IsQueueEmpty(Q))
	{
		return FALSE;
	}
	else
	{
		*val = Q->pBase[Q->front];
		Q->front = (Q->front + 1) % Q->maxsize;
		return TRUE;
	}
}

void CreateQueueForArray(PQUEUE Q, u8 *p_array, u16 depth, u16 max_frame_length)
{
	Q->pBase = p_array;

	if (NULL == Q->pBase)
	{
		printf("Memory allocation failure");
	}

	Q->front = 0;         //��ʼ������
	Q->rear = 0;
	Q->maxsize = depth;
	Q->max_frame_length = max_frame_length;

}

/*******************************************************************************
 �������� 	: u8 InsertQueueValue
 ����		: �����в���ֵ
 ����      : Q ��������Ķ��е�ַ val : Ҫ�����ֵ
 ���      : None
 ����      : true:����ɹ� false:����ʧ��
 *******************************************************************************/
bool InsertQueueArray(PQUEUE Q, u8 *p_array, u8 size)
{
	if (IsQueueFull(Q))
	{
		DebugPrintf("\r\n ���в�������ʧ��");
		return FALSE;
	}
	else
	{
//		Q->pBase[Q->rear] = val;
		API_StringCopy(p_array, Q->pBase + (Q->rear) * Q->max_frame_length, size);
		Q->valid_frame_length[Q->rear] = size;
		Q->rear = (Q->rear + 1) % Q->maxsize;
		return TRUE;
	}
}

/*******************************************************************************
 �������� 	: u8 GetQueneValue
 ����		: �Ӷ���ȡֵ
 ����      : Q �����е�ַ
 ���      : val : ȡ����ֵ
 ����      : true:�ɹ� false:ʧ��
 *******************************************************************************/
bool GetQueneArray(PQUEUE Q, u8 *p_array, u8 *size)
{
	if (IsQueueEmpty(Q))
	{
		return FALSE;
	}
	else
	{
//		*val = Q->pBase[Q->front];
		*size = Q->valid_frame_length[Q->front];
		API_StringCopy(Q->pBase + (Q->front) * Q->max_frame_length, p_array, *size);

		Q->front = (Q->front + 1) % Q->maxsize;
		return TRUE;
	}
}
