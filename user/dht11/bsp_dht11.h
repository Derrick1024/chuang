#ifndef __BSP_DHT11_H
#define	__BSP_DHT11_H

#include "stm32f10x.h"
#include "SysTick.h"

#define HIGH  1
#define LOW   0

#define DHT11_CLK_1     RCC_APB2Periph_GPIOC
#define DHT11_PIN_1     GPIO_Pin_0                
#define DHT11_PORT_1		GPIOC

#define DHT11_CLK_2     RCC_APB2Periph_GPIOC
#define DHT11_PIN_2     GPIO_Pin_1                  
#define DHT11_PORT_2		GPIOC

//���κ꣬��������������һ��ʹ��,����ߵ�ƽ��͵�ƽ
#define DHT11_DATA_OUT_1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_0)
 //��ȡ���ŵĵ�ƽ
#define  DHT11_DATA_IN_1()	   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
					
#define DHT11_DATA_OUT_2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_1)
 //��ȡ���ŵĵ�ƽ
#define  DHT11_DATA_IN_2()	   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)

typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
		                 
}DHT11_Data_TypeDef;


void DHT11_GPIO_Config_1(void);
static void DHT11_Mode_IPU_1(void);
static void DHT11_Mode_Out_PP_1(void);
uint8_t Read_DHT11_1(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte_1(void);

void DHT11_GPIO_Config_2(void);
static void DHT11_Mode_IPU_2(void);
static void DHT11_Mode_Out_PP_2(void);
uint8_t Read_DHT11_2(DHT11_Data_TypeDef *DHT11_Data);
static uint8_t Read_Byte_2(void);

#endif /* __DHT11_H */







