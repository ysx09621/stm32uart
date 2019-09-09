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

	Q->front = 0;         //初始化参数
	Q->rear = 0;
	Q->maxsize = size;
}

/***********************************************
 Function: Print the stack element;
 ************************************************/
void TraverseQueue(PQUEUE Q)
{
	int i = Q->front;
	DebugPrintf("队中的元素是:\n");
	while (i % Q->maxsize != Q->rear)
	{
		DebugPrintf("%d ", Q->pBase[i]);
		i++;
	}
	DebugPrintf("\n");
}

bool IsQueueFull(PQUEUE Q)
{
	if (Q->front == (Q->rear + 1) % Q->maxsize)    //判断循环链表是否满，留一个预留空间不用
		return TRUE;
	else
		return FALSE;
}

bool IsQueueEmpty(PQUEUE Q)
{
	if (Q->front == Q->rear)    //判断是否为空
		return TRUE;
	else
		return FALSE;
}

void ClearQueue(PQUEUE Q)
{
	Q->front = Q->rear = 0;
}

/*******************************************************************************
 函数名称 	: u8 InsertQueueValue
 描述		: 往队列插入值
 输入      : Q ：待插入的队列地址 val : 要插入的值
 输出      : None
 返回      : true:插入成功 false:插入失败
 *******************************************************************************/
bool InsertQueueValue(PQUEUE Q, u8 val)
{
	if (IsQueueFull(Q))
	{
		DebugPrintf("\r\n 队列插入数据失败");
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
 函数名称 	: u8 GetQueneValue
 描述		: 从队列取值
 输入      : Q ：队列地址
 输出      : val : 取出的值
 返回      : true:成功 false:失败
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

	Q->front = 0;         //初始化参数
	Q->rear = 0;
	Q->maxsize = depth;
	Q->max_frame_length = max_frame_length;

}

/*******************************************************************************
 函数名称 	: u8 InsertQueueValue
 描述		: 往队列插入值
 输入      : Q ：待插入的队列地址 val : 要插入的值
 输出      : None
 返回      : true:插入成功 false:插入失败
 *******************************************************************************/
bool InsertQueueArray(PQUEUE Q, u8 *p_array, u8 size)
{
	if (IsQueueFull(Q))
	{
		DebugPrintf("\r\n 队列插入数组失败");
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
 函数名称 	: u8 GetQueneValue
 描述		: 从队列取值
 输入      : Q ：队列地址
 输出      : val : 取出的值
 返回      : true:成功 false:失败
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
