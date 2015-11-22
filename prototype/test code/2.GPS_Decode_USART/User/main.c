/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2014-08-xx
  * @brief   gps模块演示测试程序
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-STM32 开发板
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
	*/
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "gps_config.h"
#include "ff.h"
#include <string.h>

//nmea
#include "stm32f10x.h"
#include "bsp_sdio_sdcard.h"
#include "bsp_usart1.h" 
#include "bsp_usart2.h"
#include "ff.h"
#include "nmea/nmea.h"
#include "gps_config.h"

//
#include "delay.h"

#ifdef __cplusplus
extern "C" 
#endif


		

int nmea_decode_test(void);


int main(void)
{
    USART1_Config();    
  
    GPS_Config();
    
    nmea_decode_test();

    while(1){
	 printf("\r\n Testing \r\n"); 
   delay_ms(100);
	}
  
  
}



