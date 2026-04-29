/*
 * power_control.h
 *
 *  Created on: Apr 20, 2026
 *      Author: Anis
 */

#ifndef INC_POWER_CONTROL_H_
#define INC_POWER_CONTROL_H_

#include "stm32f4xx_hal.h"
#include "main.h"

typedef enum
{
    POWER_OK = 0,
    POWER_FAULT
} PowerStatus_t;

/* Initialize sensing */
void PowerControl_Init(void);

/* Check motor power rail */
PowerStatus_t PowerControl_Check(void);

/* Optional handler */
void PowerControl_Process(void);

#endif /* INC_POWER_CONTROL_H_ */
