/*
 * it.c
 *
 *  Created on: 28 janv. 2022
 *      Author: hassa
 */

#include "stm32f4xx_hal.h"


extern UART_HandleTypeDef huart2;

void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart2);

}
