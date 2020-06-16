#include "stm32f4xx.h"

// Quick and dirty delay
static void delay (unsigned int time) {
    for (unsigned int i = 0; i < time; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}

int main (void) {
    // Turn on the GPIOx peripheral
#if defined(STM32F446xx)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
#else
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
#endif

    // Put pin 13 in general purpose output mode
    // Note: The only difference here is the name of the register in the
    //       definition, both lines have the same effect.
#if defined(STM32F413xx) || \
    defined(STM32F423xx)
    GPIOC->MODER |= GPIO_MODER_MODE13_0;
#elif defined(STM32F446xx)
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
#else
    GPIOC->MODER |= GPIO_MODER_MODER13_0;
#endif

    while (1) {
        // Reset the state of pin 13 to output low
#if defined(STM32F413xx) || \
    defined(STM32F423xx)
        GPIOC->BSRR = GPIO_BSRR_BR_13;
#elif defined(STM32F446xx)
    	GPIOA->BSRR = GPIO_BSRR_BR_5;
#else
        GPIOC->BSRR = GPIO_BSRR_BR13;
#endif

        delay(500);

        // Set the state of pin 13 to output high
#if defined(STM32F413xx) || \
    defined(STM32F423xx)
        GPIOC->BSRR = GPIO_BSRR_BS_13;
#elif defined(STM32F446xx)
	GPIOA->BSRR = GPIO_BSRR_BS_5;
#else
        GPIOC->BSRR = GPIO_BSRR_BS13;
#endif

        delay(500);
    }

    // Return 0 to satisfy compiler
    return 0;
}

