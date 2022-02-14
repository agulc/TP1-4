#include <stm32f103x6.h>
#include <definitions.h>
#include <delay.h>

void buttons_init(void);
uint8_t button_scan(uint8_t);
uint8_t button_press(void);
void button_release(void);

uint8_t button = NOP;

void buttons_init(void)
{
    RCC->APB2ENR |= (1<<3);
    GPIOB->CRL = 0x48888444;
    GPIOB->ODR |= (1<<3) | (1<<4) | (1<<5) | (1<<6);
}

uint8_t button_press(void)
{
    if(button_scan(6)) button = START;
    else if(button_scan(5)) button = SET;
    else if(button_scan(4)) button = RESET;
    else if (button_scan(3)) button = STOP;

    return button;
}

void button_release(void)
{
    button = NOP;
}

uint8_t button_scan(uint8_t pin)
{
    if ((GPIOB->IDR & (1<<pin)) == 0)
    {
        delay_ms(10);
        if ((GPIOB->IDR & (1<<pin)) == 0)
        {
            return 1;
        }
    }
    return 0;
}
