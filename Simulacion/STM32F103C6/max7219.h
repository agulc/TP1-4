#include <stm32f103x6.h>
void max7219_send(uint8_t cmd, uint8_t data);
void max7219_init(void);
void max7219_refresh(void);
void max7219_load(uint8_t (*playboard)[8]);
