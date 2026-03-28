#include "input.h"
#include "input_uart.h"
#include "input_buttons.h"

int get_key_input(void)
{
    int key;

    key = input_get_key_uart();
    if (key >= 0)
        return key;

    key = input_get_key_button();
    if (key >= 0)
        return key;

    return -1;
}

