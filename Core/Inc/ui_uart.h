#pragma once

#include <stdint.h>

#include "enums.h"
#include "game_logic.h"

void ui_init(void);
void ui_handle_input(uint8_t b);

ui_state_t ui_get_state(void);

void ui_uart_render(game_t *g);
void ui_uart_tick_500ms(game_t *g);

game_mode_t ui_get_mode(void);
uint8_t ui_get_size(void);

void ui_menu_run(game_mode_t *mode, uint8_t *n);
