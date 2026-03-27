#include "tim.h"

volatile uint16_t CCR_Buffer[24+50]; // 24 Werte (3 Farben je 8 Bit) + 50 * 0 (50us RET)

/* set_color:    Setzt die Helligkeit der drei Farben
 * Parameter :   red - Helligkeit für rot (0=aus ... 255=max)
 *               green - Helligkeit für gruen (0=aus ... 255=max)
 *               blue - Helligkeit für blau (0=aus ... 255=max)
 */
void set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t led_data = (green<<16)|(red<<8)|(blue); // Datenbits in GRB-Folge

    for (int i=0; i<=23; i++)
    {
        if (led_data & (1<<(23-i)))   // MS-Bit zuerst !
            CCR_Buffer[i]=40;         // 1-Bit
        else
            CCR_Buffer[i]=20;         // 0-Bit
    }

    for (int i=24; i<74; i++) CCR_Buffer[i] = 0; // >50us Reset

    // Timer mit DMA starten
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *) CCR_Buffer, 74);
}

// Pulse Finished Callback wird genutzt um den Timer 1 auszuschalten
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1); // Stoppe Timer
}
