#pragma once

#include "game_logic.h"

void show_main_uart(void);
void show_mode_menu_uart(void);
void show_choose_size_uart(void);
void show_rules_uart(void);

void render_gameboard_uart(game_t *g);
void show_game_over_uart(game_t *g);
void update_numbers_output_uart(game_t *g);
