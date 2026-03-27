#include "input.h"
#include "main.h"
#include "usart.h"


extern UART_HandleTypeDef huart2;

static int uart_try_get(uint8_t *b)
{
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == RESET)
        return 0;
    HAL_UART_Receive(&huart2, b, 1, 0);
    return 1;
}

int input_get_move(uint8_t n)
{
    uint8_t b;
    if (!uart_try_get(&b))
        return -1;

    if (b == 'q')
        return -2;

    // only one symbol yet -> '1'..'9'!!!!!!!!!TODO
    if (b >= '1' && b <= '9')
    {
        uint16_t cell = (uint16_t)(b - '1');        // '1'->0 ... '9'->8
        uint16_t max  = (uint16_t)n * (uint16_t)n;  // n*n

        if (cell < max)
            return (int)cell;
    }

    return -1;
}
