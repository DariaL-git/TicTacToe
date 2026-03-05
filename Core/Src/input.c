#include "input.h"

static uint8_t handle_classic(game_t *g, uint8_t b)
{
    // TODO: сейчас заглушка
    (void)g; (void)b;
    return 0;
}

static uint8_t handle_speed(game_t *g, uint8_t b)
{
    return handle_classic(g, b);
}

uint8_t input_handle(game_mode_t mode, game_t *g, uint8_t b)
{
    switch (mode)
    {
    case MODE_CLASSIC: return handle_classic(g, b);
    case MODE_SPEED:   return handle_speed(g, b);
    default:           return handle_classic(g, b);
    }



}

static uint8_t handle_input_classic(game_t *g, uint8_t b)
{
    (void)g; (void)b;
    return 0; // TODO
}

static uint8_t handle_input_speed(game_t *g, uint8_t b)
{
    return handle_input_classic(g, b);
}
