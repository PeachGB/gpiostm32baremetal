# STM32f103 Bare Metal GPIO Setup

this is a minimum setup for STM32f103CB (a common blue pill chip) Medium Density (it's usable for other STM32F103XX chips, in that case
you should modify the memory sizes and the vector table depending on the chip).
custom minimum HAL that defines macros and functions for checking and setting GPIOs, and RCC. 
inside the startup.s there are comments about each assembly line for the people that doesn't understand assembly or arm assembly specifically.

Only Reset_Handler it's defined, all other handlers on the vector table point to Default_Handler, which just hangs

if you're using any other chip from the F103 family you should edit the memory layout on linker.md and the vector table on startup.s
according to the chip's manual

if you flash it as it is, it should turn the pin c13 HIGH

## Build
you can use make for the binary or you can use make all for the .elf and object files, you can check the makefile for a specific file

\`\`\`bash
git clone https://github.com/PeachGB/stm32F103BareMetalSetup
cd stm32f103BareMetalSetup
cmake -S . -B build
cmake --build build
\`\`\`



## Licencia

Unlicense
