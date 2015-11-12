#ifndef _TEMP_H
#define	_TEMP_H

#include "stm32f10x.h"
#include <stdio.h>


void USART3_Config(void);
int USART3_printf(USART_TypeDef* USARTx, char *Data,...);


extern char *get_rebuff(uint8_t *len);
extern void clean_rebuff(void);

#endif /* __USART1_H */
