#ifndef stdlib_H
#define stdlib_H

#include <stdint.h>
#include <stdbool.h>
#include "entradas_salidas.h"

uint16_t i2c_readRegister(uint8_t registerAddress);
uint32_t time_us_32();
uint gpio_init(uint gpio);
uint gpio_set_dir(uint gpio, bool type);
bool gpio_get(uint gpio);

#endif // stdlib_H
