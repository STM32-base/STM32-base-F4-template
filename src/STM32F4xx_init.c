#include "STM32F4xx.h"
#include "common.h"

/**
 * Initialize the HSI clock source and reset the PLL configuration. This
 * function is called by the startup_common.s file, just before calling the
 * main() function.
 *
 * You can adapt this function to fit your needs, however, do not change its
 * name! It is called in the startup code.
 */
void SystemInit (void) {
  // FPU settings
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  // Set CP10 and CP11 Full Access
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
#endif

  // Set HSION bit
  RCC->CR |= (uint32_t)0x00000001;

  // Reset CFGR register
  RCC->CFGR = 0x00000000;

  // Reset HSEON, CSSON and PLLON bits
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  // Reset PLLCFGR register
  RCC->PLLCFGR = 0x24003010;

  // Reset HSEBYP bit
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  // Disable all interrupts
  RCC->CIR = 0x00000000;
}
