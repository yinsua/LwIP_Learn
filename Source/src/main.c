#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include <stdio.h>	 
#include  <stdarg.h>



//extern functions	
extern void SPI2_Init(void);
extern void lwip_demo(void *pdata);

void GPIO_Configuration(void);
void RCC_Configuration(void);

unsigned int system_tick_num = 0;
unsigned int sys_now(void)
{
    return system_tick_num;
}


/****************************************************************************
* ��    �ƣ�void NVIC_Configuration(void)
* ��    �ܣ��ж�Դ����
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  /* Configure one bit for preemption priority */
  /* ���ȼ��� ˵������ռ���ȼ����õ�λ�����������ȼ����õ�λ��   ��������1�� 7 */    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				 //�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	     //��ռ���ȼ� 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			 //�����ȼ�0  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //ʹ��
  NVIC_Init(&NVIC_InitStructure);

  																  //����ѡ��EXTI1�ⲿ�жϵ�����Դ��PG6��
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource6);     //�ⲿ�ж�����,�����ж�

  EXTI_InitStructure.EXTI_Line = EXTI_Line6;					  //�����ⲿ�ж�1
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			  //�ж�ģʽ
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		  //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
/****************************************************************************
* ��    �ƣ�void Usart1_Init(void)
* ��    �ܣ�����1��ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void Usart1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);	 		//ʹ�ܴ���1ʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		 		//USART1 TX
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 		//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 		//A�˿� 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         	 		//USART1 RX
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   	 		//���ÿ�©����
  GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 		//A�˿� 

  USART_InitStructure.USART_BaudRate = 115200;						//����115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;			//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;				//��У��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�շ�ģʽ

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);							//���ô��ڲ�������   
   /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);	
  
}

/****************************************************************************
* ��    �ƣ�void RCC_Configuration(void)
* ��    �ܣ�ϵͳʱ������Ϊ72MHZ�� ����ʱ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void RCC_Configuration(void)
{
   SystemInit(); 
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO  , ENABLE);  
 
}


/****************************************************************************
* ��    �ƣ�void GPIO_Configuration(void)
* ��    �ܣ�ͨ��IO������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����
****************************************************************************/  
void GPIO_Configuration(void)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                         RCC_APB2Periph_GPIOG, ENABLE);
  	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;					 //W25Q128 SPIƬѡ
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);										// W25Q128 SPIƬѡ��ֹ

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	         	 	//ENC28J60��������ж����� 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   	 		//�ڲ���������
  GPIO_Init(GPIOG, &GPIO_InitStructure);		 


//  GPIO_ResetBits(GPIOE, GPIO_Pin_1);						 //��λENC28J60
//  Delay(0xAFFF);					   
//  GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 	             
//  Delay(0xAFFF);	
}


/****************************************************************************
* ��    �ƣ�int main(void)
* ��    �ܣ��������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
 
int main(void)
{
	RCC_Configuration();				 //ϵͳʱ������
	NVIC_Configuration();
	GPIO_Configuration();                //IO�ڳ�ʼ��
	Usart1_Init();                       //����1��ʼ��
	
	/* ����systic��Ϊ20ms�ж� */
	if (SysTick_Config(20*72000))		//ʱ�ӽ����жϣ�20msһ��
    { 
    	/* error handle*/ 
     	while (1);
    }
	
	printf("\r\nStart init SPI2\r\n");
	SPI2_Init();	      //SPI�ڳ�ʼ�������������䴫������
	printf("SPI2 init finished\r\n");	
	
	printf("Launch LwIP demo\r\n");
	lwip_demo(NULL);	  //��ʼ���ںˣ�����LwIP���
	 
	while (1)
	{
	    //exit(0);	
	}
}

__asm void EnableInt(unsigned int data)
{

    MRS     R0, PRIMASK
    CPSID   I
    BX      LR

}
__asm unsigned int DisableInt(void)
{

    MSR     PRIMASK, R0;
    BX      LR

}
