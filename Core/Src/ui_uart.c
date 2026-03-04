#include "ui_uart.h"
#include <stdio.h>
#include <stdint.h>
#include "enums.h"
#include "game_logic.h"



static void show_main(void)
{
	printf("\033[2J\033[H");
	printf("\r\n=== TIC TAC TOE ===\r\n");
    printf("\r\n=== MENU ===\r\n");
    printf("1 - rules\r\n");
    printf("2 - play\r\n> ");
}

static void show_mode_menu(void)
{
	printf("\r\n\r\n\r\n");
    printf("\r\n=== CHOOSE MODE ===\r\n");
    printf("1 - Classic\r\n");
    printf("2 - Speed\r\n");
    printf("0 - Back\r\n> ");
}

static void show_choose_size(void)
{
	printf("\r\n\r\n\r\n");
    printf("\r\n=== BOARD SIZE ===\r\n");
    printf("Enter size (3-9)\r\n");
    printf("0 - Back\r\n> ");
}

static void show_rules(void)
{
	//TODO!!!!!!!!!!!!!!!
	printf("\r\n\r\n\r\n");
    printf("\r\nRules: make 3 in a row. Blablabla!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
    printf("Press 0 to back.\r\n> ");
}



static ui_state_t ui = UI_MENU_MAIN;
static game_mode_t game_mode = MODE_CLASSIC;

void ui_init(void)
{
    ui = UI_MENU_MAIN;
    show_main();          // print only once
}

void ui_handle_input(uint8_t b)
{
    switch (ui)
    {

    //
    case UI_MENU_MAIN:
        if (b == '1') { show_rules(); ui = UI_RULES; }
        else if (b == '2') { show_mode_menu(); ui = UI_MENU_MODE;}
        else if (b != '\r' && b != '\n') {
            printf("\r\nInvalid option\r\n> ");
        }
        break;

    //
    case UI_MENU_MODE:
    	if (b == '1') {
    		game_mode = MODE_CLASSIC;
    	    printf("\r\nClassic selected\r\n");
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
    	else if (b == '2') {
    	    printf("\r\nSpeed not yet available -> Classic\r\n");
    	    game_mode = MODE_CLASSIC;
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
        else if (b == '0') {
            ui = UI_MENU_MAIN;
            show_main();
        }
        else if (b != '\r' && b != '\n') {
        printf("\r\nInvalid option\r\n> ");
        }
        break;

    //
    case UI_MENU_SIZE:
        if (b >= '3' && b <= '9') {
            uint8_t board_size = (uint8_t)(b - '0'); // TODO!!!
            printf("\r\nBoard: %dx%d\r\n", board_size, board_size);
            board_size =  '3'-'0';
            printf("\r\nBoard: %dx%d\r\n", board_size, board_size);
            ui = UI_GAME;
            printf("Press q to quit\r\n> ");
        }
        else if (b == '0') {
            ui = UI_MENU_MAIN;
            show_main();
        }
        else if (b != '\r' && b != '\n') {
            printf("\r\nInvalid size (3-9)\r\n> ");
        }
        break;

    //
    case UI_GAME:
        if (b == 'q') {
            ui = UI_MENU_MAIN;
            show_main();
        }
        break;

    //
        case UI_RULES:
            if (b == '0') { show_main(); ui = UI_MENU_MAIN; }
            break;
    }
}

ui_state_t ui_get_state(void)
{
    return ui;
}

