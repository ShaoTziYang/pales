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

#include "temp.h"
#include "imu.h"



#ifdef __cplusplus
extern "C" 
#endif

int nmea_decode_test(void);
void delay(int count){
	while(count!=0){
	count--;
	}
}

int main(void)
{	  

    USART1_Config();    
  	MPU6050_Initialize();
    GPS_Config();
    
   //nmea_decode_test();

    while(1){
	}  
}

int nmea_decode_test(void){

 	int tempOut=0;
	s16  AccelGyro[7]={0};
	s16  TempBuffer[7]={0};

    nmeaINFO info;          //GPS parsed info
    nmeaPARSER parser;      //struct used for decoding 
    uint8_t new_parse=0;    //new or not, have history?
  
    nmeaTIME beiJingTime;    

    nmea_property()->trace_func = &trace;
    nmea_property()->error_func = &error;

    //GPS initialization
    nmea_zero_INFO(&info);
    nmea_parser_init(&parser);

    while(1)
    {
      if(GPS_HalfTransferEnd)     /* received half the buffer size*/
      {
        /* parse using nmea format */
        nmea_parse(&parser, (const char*)&gps_rbuff[0], HALF_GPS_RBUFF_SIZE, &info);
        
        GPS_HalfTransferEnd = 0;   //Clear flag
        new_parse = 1;             //new   info
      }
      else if(GPS_TransferEnd)    /* receiving the other half */
      {

        nmea_parse(&parser, (const char*)&gps_rbuff[HALF_GPS_RBUFF_SIZE], HALF_GPS_RBUFF_SIZE, &info);
       
        GPS_TransferEnd = 0;
        new_parse =1;
      }
      
      if(new_parse )                //if have new info
      {    
        //Converts time to GMT
        GMTconvert(&info.utc,&beiJingTime,8,1);
        
        /* Output data*/
        printf("\r\n Time:%d,%d,%d,%d,%d,%d\r\n", beiJingTime.year+1900, beiJingTime.mon+1,beiJingTime.day,beiJingTime.hour,beiJingTime.min,beiJingTime.sec);
        printf("\r\n Latitude:%f,Longtitude:%f\r\n",info.lat,info.lon);
        printf("\r\n Numbers of Sat in use:%d, Numbers of Sat in view:%d",info.satinfo.inuse,info.satinfo.inview);
        printf("\r\n Numbers of meters above horizon: %f", info.elv);
        printf("\r\n Speed: %f km/h ", info.speed);
        printf("\r\n Direction: %f degree", info.direction);
		//---------------------loop party----------------------------------------
		MPU6050_GetRawAccelGyro(AccelGyro);	
		printf("\r\nMPU Readings:");	
		printf("\r\nIMU[0]: %10d",AccelGyro[0]);
		printf("\t IMU[1]: %10d",AccelGyro[1]);
		printf("\t IMU[2]: %10d",AccelGyro[2]);
		printf("\t IMU[3]: %10d",AccelGyro[3]);
		printf("\t IMU[4]: %10d",AccelGyro[4]);
		printf("\t IMU[5]: %10d",AccelGyro[5]);        

        new_parse = 0;
      }				   
	}
}

