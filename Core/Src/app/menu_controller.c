/*
 * menu_controller.c
 *
 *  Created on: Mar 27, 2026
 *      Author: Professional
 */

#include "menu_controller.h"
#include "enums.h"
#include "view.h"
#include "input.h"
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
    	int key = get_key_input();
    	if (key < 0)
    	    continue;
    	menu_handle_input((uint8_t)key);

        if (ui == UI_GAME)
            break;
    }

    *mode = game_mode;
    *n    = board_size;
}

void menu_init(void)
{
    ui = UI_MENU_MAIN;
    show_main();          // print only once
}

void menu_handle_input(uint8_t key)
{
	if (key == '0')
	{
	    ui = UI_MENU_MAIN;
	    show_main();
	    return;
	}

	switch (ui)
    {
    case UI_MENU_MAIN:
        if (key == '1') { show_rules(); ui = UI_RULES; }
        else if (key == '2') { show_mode_menu(); ui = UI_MENU_MODE;}
        else if (key != '\r' && key != '\n') {
            printf("\r\nInvalid option\r\n> ");
        }
        break;

    //
    case UI_MENU_MODE:
    	if (key == '1') {
    		game_mode = MODE_CLASSIC;
    	    printf("\r\nClassic mode selected\r\n");
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
    	else if (key == '2') {
    	    printf("\r\nSpeed mode selected\r\n");
    	    game_mode = MODE_SPEED;
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
    	else if (key == '3') {
    	    printf("\r\nTwo players mode selected\r\n");
    	    game_mode = MODE_2P;
    	    ui = UI_MENU_SIZE;
    	    show_choose_size();
    	}
        else if (key != '\r' && key != '\n') {
        printf("\r\nInvalid option\r\n> ");
        }
        break;

    //
    case UI_MENU_SIZE:
        if (key >= '3' && key <= '9') {
           /* board_size = (uint8_t)(b - '0'); // TODO!!!
            printf("\r\nBoard: %dx%d\r\n", board_size, board_size);*/
            board_size =  '3'-'0';  // TODO!!!!: enable real sizes later
            printf("\r\nBoard: %dx%d\r\n", board_size, board_size);
            ui = UI_GAME;
            printf("Press 0 to quit\r\n> ");
        }
        else if (key != '\r' && key != '\n') {
            printf("\r\nInvalid size (3-9)\r\n> ");
        }
        break;

    case UI_RULES:
        break;

    case UI_GAME:
        break;
    }
}
