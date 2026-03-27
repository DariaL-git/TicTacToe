/*
 * RC5-Decoder fuer IR-Fernbedienungen
 *
 * Version 1.1
 *
 * Joenen / HS Osnabrück 11.03.2025
 */
#include "rc5_decoder.h"

#define S_MIN 444*RC5_TIMERCLOCK_MHZ     // min short Impulstime
#define S_MAX 1333*RC5_TIMERCLOCK_MHZ    // max short Impulstime
#define L_MIN 1334*RC5_TIMERCLOCK_MHZ    // min long Impulstime
#define L_MAX 2222*RC5_TIMERCLOCK_MHZ    // max long Impulstime
#define FB_TIME 5000*RC5_TIMERCLOCK_MHZ  // Pause zwischen den Frames, Starterkennung

/* Zustände der RC5-Statemachine */
typedef enum
{
  M0,      /* Mitte Bit L  (RC5-Bit=0) */
  M1,      /* Mitte Bit H  (RC5-Bit=1) */
  S0,      /* Bit start L   */
  S1,      /* Bit start H   */
  RES      /* reset /start Zustand */
}tRC5_states_t;

/* Aufbau des RC5-Frames */
typedef struct {
	uint32_t command : 6;
	uint32_t addr    : 5;
	uint32_t toggle  : 1;
	uint32_t start_2 : 1;
	uint32_t start_1 : 1;
}RC_5_frame_t;

/* Separierung der Daten aus dem Frame-Datenbits */
volatile union {
  RC_5_frame_t framebits;
  uint32_t data;
}RC_5_converter;

/**
 * rc5_decoder
 *
 * Die RC5-Zustandsmaschine dekodiert ein RC5-Signal anhand der
 * übergebenen H- bzw. L-Impulslängen.
 *
 * Parameter:
 *           - puls : SH,SL,LH,LL ImpulsLängen (L=Long S=Short) + Pgeel (H ,L)
 */
uint8_t rc5_decoder(tRC5_pulse_t puls)
{
	static tRC5_states_t state = RES;
	static uint32_t rc5_bits=0;
	static uint8_t bit_count=0;

	switch(state)
	{

	case M0:
			rc5_bits <<= 1; // links shift für eine 0
			bit_count++;
			switch(puls)
			{
			case LL: state = M1;
					break;
			case SL: state = S0;
					break;
			default: state = RES;
			}
			break;
	case M1:
			rc5_bits <<= 1; // links shift für eine 0
			rc5_bits |= 1;	// 1 Bit dazu odern
			bit_count++;
			if ((bit_count==2)&&(rc5_bits!=3)) // ersten beiden Bits (S1,S2) muessen 1 sein, sonst Fehler !
			{
				state = RES;
			}
			else
				switch(puls)
				{
				case LH: state = M0;
						break;
				case SH: state = S1;
						break;
				default: state = RES;
						break;
				}
			break;
	case S0:
			if (puls == SH)
				state = M0;
			else
				state = RES;
			break;
	case S1:
			if (puls == SL)
				state = M1;
			else
				state = RES;
			break;
	case RES:
	default:
			rc5_bits=0;
		    bit_count=0;
		    if (puls==SL) state = M1;
	}

	if(bit_count==14)	//Ergebniss RC% Code gefunden
	{
		RC_5_converter.data=rc5_bits; // Frame speichern
		rc5_bits=0;
		bit_count=0;
		state = RES;
		return  1;
	}
	else
		return 0;
}

/**
 * rc5_capture_frame
 *
 * Diese Funktion soll in der CaptureCallback-Funktion aufgerufen werden.
 * Sie bestimmt die Impulslängen anhand der Capture-Register.
 * Das RC5-Signal wird als invertiertes Signal interpretiert, so wie es aus dem
 * IR-Sensor kommt, deswegen sind die übergebenen Impulse an den rc5_decoder()
 * ebenfalls invertiert.
 *
 * Parameter:
 * 			- *htim       : Zeiger auf den Timerhandler
 * 			- tim_channel : Die benutzte Kanalnummer
 * 			- puls_pin    : Pegel des Capture-Pins
 */
void rc5_capture_frame(TIM_HandleTypeDef *htim, HAL_TIM_ActiveChannel tim_channel, GPIO_PinState puls_pin)
{
	static uint8_t start=0;
	static uint32_t t_old=0xffffffff;
	uint32_t t_new,puls_len;
	tRC5_pulse_t puls;

	t_new=HAL_TIM_ReadCapturedValue(htim,  tim_channel);
	if (t_new < t_old)                  // Überlauf aufgetretetn?
		puls_len=t_new+(0xffff-t_old);  // Impulslänge berechenen (Überlauf berücksichtigt)
	else
		puls_len= t_new-t_old;          // Impulslänge berechenen

	if(start)
	{
		if (puls_pin == GPIO_PIN_RESET)
		{

			if ((puls_len >= S_MIN) && (puls_len <= S_MAX)) // kurzer Puls ?
				puls=SL;						// RC5 Signal ist ivertiert, deshalb SH
			else if  ((puls_len >= L_MIN) && (puls_len <= L_MAX)) // langer Puls
				puls=LL;
			else
				puls=SH; // Reset state-machine
		}
		else
		{
			if ((puls_len >= S_MIN) && (puls_len <= S_MAX)) // kurzer Puls ?
				puls=SH;						// RC5 Signal ist ivertiert, deshalb SH
			else if  ((puls_len >= L_MIN) && (puls_len <= L_MAX)) // langer Puls
				puls=LH;
			else
				puls=SL; // Reset state-machine
		}

		if (rc5_decoder(puls))
		{
			start=0;
			t_old=0xffffffff;
		}
	}
	if ((puls_len>FB_TIME)&&(puls_pin == GPIO_PIN_RESET)) // start RC5 Frame (Signal invertiert!)
	{
		puls=SL;
		start=1;
		rc5_decoder(puls);
	}
	t_old=t_new; //aktuellen Capture-Zählerwert sichern
}

/**
 * rc5_get_newframe
 *
 * Die Funktion gibt über die Parameterzeiger die Werte eines RC5-Frames zurück.
 * Die RC5-Werte sind nur gültig wenn die Funktion eine 1 zurück gibt.
 *
 * Parameter: (nicht benötigte Parameter können mit NULL-Zeiger belegt werden)
 *           -address : Geräteadresse der Fernbedienung
 *           -toggle  : Toggle-Bit (Ermöglicht das erfassen von mechfach-Tastendrücken)
 *           -command : Command-Code der jeweiligen Taste
 *
 * Rückgabe: 1 wenn ein neue Frame erfasst wurde,
 *           0 sonst.
 *
 */
uint8_t rc5_get_newframe(uint8_t *address, uint8_t* toggle, uint8_t* command)
{

	if (RC_5_converter.data!=0)
	{
		if (address!=NULL) *address=RC_5_converter.framebits.addr;
		if (toggle!=NULL)  *toggle=RC_5_converter.framebits.toggle;
		if (command!=NULL) *command=RC_5_converter.framebits.command;
		RC_5_converter.data=0;
		return 1;
	}
	else
		return 0;
}

