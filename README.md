# bare-metal-blink

LED blinker for the NUCLEO-F446RE that uses direct register access, with no HAL.

- **SysTick** generates a 1 ms tick that drives `delay_ms()`
- **User button (B1, PC13)** triggers an EXTI interrupt (debounced) that cycles the modes:
  off → slow blink (1 s) → fast blink (500 ms)
- **LED (LD2, PA5)** is driven through `GPIOA->BSRR`

## Build

Requires `arm-none-eabi-gcc`, CMake and Ninja.

```sh
cmake --preset Debug
cmake --build --preset Debug
```

The output is `build/Debug/bare-metal-blink.elf`. Flash it with STM32CubeProgrammer, OpenOCD or the STM32 VS Code extension.

## References

- RM0390: STM32F446xx Reference Manual (RCC, GPIO, SYSCFG, EXTI)
- PM0214: Cortex-M4 Programming Manual (SysTick, NVIC)
- UM1724: STM32 Nucleo-64 User Manual (board pinout)
