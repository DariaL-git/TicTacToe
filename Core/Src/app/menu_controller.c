/*
 * menu_controller.c
 *
 *  Created on: Mar 27, 2026
 *      Author: Professional
 */

#include "menu_controller.h"
#include "enums.h"
#include "view.h"
#include <stdint.h>
#include <stdio.h>

static ui_state_t ui = UI_MENU_MAIN;
static game_mode_t game_mode = MODE_CLASSIC;
static uint8_t board_size;

void menu_controller_run(game_mode_t *mode, uint8_t *n)
{
    menu_init();

    while (1)
    {
        uint8_t b = getchar();
        if (b == '\r' || b == '\n') continue;

        ui_handle_input(b);

        if (get_game_state() == UI_GAME)
            break;
    }

    *mode = get_game_mode();
    *n    = get_game_size();
}

void menu_init(void)
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
    	    printf("\r\nClassic mode selected\r\n");
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
    	else if (b == '2') {
    	    printf("\r\nSpeed mode selected\r\n");
    	    game_mode = MODE_SPEED;
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
    	else if (b == '3') {
    	    printf("\r\nTwo players mode selected\r\n");
    	    game_mode = MODE_2P;
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
           /* board_size = (uint8_t)(b - '0'); // TODO!!!
            printf("\r\nBoard: %dx%d\r\n", board_size, board_size);*/
            board_size =  '3'-'0';  // TODO!!!!: enable real sizes later
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

//GETTERS

ui_state_t get_game_state(void)
{
    return ui;
}

uint8_t get_game_size(void)
{
    return board_size;
}

game_mode_t get_game_mode(void)
{
    return game_mode;
}
