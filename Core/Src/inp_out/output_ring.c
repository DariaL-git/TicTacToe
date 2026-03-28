#include "output_ring.h"
#include "neopixel.h"

static uint8_t pos = 0;

void ring_reset(void)
{
    pos = 0;
    neopixel_clear();
    neopixel_show();
}

void ring_add_player_move(void)
{
    if (pos >= LED_COUNT) return;

    neopixel_set(pos, 0, 255, 0); //
    pos++;
    neopixel_show();
}

void ring_add_ai_move(void)
{
    if (pos >= LED_COUNT) return;

    neopixel_set(pos, 255, 0, 0); //
    pos++;
    neopixel_show();
}
