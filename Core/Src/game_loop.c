#include "game_loop.h"
#include "game_logic.h"
#include "ui_uart.h"
#include "main.h"
#include "input.h"

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
            next500 += 500;
            ui_uart_tick_500ms(&g);   // only if show_numbers ^= 1
            redraw = 1;
        }

        // 2) input (not blocked)
        // return values:
        // -1 = no input
        // -2 = quit
        // 0..(n*n-1) = cell index
        int cell = input_get_move(n);

        if (cell == -2)
            return;

        if (cell >= 0)
        {
            redraw |= game_make_move(&g, (uint16_t)cell);
        }

        // 3) render only if needed
        if (redraw)
            ui_uart_render(&g);
    }
}



