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

#endif
