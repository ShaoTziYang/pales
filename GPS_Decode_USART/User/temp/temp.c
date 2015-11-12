#include "temp.h"
#include <stdarg.h>




/*
 * 函数名：USART2_Config
 * 描述  ：USART2 GPIO 配置,工作模式配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void USART3_Config(void)
{
/*
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//* config USART2 clock 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//* USART2 GPIO config 
  //* Configure USART2 Tx (PA.02) as alternate function push-pull 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	    
  //* Configure USART2 Rx (PA.03) as input floating 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	//* USART2 mode config 
	USART_InitStructure.USART_BaudRate = 9600;                //GPS模块默认使用波特率：9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure); 

	USART_Cmd(USART3, ENABLE);
	*/
}


int USART3_getTemp(USART_TypeDef* USARTx, char *Data,...)
{
  int tempTar =0;
  int tempEnv =0;
  int j =0;
  int RXBUFF[10];
  if (USART_GetFlagStatus(USART3, USART_FLAG_TXE) != RESET){
		USART_SendData(USART3, 0xA5);
		USART_SendData(USART3, 0x15);
		USART_SendData(USART3, 0xBA);

	}
  while(j<9)
  {		     
       //Wait until a byte is received
       while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
       RXBUFF[j] = USART_ReceiveData(USART3);
       j++;         
	   //if(RXBUFF[0]!=0x5A | RXBUFF[1]!=0x5A | RXBUFF[2]!=0x45 | RXBUFF[3]!=0x04){
	   //return error
	   //}
	   tempTar = RXBUFF[4]*16*16+RXBUFF[5];    
	   tempEnv = RXBUFF[6]*16*16+RXBUFF[7];   
	    
  }	
  return tempTar;	  
		   
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
