#ifndef GPIO_H
#define GPIO_H

#include "bits.h"
#include <stdint.h>
typedef struct {
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO;

#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000
#define GPIOD_BASE 0x40011400
#define GPIOE_BASE 0x40011800
#define GPIOF_BASE 0x40011C00
#define GPIOG_BASE 0x40012000

#define GPIOA ((GPIO *)GPIOA_BASE)
#define GPIOB ((GPIO *)GPIOB_BASE)
#define GPIOC ((GPIO *)GPIOC_BASE)
#define GPIOD ((GPIO *)GPIOD_BASE)
#define GPIOE ((GPIO *)GPIOE_BASE)
#define GPIOF ((GPIO *)GPIOF_BASE)
#define GPIOG ((GPIO *)GPIOG_BASE)

// output masks
// general puprose output
#define CNF_GPO_PUSH_PULL 0b00
#define CNF_GPO_OPEN_DRAIN 0b01
// alternate function output
#define CNF_AFO_PUSH_PULL 0b10
#define CNF_AFO_OPEN_DRAIN 0b11
// input masks
#define CNF_ANALOG_INPUT 0b00
#define CNF_INPUT_FLOATING 0b01
#define CNF_INPUT_PULL_DOWN 0b10
#define CNF_INPUT_PULL_UP 0b10

#define MODE_INPUT 0b00
#define MODE_OUTPUT_10MHZ 0b01
#define MODE_OUTPUT_2MHZ 0b10
#define MODE_OUTPUT_50MHZ 0b11

#define GPIO_CONFIG(cnf, mode) (cnf << 2) | mode

void set_pin_configuration(GPIO *gpio, uint32_t pin, uint8_t mode);
static inline bool check_odr_pin(GPIO *gpio, uint32_t pin) {
  return BIT_CHECK(gpio->ODR, pin);
}

static inline bool check_idr_pin(GPIO *gpio, uint32_t pin) {
  return BIT_CHECK(gpio->IDR, pin);
}

static inline void set_pin(GPIO *gpio, uint32_t pin) {
  BIT_SET(gpio->BSRR, pin);
}
static inline void reset_pin(GPIO *gpio, uint32_t pin) {
  BIT_SET(gpio->BRR, pin);
}
#endif
