#include <STM32F4xx.h>
#include <STM32F407xx.h>

// Quick and dirty delay
static void delay (unsigned int time) {
    for (unsigned int i = 0; i < time; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}

int main (void) {
    // Turn on the GPIOB peripheral
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Put the pin in output mode (B01)
    GPIOB->MODER |= GPIO_MODER_MODE9_0;

    while (1) {
        // Reset the bit for port B9
        GPIOB->BSRR = GPIO_BSRR_BR9;

        delay(500);

        GPIOB->BSRR = GPIO_BSRR_BS9;

        delay(500);
    }
}
