#include "stm32f4xx.h"
#include <stdio.h>

// Function prototypes
void initGPIO(void);
void initTIM2(void);
void delay_us(uint32_t us);
float measureDistance(void);
void moveForward(void);
void stopAndAlert(void);
void keypad_init();
char keypad_scan();