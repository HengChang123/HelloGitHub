#ifndef _DHT11_H_
#define _DHT11_H_

//#include "stm32f10x.h"
  #include <REG52.H>

sbit DHT11_DATA = P3^7;	 //温度传感器数据管脚为P3.6


void DHT11_init(void);
void DHT11_Reset(void);
unsigned char Read_Byte_value(void);
unsigned int Read_Byte_Multi(void);
void get_humi_tempra(unsigned char humi[8],unsigned char tempra[8]);
void delay_ms(unsigned int ms_count);
void delay_us(unsigned int us_count);

#endif
