#include "output_lcd.h"
#include "i2c_lcd.h"
#include <string.h>

void show_main_lcd(void)
{
    lcd_clr();
    lcd_cur_pos(0, 0);
    lcd_put_str("=MENU=");
    lcd_cur_pos(0, 1);
    lcd_put_str("1:R 2:P");
}

void show_main_lcd_scroll(void)
{
    static const char text[] = " TIC TAC TOE ";
    static uint8_t offset = 0;
    char buf[9];
    uint8_t len = (uint8_t)strlen(text);

    for (uint8_t i = 0; i < 8; i++)
    {
        buf[i] = text[(offset + i) % len];
    }
    buf[8] = '\0';

    lcd_cur_pos(0, 0);
    lcd_put_str(buf);

    offset++;
    if (offset >= len)
        offset = 0;
}

void show_game_over_lcd(game_t *g)
{
    lcd_clr();

    if (g->state == GAME_WIN)
    {
        lcd_cur_pos(0, 0);
        if (g->winner == CELL_X)
            lcd_put_str("X   X");
        else
            lcd_put_str("O   O");

        lcd_cur_pos(0, 1);
        lcd_put_str(" ___ ");
    }
    else if (g->state == GAME_DRAW)
    {
        lcd_cur_pos(0, 0);
        lcd_put_str("-   -");
        lcd_cur_pos(0, 1);
        lcd_put_str(" ___ ");
    }
}

void animate_game_over_lcd(game_t *g)
{
    static uint8_t state = 0;

    if (g->state != GAME_WIN)
        return;

    lcd_cur_pos(0, 1);
    if (state)
        lcd_put_str(" ___ ");
    else
        lcd_put_str(" \x5C_/ ");

    state ^= 1;
}
