#include "stm32f4xx.h"

volatile uint32_t ms_ticks = 0;
volatile uint8_t btn_state = 0;

static void delay_ms(uint32_t ms) {
  uint32_t st = ms_ticks;
  while ((ms_ticks - st) < ms) {}
}

int main(void) {
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  (void) RCC->AHB1ENR;
  (void) RCC->AHB2ENR;

  GPIOA->MODER |= (1U << (5 * 2));
  GPIOC->MODER &= ~(3U << (13 * 2));

  SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

  EXTI->FTSR |= (1U << 13);
  EXTI->RTSR &= ~(1U << 13);
  EXTI->IMR |= (1U << 13);

  NVIC_SetPriority(EXTI15_10_IRQn, 2);
  NVIC_EnableIRQ(EXTI15_10_IRQn);
  
  while (1) {
    // if (btn_state) GPIOA->BSRR |= (1U << 5);
    // else GPIOA->BSRR |= (1U << (5 + 16));
    switch(btn_state) {
    case 1:
      GPIOA->BSRR |= (1U << 5);
      delay_ms(1000);
      GPIOA->BSRR |= (1U << (5 + 16));
      delay_ms(1000);
      break;
    case 2:
      GPIOA->BSRR |= (1U << 5);
      delay_ms(500);
      GPIOA->BSRR |= (1U << (5 + 16));
      delay_ms(500);
      break;
    case 0:
      GPIOA->BSRR |= (1U << (5 + 16));
      break;
    }
  }
}