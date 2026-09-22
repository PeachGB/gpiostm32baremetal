#include "gpio.h"
#include "assert.h"
#include "bits.h"
#include "stdint.h"

void set_pin_configuration(GPIO *gpio, uint32_t pin, uint8_t gpio_config) {
  uint32_t pin_offset = (pin % 8) * 4;
  if (pin < 8) {
    gpio->CRL &= ~(0x0F << pin_offset);
    gpio->CRL |= ((uint32_t)gpio_config << pin_offset);
  } else {
    gpio->CRH &= ~(0x0F << pin_offset);
    gpio->CRH |= ((uint32_t)gpio_config << pin_offset);
  }
}
