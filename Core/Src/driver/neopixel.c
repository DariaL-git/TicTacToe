#include "neopixel.h"
#include "tim.h"

#define BUFFER_SIZE (LED_COUNT * 24 + 50)

static uint16_t CCR_Buffer[BUFFER_SIZE];
static uint8_t led_buffer[LED_COUNT][3]; // [led][G,R,B]

void neopixel_set(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{
    if (led >= LED_COUNT) return;

    led_buffer[led][0] = g;
    led_buffer[led][1] = r;
    led_buffer[led][2] = b;
}

void neopixel_clear(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        led_buffer[i][0] = 0;
        led_buffer[i][1] = 0;
        led_buffer[i][2] = 0;
    }
}

void neopixel_show(void)
{
    uint32_t idx = 0;

    for (uint8_t led = 0; led < LED_COUNT; led++)
    {
        uint32_t color =
            (led_buffer[led][0] << 16) |  // G
            (led_buffer[led][1] << 8)  |  // R
            (led_buffer[led][2]);         // B

        for (int8_t i = 23; i >= 0; i--)
        {
            if (color & (1 << i))
                CCR_Buffer[idx] = 40; // 1-bit
            else
                CCR_Buffer[idx] = 20; // 0-bit

            idx++;
        }
    }

    // reset (>50us)
    for (uint16_t i = idx; i < BUFFER_SIZE; i++)
    {
        CCR_Buffer[i] = 0;
    }

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)CCR_Buffer, BUFFER_SIZE);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    }
}
