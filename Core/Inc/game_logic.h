#pragma once
#include <stdint.h>

#define GAME_MAX_N 9

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

typedef struct {
    game_mode_t mode;					   // game mode
    uint8_t n;                             // size of board
    cell_t board[GAME_MAX_N][GAME_MAX_N];  // board array
    cell_t turn;                           // who turns?
    uint16_t moves;                        // number of turns
    uint32_t ai_next;						////!!!take away later
} game_t;

void game_init(game_t *g, uint8_t n, game_mode_t mode);
uint8_t speed_timer_ready(game_t *g);
uint8_t ai_can_move_now(game_t *g);
uint8_t game_ai_step(game_t *g);
// return 1 if move applied (board changed), else 0
uint8_t game_make_move(game_t *g, uint16_t cell);
