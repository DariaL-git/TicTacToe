#include "input_keyboard.h"
#include "input.h"
#include "input_uart.h"

int get_key_input(void)
{
    int key;

    key = input_get_key_uart();
    if (key >= 0)
        return key;

    key = input_get_key_keyboard();
    if (key >= 0)
        return key;

    return -1;
}

