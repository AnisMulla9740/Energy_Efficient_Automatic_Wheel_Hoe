/*
 * it.h
 *
 *  Created on: Sep 13, 2025
 *      Author: Anis
 */

#ifndef INC_IT_H_
#define INC_IT_H_

#include "main.h"

/* Cortex -M4 processor interrupt handlers */
void SysTick_Handler(void);

/* Peripheral Interrupt Handlers */
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
void USART2_IRQHandler(void);
void ADC_IRQHandler(void);

#endif /* INC_IT_H_ */
