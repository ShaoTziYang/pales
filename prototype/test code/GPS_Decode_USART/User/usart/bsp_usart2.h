#ifndef __USART2_H
#define	__USART2_H

#include "stm32f10x.h"
#include <stdio.h>

				  
void USART2_Config(void);
void USART2_printf(USART_TypeDef* USARTx, char *Data,...);


extern char *get_rebuff(uint8_t *len);
extern void clean_rebuff(void);

#endif /* __USART2_H */
