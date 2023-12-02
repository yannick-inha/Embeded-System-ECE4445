#include "stm32f4xx.h"
#include <stdio.h>

void delay_us(uint32_t us) {
    __HAL_TIM_SET_COUNTER(&htim2, 0);  // Reset the counter
    while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}

float measureDistance(void) {
    // Trigger the ultrasonic sensor
    HAL_GPIO_WritePin(GPIOA, TRIG_PIN, GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(GPIOA, TRIG_PIN, GPIO_PIN_RESET);

    // Wait for the echo signal
    while (HAL_GPIO_ReadPin(GPIOA, ECHO_PIN) == GPIO_PIN_RESET);
    uint32_t start_time = __HAL_TIM_GET_COUNTER(&htim2);

    // Wait for the end of the echo signal
    while (HAL_GPIO_ReadPin(GPIOA, ECHO_PIN) == GPIO_PIN_SET);
    uint32_t end_time = __HAL_TIM_GET_COUNTER(&htim2);

    // Calculate distance in centimeters
    float distance = (float)(end_time - start_time) * 0.0343 / 2.0;
    return distance;
}

void stepForward(uint16_t steps) {
    // Set the direction pin to indicate forward rotation
    HAL_GPIO_WritePin(GPIOA, DIR_PIN, GPIO_PIN_SET);

    // Generate pulses to drive the stepper motor forward
    for (uint16_t i = 0; i < steps; ++i) {
        HAL_GPIO_WritePin(GPIOA, STEP_PIN, GPIO_PIN_SET);
        delay_us(500);  // Adjust as needed based on your stepper motor specifications
        HAL_GPIO_WritePin(GPIOA, STEP_PIN, GPIO_PIN_RESET);
        delay_us(500);  // Adjust as needed based on your stepper motor specifications
    }
}

void stopAndAlert(void) {
    // Stop the robot
    // Implement the code to stop the robot

    // Activate the buzzer to alert about the obstacle
    HAL_GPIO_WritePin(GPIOA, BUZZER_PIN, GPIO_PIN_SET);
    delay_us(500000);  // Delay for 500 ms (adjust as needed)
    HAL_GPIO_WritePin(GPIOA, BUZZER_PIN, GPIO_PIN_RESET);
}

char keypad_scan() {
    const char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    for (int row = 0; row < 4; ++row) {
        // Activate row
        ROW_PORT->ODR = 1 << row;

        for (int col = 0; col < 4; ++col) {
            if (!(COL_PORT->IDR & (1 << (col + 8)))) {
                // Key pressed
                return keys[row][col];
            }
        }

        // Deactivate row
        ROW_PORT->ODR = 0;
    }

    // No key pressed
    return 0;
}