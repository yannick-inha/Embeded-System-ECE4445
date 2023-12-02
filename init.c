#include "stm32f4xx.h"
#include <stdio.h>

void initGPIO(void) {
    // Enable GPIO Clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure TRIG_PIN and BUZZER_PIN as output
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = TRIG_PIN | BUZZER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure ECHO_PIN as input
    GPIO_InitStruct.Pin = ECHO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void keypad_init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

    // Rows are outputs
    ROW_PORT->MODER &= ~(0xFF);  // Clear bits for pins 0-3
    ROW_PORT->MODER |= 0x55;     // Set as outputs

    // Columns are inputs with pull-up resistors
    COL_PORT->MODER &= ~(0xFF << 8);  // Clear bits for pins 8-11
    COL_PORT->PUPDR |= 0xAA << 8;     // Set as pull-up inputs
}

void initTIM2(void) {
    // Enable TIM2 clock
    __HAL_RCC_TIM2_CLK_ENABLE();

    // Configure TIM2
    TIM_HandleTypeDef htim2;
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 84 - 1;  // Assuming a system clock of 84 MHz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0xFFFF;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim2);
}