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

int get_key_input(void)
{
    uint8_t key;
    if (!uart_try_get(&key))
        return -1;

    if (key == '\r' || key == '\n')
        return -1;

    if (key == '0')
        return -2;   // global reset to main menu

    // only one symbol yet -> '1'..'9'!!!!!!!!!TODO
    if (key >= '1' && key <= '9')
        return (int)key;

    return -1;
}
