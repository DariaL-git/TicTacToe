/*
 * Funktionen zum Midas I2C-LCD 2x8 (MC20805A6W-BNMLWI-V2)
 *
 * Version 1.1
 *
 * Joenen / HS Osnabrück 24.02.2026
 */
#include "i2c_lcd.h"
#include <string.h>

#define LCD_I2C_ADDR 0x78           // I2C Adresse der LCD Anzeige
I2C_HandleTypeDef* lcd_hi2c=NULL;   // Zeigerhandle zum I2C

/*************************************************
* lcd_init: Initiierung der RW1063 Register
*           für das 2x8 LCD
*
*  Parameter: Zeiger auf I2C Handler
*************************************************/
void lcd_init(I2C_HandleTypeDef* hi2c)
{
	lcd_hi2c=hi2c;
	uint8_t init_buf[]=
	{
			0x00, // (control byte) CO=0 (nur ein Control-byte), A0=0 Instructions
	        0x38, // Function_set    DL=1 (I2C),  N=1 (2 Lines), F=0 (5x8 dots)
	        0x14, // Cursor shift right
	        0x0F, // Display on (D=1), Cursor on (C=1), Blink on (B=1)
            0x06, // Entry_mode_set   ID=1, S=0
	};
	HAL_Delay(40); // 40ms warten nach Power on
    HAL_I2C_Master_Transmit(lcd_hi2c, LCD_I2C_ADDR, init_buf, sizeof(init_buf), HAL_MAX_DELAY);

    lcd_clr();    // LCD Clear nicht direkt in der Initierung weil clear bis zu 0.8 ms dauert
    lcd_home();   // LCD Home nicht direkt in der Initierung weil home bis zu 0.8 ms dauert
}

/**
 * write_data
 *
 *  interne Funktion zum senden von Daten
 **/
static void write_data(uint8_t data)
{
	uint8_t buf[2];

	buf[0] = 0x40; // CO=0 (kein weiters Control-Byte), A0=1 (Daten fürs RAM)
	buf[1] = data;
    HAL_I2C_Master_Transmit(lcd_hi2c, LCD_I2C_ADDR, buf, 2, HAL_MAX_DELAY);
}

/**
 *  write_command
 *
 *  interne Funktion zum senden von Kommandos
 *
 **/
static void write_command(uint8_t cmd)
{
	uint8_t buf[2];

	buf[0] = 0x00;  // C0=0 (kein weiters Control-Byte), A0=0 (Instructions)
	buf[1] = cmd;
    HAL_I2C_Master_Transmit(lcd_hi2c, LCD_I2C_ADDR, buf, 2, HAL_MAX_DELAY);
}

/**
 * lcd_clr
 *
 *  Sende Kommando clear Display
 *  (schreibt in alle DDRAM-Adressen 0x20)
 **/
void lcd_clr(void)
{
	write_command(0x01);
	HAL_Delay(2);
}

/**
 * lcd_home
 *
 *  Sende Kommando home Cursor
 *  setzt den Cursor auf home position
 **/
void lcd_home(void)
{
	write_command(0x02);
	HAL_Delay(2);
}

/**
 * lcd_putc
 *
 *  Ein Zeichen c an aktueller Stelle ausgeben
 *
 *  Parameter:
 *              c : Zeichen aus dem CGROM
 *
 **/
void lcd_putc(char c)
{
	write_data(c);
}

/**
 * lcd_put_st
 *
 *  Schreibt einen String (in ASCII)
 *  Maximale Laenge 8 Zeichen
 *
 *  Parameter:
 *              str : Null-terminierter String
 **/
void lcd_put_str(char* str)
{
    while (*str != '\0')
    {
        lcd_putc(*str);
        str++;
    }
}
/**
 * lcd_cur_pos
 *
 *  Cursor an Stelle x,y
 *
 *  Parameter: x : Spalte 0-7
 *             y : Zeile 0-1
 **/
void lcd_cur_pos(uint8_t x, uint8_t y)
{
    uint8_t addr;

    if (x > 7) x = 7;
    if (y > 1) y = 1;

    if (y == 0)
        addr = x;
    else
        addr = 0x40 + x;

    write_command(0x80 | addr);
}

/**
 * lcd_set_cur_blink
 *
 * Ein-/Aus des Blink-Cursors
 *
 * Parameter:
 *             cur:   Cursor Unterstrich (on/off)
 *             blink: Cursor blinken (on/off)
 **/
void lcd_set_cur_blink(cursor_mode_t cur, cursor_mode_t blink)
{
    uint8_t cmd = 0x08;   // Display ON/OFF control
    cmd |= 0x04;          // Display an

    if (cur == on)
        cmd |= 0x02;

    if (blink == on)
        cmd |= 0x01;

    write_command(cmd);
}

