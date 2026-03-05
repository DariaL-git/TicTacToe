#include "game_logic.h"

void game_init(game_t *g, uint8_t n, game_mode_t mode)
{
    g->mode = mode;
    g->n = n;
    g->turn = CELL_X;
    g->moves = 0;


    for (uint8_t y = 0; y < n; y++)
        for (uint8_t x = 0; x < n; x++)
            g->board[y][x] = CELL_EMPTY;

}
