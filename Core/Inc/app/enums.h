#pragma once

typedef enum {
  UI_RULES,
  UI_MENU_MAIN,
  UI_MENU_MODE,
  UI_MENU_SIZE,
  UI_GAME
} ui_state_t;

typedef enum {
    GAME_IN_PROGRESS = 0,
    GAME_WIN,
    GAME_DRAW
} game_state_t;

typedef enum {
    CELL_EMPTY = 0,
    CELL_X,
    CELL_O
} cell_t;

typedef enum {
    MODE_CLASSIC,
    MODE_SPEED,
	MODE_2P
} game_mode_t;
