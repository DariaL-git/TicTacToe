/*
 * output_lcd.h
 *
 *  Created on: Mar 28, 2026
 *      Author: Professional
 */

#ifndef INC_INP_OUT_OUTPUT_LCD_H_
#define INC_INP_OUT_OUTPUT_LCD_H_
#include "game_logic.h"

void show_main_lcd(void);
void show_main_lcd_scroll(void);

void show_game_over_x_lcd(void);
void show_game_over_o_lcd(void);
void show_game_over_draw_lcd(void);
void animate_game_over_win_lcd(void);

void show_game_over_lcd(game_t *g);
void animate_game_over_lcd(game_t *g);

#endif /* INC_INP_OUT_OUTPUT_LCD_H_ */
