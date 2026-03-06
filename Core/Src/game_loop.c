#include "game_loop.h"
#include "game_logic.h"
#include "ui_uart.h"
#include "main.h"
#include "input.h"
#include <stdio.h>

void game_loop_run(game_mode_t mode, uint8_t n)
{
    game_t g;
    game_init(&g, n, mode);

    uint32_t next500 = HAL_GetTick() + 500;
    ui_uart_render(&g);

    while (1)
    {
        uint8_t redraw = 0;

        // 1) tick 500ms
        if ((int32_t)(HAL_GetTick() - next500) >= 0)
        {
            next500 += 900;
            ui_uart_tick_ms(&g);   // only if show_numbers ^= 1
            redraw = 1;
        }

        // 2) human input q (not blocked):
        // return -2 == quit to main menu
        int cell = input_get_move(n);
        if (cell == -2)
            return;

        // 3) moves only while game is active
        if (g.state == GAME_IN_PROGRESS)
         {
             if (cell >= 0)
                 redraw |= game_apply_move(&g, (uint16_t)cell);
             if (g.state == GAME_IN_PROGRESS && ai_can_move_now(&g))
                 redraw |= game_ai_step(&g);
         }

        // 4) render

        if (redraw)
            ui_uart_render(&g);

        if (g.state != GAME_IN_PROGRESS)
        {
        	show_game_over(&g);

            while (1)
            {
                int c = getchar();
                if (c == 'q')
                    return;
            }
        }
    }
}
