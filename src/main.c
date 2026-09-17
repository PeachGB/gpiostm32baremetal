#include "stdint.h"
#include <stdint.h>
#define BIT_SET(reg, pos) (reg |= (1 << pos))
#define BIT_CHECK(reg, pos) (reg & (1 << pos))
#define BIT_CLEAR(reg, pos) (reg &= ~(1 << pos))

#define RCC_BASE 0x40021000

#define GPIOC_BASE 0x40011000

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
} RCC;

typedef struct {
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO;

int main() {
  GPIO *GPIOC = (GPIO *)GPIOC_BASE;
  RCC *rcc = (RCC *)RCC_BASE;

  BIT_SET(rcc->APB2ENR, 4);

  BIT_SET(GPIOC->CRH, 20);
  BIT_SET(GPIOC->CRH, 21);
  BIT_CLEAR(GPIOC->CRH, 22);
  BIT_CLEAR(GPIOC->CRH, 23);
  BIT_SET(GPIOC->BSRR, 13);
  while (1) {
  }
}
