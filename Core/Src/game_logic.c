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

uint8_t game_make_move(game_t *g, uint16_t cell)
{
    uint16_t max = (uint16_t)g->n * (uint16_t)g->n;
    if (cell >= max) return 0;
    uint8_t r = cell / g->n;
    uint8_t c = cell % g->n;

    if (g->board[r][c] != CELL_EMPTY)
        return 0;      									// if cell empty

    g->board[r][c] = (g->turn == 0) ? CELL_X : CELL_O; 	//place X or O in the cell depending on whose turn it is
    g->turn ^= 1;										//switch player
    return 1;											//move applied successfully (board state changed)

}
