#pragma once
#include <stdint.h>
#include "enums.h"

void ui_init(void);
void ui_handle_input(uint8_t b);
ui_state_t ui_get_state(void);
