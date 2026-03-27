#pragma once

#include <stdint.h>

#include "enums.h"
#include "game_logic.h"

void menu_init(void);
void ui_handle_input(uint8_t b);
ui_state_t get_game_state(void);
void render_gameboard_uart(game_t *g);
void ui_uart_tick_ms(game_t *g);
game_mode_t get_game_mode(void);
uint8_t get_game_size(void);
void menu_controller_run(game_mode_t *mode, uint8_t *n);
uint8_t ui_game_over_run(game_t *g);
void show_game_over_uart(game_t *g);
