#include "bits.h"
#include "gpio.h"
#include "rcc.h"

static inline void delay_cycles(uint32_t count) {
  while (count--) {
    __asm volatile("nop");
  }
}

int main() {

  SET_GPIOA;
  SET_GPIOC;

  set_pin_configuration(GPIOC, 15,
                        GPIO_CONFIG(CNF_INPUT_PULL_DOWN, MODE_INPUT));
  set_pin_configuration(GPIOA, 1,
                        GPIO_CONFIG(CNF_GPO_PUSH_PULL, MODE_OUTPUT_10MHZ));
  GPIOC->BSRR = (1U << 15);
  GPIOA->BSRR = (1U << 17);

  while (1) {

    if (!(check_idr_pin(GPIOC, 15))) {
      delay_cycles(20000);
      if (!(check_idr_pin(GPIOC, 15))) {
        if (!check_odr_pin(GPIOA, 1))

          set_pin(GPIOA, 1);
        else
          reset_pin(GPIOA, 1);

        while (!check_idr_pin(GPIOC, 15))
          ;
      }
    }
  }
}
