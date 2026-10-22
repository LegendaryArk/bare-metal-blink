#include "stm32f4xx.h"

volatile uint32_t ms_ticks = 0;

static void delay_ms(uint32_t ms) {
  uint32_t st = ms_ticks;
  while ((ms_ticks - st) < ms) {}
}

int main(void) {
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  (void) RCC->AHB1ENR;

  GPIOA->MODER |= (1U << (5 * 2));
  
  while (1) {
    GPIOA->BSRR |= (1U << 5);
    delay_ms(1000);
    GPIOA->BSRR |= (1U << (5 + 16));
    delay_ms(500);
  }
}