/*
 * keyboard.h
 *
 *  Created on: Nov 19, 2024
 *      Author: DJ
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "stdint.h"
#include "spi.h"

void keyboard_init(SPI_HandleTypeDef *hspi, uint8_t ms_rate);
void get_key_1ms(void);
void keyboard_callback(uint8_t key_val);
#endif /* INC_KEYBOARD_H_ */

