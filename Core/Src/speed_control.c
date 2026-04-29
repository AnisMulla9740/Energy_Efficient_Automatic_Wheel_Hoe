/* speed_control.c */
#include "speed_control.h"
#include <stdio.h>

/* Private variables */
int speedLevel = 0;
static uint8_t lastIncState = 1;   // Released (HIGH due to pull-up)
static uint8_t lastDecState = 1;

/* Private function */
static void SpeedControl_HandleButtons(void);

/* Initialize buttons and set initial LED state */
void SpeedControl_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Buttons on PE2 & PE3 */
    GPIO_InitStruct.Pin   = INC_BTN_PIN | DEC_BTN_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* LEDs on Port D - PD12, PD13, PD14, PD15 */
    GPIO_InitStruct.Pin   = SPEED_LED1_PIN | SPEED_LED2_PIN |
                            SPEED_LED3_PIN | SPEED_LED4_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);   // ← GPIOD not GPIOA

    SpeedControl_UpdateLEDs();

    printf("Speed Control Initialized\r\n");
}

/* Main process - call this in every loop iteration */
void SpeedControl_Process(void)
{
    SpeedControl_HandleButtons();
    SpeedControl_UpdateLEDs();
}

/* Update the 4 onboard LEDs based on speedLevel */
//void SpeedControl_UpdateLEDs(void)
//{
//    HAL_GPIO_WritePin(SPEED_LED1_PORT, SPEED_LED1_PIN,
//        (speedLevel >= 25) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//
//    HAL_GPIO_WritePin(SPEED_LED2_PORT, SPEED_LED2_PIN,
//        (speedLevel >= 50) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//
//    HAL_GPIO_WritePin(SPEED_LED3_PORT, SPEED_LED3_PIN,
//        (speedLevel >= 75) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//
//    HAL_GPIO_WritePin(SPEED_LED4_PORT, SPEED_LED4_PIN,
//        (speedLevel >= 100) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//}

void SpeedControl_UpdateLEDs(void)
{
    HAL_GPIO_WritePin(SPEED_LED1_PORT, SPEED_LED1_PIN, (speedLevel >= 25) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SPEED_LED2_PORT, SPEED_LED2_PIN, (speedLevel >= 50) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SPEED_LED3_PORT, SPEED_LED3_PIN, (speedLevel >= 75) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SPEED_LED4_PORT, SPEED_LED4_PIN, (speedLevel >= 100) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/* Handle button presses with edge detection (only trigger on press, not hold) */
static void SpeedControl_HandleButtons(void)
{
    uint8_t incState = HAL_GPIO_ReadPin(INC_BTN_PORT, INC_BTN_PIN);
    uint8_t decState = HAL_GPIO_ReadPin(DEC_BTN_PORT, DEC_BTN_PIN);

    /* Increase button pressed */
    if (incState == GPIO_PIN_RESET && lastIncState == GPIO_PIN_SET)
    {
        speedLevel += 25;
        if (speedLevel > 100)
            speedLevel = 100;
        printf("Speed Increased -> %d%%\r\n", speedLevel);
    }

    /* Decrease button pressed */
    if (decState == GPIO_PIN_RESET && lastDecState == GPIO_PIN_SET)
    {
        speedLevel -= 25;
        if (speedLevel < 0)
            speedLevel = 0;
        printf("Speed Decreased -> %d%%\r\n", speedLevel);
    }

    /* Save current button states for next edge detection */
    lastIncState = incState;
    lastDecState = decState;
}
