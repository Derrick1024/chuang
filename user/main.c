#include "stm32f10x.h"
#include "bsp_sdio_sdcard.h"
#include "bsp_usart1.h"	
#include "ff.h"
#include "systick.h"
#include "bsp_dht11.h"
#include "pwm_output.h"

FIL fnew;													/* file objects */
FATFS fs;													/* Work area (file system object) for logical drives */
FRESULT res; 
UINT br, bw;            					/* File R/W count */
//BYTE buffer[4096]={0};       		  /* file copy buffer */
char text[64] ; 
uint8_t usart1_rx_flag = 0;
DHT11_Data_TypeDef DHT11_1_Data;
DHT11_Data_TypeDef DHT11_2_Data;

int Data_Write_In_SD(void);
void DHT11_1(void);
void DHT11_2(void);
void cmp_dht11_1_2(void);


int main(void)
{
	/* USART1 config */
	USART1_Config();
	/* Sdio Interrupt Config */
	NVIC_Configuration();
	/* systick Config */
	SysTick_Init();
	/* TIM3 Config */
	TIM3_PWM_Init();
	/* DHT11_1_2 Config */
	DHT11_GPIO_Config_1();
	DHT11_GPIO_Config_2();
	/* Register work area for each volume (Always succeeds regardless of disk status) */
	f_mount(0,&fs);
	printf("\r\n this is 节能减排电控 Vision 1 \r\n");
	printf("\r\n Initial success  \r\n");
	//Delay_us(10);

	
	while(1)
	{	
		if(usart1_rx_flag == 1)
		{
			Data_Write_In_SD();//向SD卡中写数据
			
			//printf("%s",text);
			
			usart1_rx_flag=0;//清空自定义标志位 usart1_rx_flag
		}
		DHT11_1();
		DHT11_2();
		cmp_dht11_1_2();
		
	}
	
		/* Unregister work area prior to discard it */
    //f_mount(0, NULL);


}


int Data_Write_In_SD(void)
{
	/* Create new file on the drive 0 */
	res = f_open(&fnew, "0:Data1.txt", FA_OPEN_ALWAYS | FA_WRITE );
		
	if ( res == FR_OK )
	{
		f_lseek(&fnew,fnew.fsize);
		f_printf(&fnew,text);
		//res = f_write(&fnew, textFileBuffer, sizeof(textFileBuffer), &bw);
		f_close(&fnew);      
	}
	return 0;
}

void DHT11_1(void)
{
	if( Read_DHT11_1(&DHT11_1_Data)==SUCCESS)
	{
		printf(" <1>**湿度%d.%d,温度%d.%d \n",
		DHT11_1_Data.humi_int,DHT11_1_Data.humi_deci,DHT11_1_Data.temp_int,DHT11_1_Data.temp_deci);
	}
	else
	{
		printf("Read DHT11_1 ERROR!\r\n");
	}
	Delay_ms(10);
}

void DHT11_2(void)
{
	if( Read_DHT11_2(&DHT11_2_Data)==SUCCESS)
	{
		printf(" <2>**湿度%d.%d,温度%d.%d \n\n",
		DHT11_2_Data.humi_int,DHT11_2_Data.humi_deci,DHT11_2_Data.temp_int,DHT11_2_Data.temp_deci);
	}
	else
	{
		printf("Read DHT11_2 ERROR!\r\n");
	}
	Delay_ms(10);
}

void cmp_dht11_1_2(void)
{
	int max,min;
	
	max=(DHT11_1_Data.temp_int>DHT11_2_Data.temp_int) ? DHT11_1_Data.temp_int : DHT11_2_Data.temp_int ;
	min=(DHT11_1_Data.temp_int>DHT11_2_Data.temp_int) ? DHT11_2_Data.temp_int : DHT11_1_Data.temp_int ;
	
	if((max-min) >= 2)
	{
		TIM3_Mode_Config(500);
		Delay_ms(200);
	}
	else 
	{
		TIM3_Mode_Config(300);
		Delay_ms(200);
	}
}
//Delay_us(__IO u32 nTime);
//Delay_ms(__IO u32 nTime);

	  

