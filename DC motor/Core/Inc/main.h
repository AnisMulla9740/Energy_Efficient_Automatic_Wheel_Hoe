/*
 * main.h
 *
 *  Created on: Sep 13, 2025
 *      Author: Anis
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_


#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>

/* Clock frequencies */
#define SYS_CLOCK_FREQ_84_MHZ			84U

/* True/False macros */
#define TRUE							1U
#define FALSE							0U

/* Peripherals handle (declared in main.c) */
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;			//encoder
extern TIM_HandleTypeDef htim4;			//pwm

/* User init functions */
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM4_Init(void);
void MX_USART2_UART_Init(void);

#endif /* INC_MAIN_H_ */
