
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "gps_config.h"
#include "ff.h"			 
#include <string.h>

#include "temp.h"
#include "imu.h"

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

void delay(int count){
	while(count!=0){
	count--;
	}
}

int main(void)
{
	//int16_t  AccelGyro[6]={0};
	int tempOut=0;

	delay_init(72);
	//USART1_Config();
	MPU6050_Initialize();
	GPS_Config();

	printf("\r\n GPS Ready.\r\n"); 
	nmea_decode_test();
	
//	USART3_Config();
	
	/*
   //Usart1 setup, sending info using printf
    int16_t  AccelGyro[6]={0};
	
	USART1_Config();
	GPS_Config();
    printf("\r\n GPS Ready.\r\n"); 
  
    nmea_decode_test();
	
	MPU6050_I2C_Init();
	MPU6050_Initialize();
	if( MPU6050_TestConnection()== TRUE){
   	// connection success
	}else{
   	// connection failed
	}
	MPU6050_GetRawAccelGyro(AccelGyro);
	  */
    while(1){
	
	
		
	
	  /*
	tempOut=USART3_getTemp();
	printf("temp is: %d\n",tempOut);
	delay(10000000);
		*/
	}
 }						

 int nmea_decode_test(void){
 
	s16  AccelGyro[7]={0};
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
        
        new_parse = 0;
      }
	  //--------------------------actual loop------------------------
					printf("\r\nMPU Readings:");	
		MPU6050_GetRawAccelGyro(AccelGyro);
		printf("\r\nIMU[0]: %10d",AccelGyro[0]);
		printf("\t IMU[1]: %10d",AccelGyro[1]);
		printf("\t IMU[2]: %10d",AccelGyro[2]);
		printf("\t IMU[3]: %10d",AccelGyro[3]);
		printf("\t IMU[4]: %10d",AccelGyro[4]);
		printf("\t IMU[5]: %10d",AccelGyro[5]);
		delay_ms(100);
	}
}

