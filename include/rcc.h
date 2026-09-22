#ifndef RCC_H
#define RCC_H

#include "bits.h"
#include "stdint.h"

#define RCC_BASE 0x40021000
#define RCC ((RCC_t *)RCC_BASE)

#define SET_GPIOA BIT_SET(RCC->APB2ENR, 2)
#define SET_GPIOB BIT_SET(RCC->APB2ENR, 3)
#define SET_GPIOC BIT_SET(RCC->APB2ENR, 4)
#define SET_GPIOD BIT_SET(RCC->APB2ENR, 5)
#define SET_GPIOE BIT_SET(RCC->APB2ENR, 6)

#define HSI_ON BIT_SET(RCC->CR, 0)
#define HSI_OFF BIT_CLEAR(RCC->CR, 0)
#define HSI_READY BIT_CHECK(RCC->CR, 1)

#define HSE_ON BIT_SET(RCC->CR, 16)
#define HSE_OFF BIT_CLEAR(RCC->CR, 16)
#define HSE_READY BIT_CHECK(RCC->CR, 17)

#define PLL_ON BIT_SET(RCC->CR, 24)
#define PLL_OFF BIT_CLEAR(RCC->CR, 24)
#define PLL_READY BIT_CHECK(RCC->CR, 25)

#define SYSTEM_CLOCK_SWITCH_HSI RCC->CFGR &= ~(0b11)
#define SYSTEM_CLOCK_SWITCH_HSE                                                \
  RCC->CFGR &= ~(0b11);                                                        \
  RCC->CFGR |= 0b01
#define SYSTEM_CLOCK_SWITCH_PLL                                                \
  RCC->CFGR &= ~(0b11);                                                        \
  RCC->CFGR |= 0b10

#define PLL_SOURCE_HSI_OSCILATOR_CLOCK_DIV 0
#define PLL_SOURCE_FROM_PREDIV1 1
#define PLL_SOURCE(PLL_SOURCE)                                                 \
  RCC->CFGR &= ~(1 << 16);                                                     \
  RCC->CFGR |= (PLL_SOURCE << 16)

// PLL factors
#define PLL_MULT_X_4 0b0010
#define PLL_MULT_X_5 0b0011
#define PLL_MULT_X_6 0b0100
#define PLL_MULT_X_7 0b0101
#define PLL_MULT_X_8 0b0110
#define PLL_MULT_X_9 0b0111
#define PLL_MULT_X_6_dot_5 0b01101
// PLL_MULT_MASK
#define PLL_MULT_MASK(MULT) (MULT << 18)
#define PLL_MULT(MULT)                                                         \
  RCC->CFGR &= ~(0xF << 18);                                                   \
  RCC->CFGR |= PLL_MULT_MASK(MULT)

typedef struct {
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t CSR;
  volatile uint32_t AHBRSTR;
  volatile uint32_t CFGR2;
} RCC_t;

static inline void hse_on() {
  HSE_ON;
  while (!HSE_READY) {
  }
}
static inline void hse_off() {
  HSE_OFF;
  while (HSE_READY) {
  }
}

static inline void hsi_on() {
  HSI_ON;
  while (!HSI_READY) {
  }
}
static inline void hsi_off() {
  HSI_OFF;
  while (HSI_READY) {
  }
}

static inline void pll_on() {
  PLL_ON;
  while (!PLL_READY) {
  }
}
static inline void pll_off() {
  PLL_OFF;
  while (PLL_READY) {
  }
}

#endif
