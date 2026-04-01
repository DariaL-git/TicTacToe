#include "input_keyboard.h"
#include "spi.h"
#include "stm32l4xx_hal.h"
#include "time.h"
#include <stdint.h>
#include <stdio.h>

extern SPI_HandleTypeDef hspi1;

int input_get_key_keyboard(void)
{
    static uint8_t locked = 0;
    static uint32_t last_poll = 0;

    uint16_t spi_val = 0xFFFF;
    uint8_t i;
    int key_num = 0;
    uint32_t now = time_ms();

    //
    if ((now - last_poll) < 50)
        return -1;

    last_poll = now;

    //
    if (HAL_SPI_Receive(&hspi1, (uint8_t *)&spi_val, 1, 5) != HAL_OK)
        return -1;
   // printf("spi=0x%04X\r\n", spi_val);
    //
    for (i = 0; i < 16; i++)
    {
        if (((~spi_val) & (1U << i)) != 0)
        {
            key_num = i + 1;
            break;
        }
    }

    //
    if (key_num == 0)
    {
        locked = 0;
        return -1;
    }

    //
    if (locked)
        return -1;

    locked = 1;

    //
    if (key_num >= 1 && key_num <= 9)
        return '0' + key_num;

    if (key_num == 10)
        return '0';

    return -1;
}
