#include "output_lcd.h"
#include "i2c_lcd.h"

void show_main_lcd(void)
{
    lcd_clr();
    lcd_cur_pos(0, 0);
    lcd_put_str("TIC TAC TOE");
    lcd_cur_pos(0, 1);
    lcd_put_str("1:R 2:P");
}
