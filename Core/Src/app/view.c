#include "view.h"
#include <stdio.h>
#include <stdint.h>
#include "enums.h"
#include "game_logic.h"

static uint8_t show_numbers = 1;

void show_main(void)
{
	show_main_uart();
	show_main_lcd();
	show_main_ring();
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
	show_choose_size_lcd();
	show_choose_size_ring();
}

void show_mode_menu(void)
{
	show_mode_menu_uart();
	show_mode_menu_lcd();
	show_mode_menu_ring();
}

void show_main_uart(void)
{
	printf("\033[2J\033[H");
	printf("\r\n=== TIC TAC TOE ===\r\n");
    printf("\r\n=== MENU ===\r\n");
    printf("1 - rules\r\n");
    printf("2 - play\r\n> ");
}

void show_mode_menu_uart(void)
{
	printf("\r\n\r\n\r\n");
    printf("\r\n=== CHOOSE MODE ===\r\n");
    printf("1 - Classic\r\n");
    printf("2 - Speed\r\n");
    printf("3 - two players\r\n");
    printf("0 - Back\r\n> ");
}

void show_choose_size_uart(void)
{
	printf("\r\n\r\n\r\n");
    printf("\r\n=== BOARD SIZE ===\r\n");
    printf("Enter size (3-9)\r\n");
    printf("0 - Back\r\n> ");
}

void show_rules_uart(void)
{
	//TODO!!!!!!!!!!!!!!!
	printf("\r\n\r\n\r\n");
    printf("\r\nRules: make 3 in a row. Blablabla!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
    printf("Press 0 to back.\r\n> ");
}


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



//

void ui_uart_tick_ms(game_t *g)
{
	(void)g;
    show_numbers ^= 1;
}

static void print_cell_uart(uint8_t idx, cell_t c)
{
    if (c == CELL_X) printf(" X ");
    else if (c == CELL_O) printf(" O ");
    else
    {
        if (show_numbers) printf(" %d ", idx+1);
        else              printf("   ");
    }
}

void render_gameboard_uart(game_t *g)
{
    printf("\033[2J\033[H");

	printf("Press q to quit\r\n");

    for (int r = 0; r < g->board_size; r++)
    {
        for (int i = 0; i < g->board_size; i++)
            printf("+---");
        printf("+\r\n|");

        for (int c = 0; c < g->board_size; c++)
        {
            int idx = r * g->board_size + c;
            print_cell_uart(idx, g->board[r][c]);
            printf("|");
        }
        printf("\r\n");
    }

    for (int i = 0; i < g->board_size; i++)
        printf("+---");
    printf("+\r\n");
}

void show_game_over_uart(game_t *g)
{
    render_gameboard_uart(g);

    if (g->state == GAME_WIN)
    {
        (g->turn == 0) ?
        printf("\r\nO wins!\r\n")
        : printf("\r\nX wins!\r\n");
    }
    else if (g->state == GAME_DRAW)
    {
        printf("\r\nDraw!\r\n");
    }

    printf("Press q to return\r\n");
}




