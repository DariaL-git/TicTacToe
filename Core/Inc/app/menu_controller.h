#ifndef INC_APP_MENU_CONTROLLER_H_
#define INC_APP_MENU_CONTROLLER_H_

#include <stdint.h>
#include "enums.h"

void menu_init(void);
void menu_handle_input(uint8_t b);
void menu_controller_run(game_mode_t *mode, uint8_t *n);

#endif /* INC_APP_MENU_CONTROLLER_H_ */
