#include "game_logic.h"
#include "main.h"

void game_init(game_t *g, uint8_t n, game_mode_t mode)
{
    g->mode = mode;
    g->board_size = n;
    g->turn = (HAL_GetTick() & 1);  // 0=X first, 1=O first (random)
    g->moves = 0;
    g->ai_next = HAL_GetTick() + 900;
    g->state = GAME_IN_PROGRESS;


    for (uint8_t y = 0; y < n; y++)
        for (uint8_t x = 0; x < n; x++)
            g->board[y][x] = CELL_EMPTY;

}

uint8_t game_make_move(game_t *g, uint16_t cell)
{
    uint16_t max = (uint16_t)g->board_size * (uint16_t)g->board_size;
    if (cell >= max) return 0;
    uint8_t r = cell / g->board_size;
    uint8_t c = cell % g->board_size;

    if (g->board[r][c] != CELL_EMPTY)
        return 0;      									// if cell empty

    g->board[r][c] = (g->turn == 0) ? CELL_X : CELL_O; 	//place X or O in the cell depending on whose turn it is
    g->turn ^= 1;										//switch player
    g->moves++;											//moves counter
    return 1;											//move applied successfully (board state changed)

}


uint8_t game_check_winner(const game_t *g)
{
    uint8_t n = g->board_size;

    // rows
    for (uint8_t r = 0; r < n; r++)
    {
        cell_t first = g->board[r][0];
        if (first == CELL_EMPTY) continue;

        uint8_t c;
        for (c = 1; c < n; c++)
            if (g->board[r][c] != first)
                break;

        if (c == n) return 1;
    }

    // columns
    for (uint8_t c = 0; c < n; c++)
    {
        cell_t first = g->board[0][c];
        if (first == CELL_EMPTY) continue;

        uint8_t r;
        for (r = 1; r < n; r++)
            if (g->board[r][c] != first)
                break;

        if (r == n) return 1;
    }

    // main diagonal
    cell_t first = g->board[0][0];
    if (first != CELL_EMPTY)
    {
        uint8_t i;
        for (i = 1; i < n; i++)
            if (g->board[i][i] != first)
                break;

        if (i == n) return 1;
    }

    // secondary diagonal
    first = g->board[0][n-1];
    if (first != CELL_EMPTY)
    {
        uint8_t i;
        for (i = 1; i < n; i++)
            if (g->board[i][n-1-i] != first)
                break;

        if (i == n) return 1;
    }

    return 0;
}

uint8_t game_is_draw(const game_t *g)
{
    uint8_t n = g->board_size;

    for (uint8_t r = 0; r < n; r++)
        for (uint8_t c = 0; c < n; c++)
            if (g->board[r][c] == CELL_EMPTY)
                return 0;   // still empty cells → not draw

    return 1;               // no empty cells → draw
}

uint8_t game_apply_move(game_t *g, uint16_t cell)
{
    if (!game_make_move(g, cell))
        return 0;

    if (game_check_winner(g))
        g->state = GAME_WIN;
    else if (game_is_draw(g))
        g->state = GAME_DRAW;

    return 1;
}

uint8_t speed_timer_ready(game_t *g)
{
    if ((int32_t)(HAL_GetTick() - g->ai_next) >= 0)
    {
    	g->ai_next = HAL_GetTick() + 900;
        return 1;
    }
    return 0;
}

uint8_t ai_can_move_now(game_t *g)
{
    switch (g->mode)
    {
    case MODE_CLASSIC:
        if (g->turn != 1)     // AI = O
            return 0;
        return 1;

    case MODE_SPEED:
        return speed_timer_ready(g);

    default:
        return 0;
    }
}

uint8_t game_ai_step(game_t *g)
{
    uint16_t max = (uint16_t)g->board_size * (uint16_t)g->board_size;
    for (uint16_t cell = 0; cell < max; cell++)
    {
        uint8_t r = cell / g->board_size;
        uint8_t c = cell % g->board_size;

        if (g->board[r][c] == CELL_EMPTY)
        {
        	return game_apply_move(g, cell); // make O (turn==1) and switch
        }
    }

    return 0; // no move possible
}

