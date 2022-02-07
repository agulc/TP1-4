#include <stm32f103x6.h>

void seos_init(void);
void seos_task_scheduler(void);
uint8_t seos_get_flag(uint8_t flag);
void seos_clear_flag(uint8_t flag);
