#include "game_logic.h"
#include "main.h"
#include "config.h"

void game_init(game_t *g, uint8_t board_size, game_mode_t mode)
{
    g->mode = mode;
    g->board_size = board_size;
    g->turn = (HAL_GetTick() & 1);  // 0=X first, 1=O first (random) for classik/2P mode
    g->moves = 0;
    g->ai_next = HAL_GetTick() + TICK_MS;
    g->state = GAME_IN_PROGRESS;
    g->winner = CELL_EMPTY;

    for (uint8_t y = 0; y < board_size; y++)
        for (uint8_t x = 0; x < board_size; x++)
            g->board[y][x] = CELL_EMPTY;

}

uint8_t game_make_move(game_t *g, uint16_t cell)
{
    uint16_t max = (uint16_t)g->board_size * (uint16_t)g->board_size;
    if (cell >= max) return 0;

    uint8_t r = cell / g->board_size;
    uint8_t c = cell % g->board_size;

    if (g->board[r][c] != CELL_EMPTY)					// if cell empty?
        return 0;

    cell_t placed = (g->turn == 0) ? CELL_X : CELL_O;	//place X or O in the cell depending on whose turn it is
    g->board[r][c] = placed;
    g->moves++;												//moves counter

    if (game_check_winner(g))
    {
        g->state = GAME_WIN;
        g->winner = placed;
    }
    else if (game_is_draw(g))
    {
        g->state = GAME_DRAW;
    }

    g->turn ^= 1;
    return 1;												//move applied successfully (board state changed)
}

uint8_t game_check_winner(const game_t *g)
{
    uint8_t board_size = g->board_size;

    // rows
    for (uint8_t r = 0; r < board_size; r++)
    {
        cell_t first = g->board[r][0];
        if (first == CELL_EMPTY) continue;

        uint8_t c;
        for (c = 1; c < board_size; c++)
            if (g->board[r][c] != first)
                break;

        if (c == board_size) return 1;
    }

    // columns
    for (uint8_t c = 0; c < board_size; c++)
    {
        cell_t first = g->board[0][c];
        if (first == CELL_EMPTY) continue;

        uint8_t r;
        for (r = 1; r < board_size; r++)
            if (g->board[r][c] != first)
                break;

        if (r == board_size) return 1;
    }

    // main diagonal
    cell_t first = g->board[0][0];
    if (first != CELL_EMPTY)
    {
        uint8_t i;
        for (i = 1; i < board_size; i++)
            if (g->board[i][i] != first)
                break;

        if (i == board_size) return 1;
    }

    // secondary diagonal
    first = g->board[0][board_size-1];
    if (first != CELL_EMPTY)
    {
        uint8_t i;
        for (i = 1; i < board_size; i++)
            if (g->board[i][board_size-1-i] != first)
                break;

        if (i == board_size) return 1;
    }

    return 0;
}

uint8_t game_is_draw(const game_t *g)
{
	return (g->moves == g->board_size * g->board_size);  // still empty cells → not draw, no empty cells → draw
}

uint8_t game_player_move(game_t *g, uint16_t cell)
{
	if (g->mode == MODE_SPEED)
    g->turn = 0;   // human player = X
    return game_make_move(g, cell);
}

uint8_t speed_timer_ready(game_t *g)
{
    if ((int32_t)(HAL_GetTick() - g->ai_next) >= 0)
    {
        g->ai_next = HAL_GetTick() + TICK_MS;
        return 1;
    }
    return 0;
}

uint8_t ai_can_move_now(game_t *g)
{
    if (g->state != GAME_IN_PROGRESS)
        return 0;

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

//stupid AI -- TODO
uint8_t game_ai_step(game_t *g)
{
	if (g->mode == MODE_SPEED)
	g->turn = 1;
    uint16_t max = (uint16_t)g->board_size * (uint16_t)g->board_size;
    for (uint16_t cell = 0; cell < max; cell++)
    {
        uint8_t r = cell / g->board_size;
        uint8_t c = cell % g->board_size;

        if (g->board[r][c] == CELL_EMPTY)
        {
        	return game_make_move(g, cell); // make O (turn==1) and switch
        }
    }

    return 0; // no move possible
}

