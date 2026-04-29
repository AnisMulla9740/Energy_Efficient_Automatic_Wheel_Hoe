/* speed_control.h */

#ifndef SPEED_CONTROL_H
#define SPEED_CONTROL_H

#include "stm32f4xx_hal.h"

/* Buttons */
#define INC_BTN_PIN     GPIO_PIN_4
#define INC_BTN_PORT    GPIOE

#define DEC_BTN_PIN     GPIO_PIN_5
#define DEC_BTN_PORT    GPIOE

/* Onboard LEDs - Correct Pins for STM32F407 Discovery */
#define SPEED_LED1_PIN  GPIO_PIN_12     // LD4 Green   → 25%
#define SPEED_LED1_PORT GPIOD

#define SPEED_LED2_PIN  GPIO_PIN_13     // LD3 Orange  → 50%
#define SPEED_LED2_PORT GPIOD

#define SPEED_LED3_PIN  GPIO_PIN_14     // LD5 Red     → 75%
#define SPEED_LED3_PORT GPIOD

#define SPEED_LED4_PIN  GPIO_PIN_15     // LD6 Blue    → 100%
#define SPEED_LED4_PORT GPIOD

/* Exported variable */
extern int speedLevel;

/* Function prototypes */
void SpeedControl_Init(void);
void SpeedControl_Process(void);
void SpeedControl_UpdateLEDs(void);

#endif /* SPEED_CONTROL_H */
