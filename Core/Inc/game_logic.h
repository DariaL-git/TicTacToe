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
    MODE_SPEED
} game_mode_t;

typedef struct {
    uint8_t n;                             // size of board
    cell_t board[GAME_MAX_N][GAME_MAX_N];  // board array
    cell_t turn;                           // who turns?
    uint16_t moves;                        // number of turns
} game_t;

void game_init(game_t *g, uint8_t n, game_mode_t mode);
