/****************************************************************************

*
* �ļ���: usart_printf.c
* ���ݼ���: ��ģ��ʵ��printf��scanf�����ض��򵽴���1
*	ʵ���ض���ֻ��Ҫ���2������
		int fputc(int ch, FILE *f);
		int fgetc(FILE *f);
*


*
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include <stdio.h>

/*******************************************************************************
	��������PrintfLogo
	��  ��: �������ƺ���������������
	��  ��:
	����˵����
*/
//void PrintfLogo(char *strName, char *strDate)
//{
//	USART_OUT(USART1,"*************************************************************\r\n");
//	USART_OUT(USART1,"* Example Name : %s\r\n", strName);
//	USART_OUT(USART1,"* Update Date  : %s\r\n", strDate);
//	USART_OUT(USART1,"* StdPeriph_Lib Version : V3.1.2\r\n");
//	USART_OUT(USART1,"* \r\n");
//	USART_OUT(USART1,"* Copyright ourstm.5d6d.com \r\n");
//	USART_OUT(USART1,"* QQ    : 9191274 \r\n");
//	USART_OUT(USART1,"* Email : sun68@qq.com \r\n");
//	USART_OUT(USART1,"*************************************************************\r\n");
//}



/*******************************************************************************
	��������fputc
	��  ��:
	��  ��:
	����˵����
	�ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���
*/
int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{}

	return ch;
}

/*******************************************************************************
	��������fputc
	��  ��:
	��  ��:
	����˵����
	�ض���getc��������������ʹ��scanff�����Ӵ���1��������
*/
int fgetc(FILE *f)
{
	/* �ȴ�����1�������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
	{}

	return (int)USART_ReceiveData(USART1);
}

