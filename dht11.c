#include "dht11.h"
#include <stdio.h>
#include <stdlib.h>

/**************************************
*文件名: dht11.c
*功能: 检测当前环境温度和湿度
*作者:XIAOZHI
*日期:2017-01-16
**************************************/

/* 管脚初始化 */
/* 
 *单总线通信，本身有上拉电阻，
 * 故设置接口  P3.6  为开漏输出 
 * 记得加上拉电阻
 */
void DHT11_init(void)
{
	   /* 时钟使能 */
	//   RCC->APB2ENR |= (0X01<<7);  //PF
   //  GPIOF->CRL &= ~(0X0F<<1*4);
	//   GPIOF->CRL |=  (0X07<<1*4);  //开漏输出  
}


/* 主机复位信号函数 */
void DHT11_Reset(void)
{

	//GPIOF->ODR &= ~(0X01<<1);     //拉低数据总线
	DHT11_DATA = 0;
	delay_ms(18);    //主机至少拉低18ms
	//GPIOF->ODR |=  (0X01<<1);   //拉高数据总线
	DHT11_DATA = 1;
	delay_us(35);    //	20—40
}

/* 读取一个字节数据函数 */
unsigned char Read_Byte_value(void)
{	
  unsigned char data_one_byte = 0;
  unsigned char data_return = 0;	
	unsigned char i; 

  /* 开始读数据1 */
	for(i=0;i<8;i++)
	{
		delay_us(78);
		//if(GPIOF->IDR & (0X01<<1))
		if(1 ==	DHT11_DATA)
		{		
			data_one_byte = 1;    //读1
			delay_us(46);
		}	
    	else
		{
			data_one_byte = 0;    //读0
		}

    	data_return <<= 1;		
    	data_return |= data_one_byte;	
	}

  return data_return;	
}

/* 读取四个字节数据函数（并未有读出最后一个检验字节） */
unsigned int Read_Byte_Multi(void)
{
  unsigned int data_multi = 0;
  unsigned int data_multi_return = 0;	
	unsigned char i;
	
	/* 主机发开始信号 */
	DHT11_Reset();
	
	/* DHT响应信号80us，紧接又拉高80us */
	delay_us(170);  

  /* 开始读数据1 */
	for(i=0;i<32;i++)
	{
		delay_us(78);
		//if(GPIOF->IDR & (0X01<<1))
		if(1 == DHT11_DATA)
		{		
			data_multi = 1;    //读1
			delay_us(47);
		}	
    	else
		{
			data_multi = 0;    //读0
		}
    	data_multi_return <<= 1;	//高位在前	
    	data_multi_return |= data_multi;	
	}

  	return data_multi_return;	
}


void get_humi_tempra(unsigned char humi[8],unsigned char tempra[8])
{
	  	unsigned char data_out[5] = {0};
	  	unsigned char i;
	
		/* 主机发开始信号 */
		DHT11_Reset();
		
		/* DHT响应信号80us，紧接又拉高80us */
		delay_us(170);  
	
	  	for(i=0;i<5;i++)
		{
			  data_out[i] = Read_Byte_value(); 
		}
		
    	sprintf(humi,"%d",data_out[0]);		
    	sprintf(tempra,"%d",data_out[2]);				
}


void delay_ms(unsigned int ms_count)
{
	unsigned int x;
	for(ms_count;ms_count > 0;ms_count--)
		for(x=110;x>0;x--);
}

void delay_us(unsigned int us_count)
{
	while(us_count--);
}


