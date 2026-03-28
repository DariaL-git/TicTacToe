/*
 * time.c
 *
 *  Created on: Mar 28, 2026
 *      Author: Professional
 */
#include "stm32l4xx_hal.h"

uint32_t time_ms(void)
{
    return HAL_GetTick();
}
