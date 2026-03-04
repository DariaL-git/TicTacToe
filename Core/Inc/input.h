#pragma once
#include <stdint.h>

void input_init(void);
void input_task(void);

void input_set_board_n(uint8_t n);      // n = 3..9

int  input_get_cell(uint8_t *k);
