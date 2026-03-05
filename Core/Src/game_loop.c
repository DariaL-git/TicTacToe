#include "game_loop.h"
#include "game_logic.h"
#include "ui_uart.h"
#include "main.h"
#include "input.h"

extern UART_HandleTypeDef huart2;
static uint8_t handle_input_classic(game_t *g, uint8_t b);
static uint8_t handle_input_speed(game_t *g, uint8_t b);

static int uart_try_get(uint8_t *b)
{
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == RESET)
        return 0;

    HAL_UART_Receive(&huart2, b, 1, 0);
    return 1;
}


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
        uint8_t b;
        if (uart_try_get(&b))
        {
            if (b == 'q') return;
            redraw |= input_handle(mode, &g, b);
        }

        // 3) render only if needed
        if (redraw)
            ui_uart_render(&g);
    }
}



