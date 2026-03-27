/*
 * menu_controller.h
 *
 *  Created on: Mar 27, 2026
 *      Author: Professional
 */

#ifndef INC_APP_MENU_CONTROLLER_H_
#define INC_APP_MENU_CONTROLLER_H_

#include "game_logic.h"

void ui_uart_show_main(void);
void ui_uart_show_mode_menu(void);
void ui_uart_show_size_menu(void);
void ui_uart_show_rules(void);

void ui_uart_tick_ms(game_t *g);
void ui_uart_render_game(const game_t *g);
void ui_uart_show_game_over(const game_t *g);

#endif /* INC_APP_MENU_CONTROLLER_H_ */
