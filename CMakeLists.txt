cmake_minimum_required(VERSION 3.15)

project(GPIOBareMetalSetup LANGUAGES C ASM)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)

add_executable(firmware.elf
src/main.c startup.s
)

target_compile_options(firmware.elf PRIVATE
-mcpu=cortex-m3 -mthumb)

target_link_options(firmware.elf PRIVATE
-mcpu=cortex-m3
-mthumb
-T${CMAKE_SOURCE_DIR}/linker.ld -nostdlib)
target_include_directories(firmware.elf PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
add_custom_command(TARGET firmware.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary
  $<TARGET_FILE:firmware.elf>
  ${CMAKE_BINARY_DIR}/firmware.bin
  COMMENT "Generating firmware.bin"
)


