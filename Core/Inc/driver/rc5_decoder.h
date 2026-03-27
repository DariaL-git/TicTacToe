/*
 * RC5-Decoder fuer IR-Fernbedienung
 *
 * Version 1.0
 *
 * Joenen / HS Osnabrück 10.01.2024
 */
#ifndef INC_RC5_DECODER_H_
#define INC_RC5_DECODER_H_
#include "tim.h"
#include "stdint.h"

#ifndef RC5_TIMERCLOCK_MHZ
	#define RC5_TIMERCLOCK_MHZ  1  // Wenn keine Timer-Frequenz definiert 1 MHz
#endif

typedef enum
{
  LH,     /*!< RC5 Puls Long High  */
  LL,     /*!< RC5 Puls Long Low   */
  SH,     /*!< RC5 Puls Short High */
  SL,     /*!< RC5 Puls Short Low  */
} tRC5_pulse_t;


uint8_t rc5_decoder(tRC5_pulse_t puls);
void rc5_capture_frame(TIM_HandleTypeDef *htim, HAL_TIM_ActiveChannel tim_channel, GPIO_PinState puls_pin);
uint8_t rc5_get_newframe(uint8_t *address, uint8_t* toggle, uint8_t* command);
#endif /* INC_RC5_DECODER_H_ */
