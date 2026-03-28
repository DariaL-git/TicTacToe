#pragma once
#include <stdint.h>

#define LED_COUNT 12

void neopixel_set(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
void neopixel_show(void);
void neopixel_clear(void);
