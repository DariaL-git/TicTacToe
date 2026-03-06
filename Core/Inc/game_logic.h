#pragma once
#include <stdint.h>
#include "enums.h"

#define GAME_MAX_N 9

typedef enum {
    MODE_CLASSIC,
    MODE_SPEED,
	MODE_2P
} game_mode_t;

typedef struct {
    game_mode_t mode;					   // game mode
    uint8_t board_size;                             // size of board
    cell_t board[GAME_MAX_N][GAME_MAX_N];  // board array
    uint8_t turn;          				   // 0 = X, 1 = O who turns?
    uint16_t moves;                        // number of turns
    uint32_t ai_next;
    game_state_t state;
} game_t;

void game_init(game_t *g, uint8_t board_size, game_mode_t mode);
uint8_t game_make_move(game_t *g, uint16_t cell);
uint8_t game_check_winner(const game_t *g);
uint8_t game_is_draw(const game_t *g);
uint8_t game_apply_move(game_t *g, uint16_t cell);
uint8_t speed_timer_ready(game_t *g);
uint8_t ai_can_move_now(game_t *g);
uint8_t game_ai_step(game_t *g);
