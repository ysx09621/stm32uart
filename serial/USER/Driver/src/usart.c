/******************** ��ʢ���ӹ����� ********************
 * �ļ���  ��usart1.c
 * ����    ������USART1         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103VET6
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0  
 * �Ա��꣺http://shop66177872.taobao.com
**********************************************************************************/
#include "global.h"


void usart1_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	/* USART1 ʹ��IO�˿����� */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART1 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);  //��ʼ��USART1
	
	
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);       
  USART_ClearFlag(USART1, USART_FLAG_TC); 
}
  
void uart4_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* ʹ�� USART1 ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/* USART1 ʹ��IO�˿����� */    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);   //��ʼ��GPIOA
	  
	/* USART1 ����ģʽ���� */
	USART_InitStructure.USART_BaudRate = 115200;	//���������ã�115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//����λ�����ã�8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 	//ֹͣλ���ã�1λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  //�Ƿ���żУ�飺��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ģʽ���ã�û��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�����뷢�Ͷ�ʹ��
	USART_Init(UART4, &USART_InitStructure);  //��ʼ��USART1
	
	
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART4, ENABLE);       
  USART_ClearFlag(UART4, USART_FLAG_TC); 
}

 
u8 uart4_send_byte(uint8_t *data, uint16_t len)
{
 	  u8 pos = 0;	  
		DebugPrintf("\r\n");
		DebugPrintf("\r\nMCUָ��>>>>>>>> ");
		while (pos < len)
		{
			if (pos == 2)
			{
				DebugPrintf(" [");
			}
			else if (pos == len - 2)
			{
				DebugPrintf(" ] ");
			}

			DebugPrintf(" %02x", data[pos]);

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
	

	
	InsertQueueValue(&Uart4TransmitQueue,ARMHEAD2 );
	InsertQueueValue(&Uart4TransmitQueue,ARMHEAD1);
  for(u8 i=0; i<len; i++)
	{
		InsertQueueValue(&Uart4TransmitQueue, *(data++));
	}
	
	USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
	
	return 1;
}


