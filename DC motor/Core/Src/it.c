/*
 * it.c
 *
 *  Created on: Sep 13, 2025
 *      Author: Anis
 */

#include "main.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

/* Cortex -M4 System Tick */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

/* TIM2 Encoder IRQ */
void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim2);
}

/* TIM4 Encoder IRQ */
void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim4);
}

/* UART2 IRQ */
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2);
}

/* ADC IRQ */
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1);
}
