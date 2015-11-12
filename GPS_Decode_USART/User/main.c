
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "gps_config.h"
#include "ff.h"			 
#include <string.h>

//test
#include "temp.h"


//extern void nmea_decode_test(void);


int main(void)
{
   //Usart1 setup, sending info using printf
    USART1_Config();    
  
    
    GPS_Config();
    
    printf("\r\n GPS Ready.\r\n"); 
  
    nmea_decode_test();

    while(1);
 }
