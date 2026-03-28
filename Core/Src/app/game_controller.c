#include "game_controller.h"
#include "game_logic.h"
#include "time.h"
#include "input.h"
#include "config.h"
#include "view.h"
#include <stdio.h>

void game_controller_run(game_mode_t mode, uint8_t board_size)
{
    game_t g;
    uint32_t now = time_ms();
    uint8_t first_turn = now & 1;
    game_init(&g, board_size, mode, first_turn, now);

    uint32_t next_ms = now + TICK_MS;
    uint32_t anim_next = now + TICK_MS;
    uint8_t game_over_shown = 0;
    render_gameboard(&g);

    while (1)
    {
        uint8_t redraw = 0;

        // 1) tick 500ms
        uint32_t now = time_ms();

        if ((int32_t)(now - next_ms) >= 0)
        {
            next_ms += TICK_MS;
            update_numbers_output(&g);
            redraw = 1;
        }

        // 2) human input q (not blocked):
        int key = get_key_input();

        // return == quit to main menu
        if (key == '0')
            return;

        // 3) moves only while game is active
               if (g.state == GAME_IN_PROGRESS)
                {
            	    if (key >= '1' && key <= '9')
            	    {
            	        int cell = key - '1';

            	        if (cell < board_size * board_size)
            	            redraw |= game_player_move(&g, (uint16_t)cell);
            	    }
                    if (g.state == GAME_IN_PROGRESS && ai_can_move_now(&g, now))
                        redraw |= game_ai_step(&g);
                }

        // 4) render
        if (redraw && g.state == GAME_IN_PROGRESS)
        render_gameboard(&g);

        if (g.state != GAME_IN_PROGRESS)
        {
            if (!game_over_shown)
            {
                show_game_over(&g);
                game_over_shown = 1;
                anim_next = now + TICK_MS;
            }

            if (g.state == GAME_WIN && (int32_t)(now - anim_next) >= 0)
            {
            	anim_next += TICK_MS;
                animate_game_over(&g);
            }

            continue;
        }
    }
}
