/*
 * power_control.c
 *
 *  Created on: Apr 20, 2026
 *      Author: Anis
 */


#include "power_control.h"

/* -------- CONFIG -------- */
#define POWER_SENSE_PORT   GPIOE
#define POWER_SENSE_PIN    GPIO_PIN_2

static PowerStatus_t powerStatus = POWER_FAULT;

/* -------- INIT -------- */
void PowerControl_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStruct.Pin = POWER_SENSE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;  // Expect HIGH when motor powered

    HAL_GPIO_Init(POWER_SENSE_PORT, &GPIO_InitStruct);
}

/* -------- CHECK POWER -------- */
PowerStatus_t PowerControl_Check(void)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(POWER_SENSE_PORT, POWER_SENSE_PIN);

    if (state == GPIO_PIN_SET)
        return POWER_OK;
    else
        return POWER_FAULT;
}

/* -------- PROCESS -------- */
void PowerControl_Process(void)
{
    powerStatus = PowerControl_Check();

    if (powerStatus == POWER_OK)
    {
        // Everything normal
    }
    else
    {
        // Fault detected
        // Example: stop motor, alert user
    }
}
