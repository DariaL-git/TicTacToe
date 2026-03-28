#include "stm32l4xx_hal.h"
#include "usart.h"
#include "input_uart.h"


extern UART_HandleTypeDef huart2;

static int uart_try_get(uint8_t *b)
{
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) == RESET)
        return 0;
    HAL_UART_Receive(&huart2, b, 1, 0);
    return 1;
}

int input_get_key_uart(void)
{
    uint8_t key;
    if (!uart_try_get(&key))
        return -1;

    if (key == '\r' || key == '\n')
        return -1;

    // only one symbol yet -> '1'..'9'!!!!!!!!!TODO
    if (key >= '0' && key <= '9')
        return (int)key;

    return -1;
}
