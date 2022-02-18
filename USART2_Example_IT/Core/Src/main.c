#include<string.h>
#include "stm32f4xx_hal.h"
#include "main.h"

#define TRUE 1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);
uint8_t convert_to_capital(uint8_t data);

UART_HandleTypeDef huart2;

char *user_data = "The application is running\r\n";

uint8_t data_buffer[100];
uint8_t recvd_data;
uint32_t count=0;
uint8_t reception_complete = FALSE;

uint8_t Rx_data[10];

int main(void)
{
	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t len_of_data = strlen(user_data);
	HAL_UART_Transmit(&huart2,(uint8_t*)user_data,len_of_data,HAL_MAX_DELAY);


    while(reception_complete != TRUE)
    {
    	HAL_UART_Receive_IT(&huart2,Rx_data,7);
    }


	while(1);


	return 0;
}


void SystemClockConfig(void)
{


}


void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ( HAL_UART_Init(&huart2) != HAL_OK )
	{
		//There is a problem
		Error_handler();
	}


}

 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	 int i = 0;
	 while(Rx_data[i] != '\r')
	 {
		 i++;
	 }

	 reception_complete = TRUE;
	 HAL_UART_Transmit(huart,Rx_data,7,HAL_MAX_DELAY);

}


uint8_t convert_to_capital(uint8_t data)
{
	if( data >= 'a' && data <= 'z')
	{
		data = data - ( 'a'- 'A');
	}

	return data;

}

void Error_handler(void)
{
	while(1);
}
