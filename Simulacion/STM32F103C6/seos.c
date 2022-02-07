#include <stm32f103x6.h>
#include <definitions.h>

#define TIME_button_scanning 50
#define TIME_matrix_refresh 100
#define TIME_state_machine_update 200

volatile uint8_t FLAG_button_scanning = 0;
volatile uint8_t FLAG_matrix_refresh = 0;
volatile uint8_t FLAG_state_machine_update = 0;

static uint16_t COUNTER_button_scanning = TIME_button_scanning - 1;
static uint16_t COUNTER_matrix_refresh = TIME_matrix_refresh - 1;
static uint16_t COUNTER_state_machine_update = TIME_state_machine_update - 1;

void seos_init(void);
void seos_task_scheduler(void);
uint8_t seos_get_flag(uint8_t flag);
void seos_clear_flag(uint8_t flag);


void seos_task_scheduler(void)
{
    if(++COUNTER_button_scanning >= TIME_button_scanning)
    {
        COUNTER_button_scanning = 0;
        FLAG_button_scanning = 1;
    }
    if(++COUNTER_matrix_refresh >= TIME_matrix_refresh)
    {
        COUNTER_matrix_refresh = 0;
        FLAG_matrix_refresh = 1;
    }
    if(++COUNTER_state_machine_update >= TIME_state_machine_update)
    {
        COUNTER_state_machine_update = 0;
        FLAG_state_machine_update = 1;
    }
}

uint8_t seos_get_flag(uint8_t flag)
{
    switch(flag)
    {
        case BUTTON_SCANNING:
            return FLAG_button_scanning;
        case MATRIX_REFRESH:
            return FLAG_matrix_refresh;
        case STATE_MACHINE:
            return FLAG_state_machine_update;
        default:
            return 0;
    }
}

void seos_clear_flag(uint8_t flag)
{
    switch(flag)
    {
        case BUTTON_SCANNING:
            FLAG_button_scanning = 0;
            break;
        case MATRIX_REFRESH:
            FLAG_matrix_refresh = 0;
            break;
        case STATE_MACHINE:
            FLAG_state_machine_update = 0;
            break;
    }
}
