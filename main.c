#include "init.c"
#include "function.c"
#include "main.h"

// Define GPIO pins for ultrasonic sensor and buzzer
#define TRIG_PIN GPIO_PIN_0
#define ECHO_PIN GPIO_PIN_1
#define BUZZER_PIN GPIO_PIN_2

char password[] = "1234";  // Set your initial password
char entered_password[5];
int password_index = 0;


int main(void) {
    HAL_Init();  // Initialize the Hardware Abstraction Layer
    keypad_init() 
    SystemClock_Config();  // Configure the system clock
    initGPIO();  // Initialize GPIO pins
    initTIM2();  // Initialize TIM2 for delay function


    while (1) {
    char key = keypad_scan();

    if (key) {
        // Handle keypress
        entered_password[password_index++] = key;
        if (password_index == 4) {
            // Check entered password
            entered_password[4] = '\0';  // Null-terminate the string
            if (strcmp(entered_password, password) == 0) {
                printf("Correct password!\n");
                printf("Access granted!\n");
                printf("Start program")
                while (1) {
                    float distance = measureDistance();
                    if (distance > 20.0) {
                        moveForward();
                    } else {
                        stopAndAlert();
                    }
    }
            } else {
                printf("Incorrect password!\n");
                printf("Access denied!\n");-
            }
            // Reset password entry
            password_index = 0;
            memset(entered_password, 0, sizeof(entered_password));
            }
        }
    }
return 0;
}