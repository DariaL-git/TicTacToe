#include "view.h"
#include "output_uart.h"
#include "output_lcd.h"

void show_main(void)
{
	show_main_uart();
	show_main_lcd();
	//show_main_ring();
}

void show_main_scroll(void)
{
    show_main_lcd_scroll();
}

void show_win_animation(game_t *g)
{
    animate_game_over_lcd(g);
}

void show_rules(void)
{
    show_rules_uart();
    // show_rules_lcd();
    // show_rules_ring();
}

void show_choose_size(void)
{
	show_choose_size_uart();
	//show_choose_size_lcd();
	//show_choose_size_ring();
}

void show_mode_menu(void)
{
	show_mode_menu_uart();
	//show_mode_menu_lcd();
	//show_mode_menu_ring();
}

void render_gameboard(game_t *g)
{
    render_gameboard_uart(g);
}

void show_game_over(game_t *g)
{
	show_game_over_uart(g);
    show_game_over_lcd(g);
}

void update_numbers_output(game_t *g)
{
    (void)g;
    update_numbers_output_uart(g);
}

void animate_game_over(game_t *g)
{
    animate_game_over_lcd(g);
}
