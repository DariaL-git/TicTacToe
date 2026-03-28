#include "view.h"
#include <stdio.h>
#include <stdint.h>
#include "output_uart.h"

void show_main(void)
{
	show_main_uart();
	//show_main_lcd();
	//show_main_ring();
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
}

void update_numbers_output(game_t *g)
{
    (void)g;
    update_numbers_output_uart(g);
}



/*
//Periphery

void show_main_lcd(void)
{
	printf("tut LCD");
}

void show_main_ring(void)
{
	printf("tut ring");
}

void show_choose_size_lcd(void)
{
	printf("tut LCD");
}

void show_choose_size_ring(void)
{
	printf("tut ring");
}

void show_mode_menu_lcd(void)
{
	printf("tut LCD");
}

void show_mode_menu_ring(void)
{
	printf("tut ring");
}

*/









