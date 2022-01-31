#include <stm32f103x6.h>
#include <definitions.h>

void fsm_state_selector(int button, uint8_t (*led_matrix)[BOARD_SIZE]);