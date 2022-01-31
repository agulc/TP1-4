#include <max7219.h>
#include <spi_config.h>
#include <stm32f103x6.h>
#include <delay.h>


uint16_t matrix_lines[8] = {0};

void max7219_send(uint8_t cmd, uint8_t data);
void max7219_init(void);


void max7219_send(uint8_t cmd, uint8_t data)
{
    delay_ms(1);
    GPIOA->BRR = (1<<4); //Low signal enables chip selection
    spi_send(cmd);
    spi_send(data);
    GPIOA->BSRR = (1<<4); //High signal disables chip selection
}

void max7219_init(void)
{
    max7219_send(0x09, 0x00); //decode mode: No decode
    max7219_send(0x09, 0x00); //decode mode: No decode
    max7219_send(0x0a, 0x08); //brightness PWM: dutty cycle = 17/32
    max7219_send(0x0b, 0x07); //scan limit: 8 leds
    max7219_send(0x0c, 0x01); //Shutdown mode: Normal operation
    max7219_send(0x0f, 0x00); //test mode: No test
}

void max7219_refresh(void)
{
    volatile int i;
    for(i = 0; i < 8; i++)
    {
        max7219_send(i+1, matrix_lines[i]);
    }
    max7219_send(8, matrix_lines[7]);
}

void max7219_load(uint8_t (*playboard)[8])
{
    uint8_t i, j;
    for (j = 0; j < 8; j++)
    {
        matrix_lines[j] = 0;
        for (i = 0; i < 8; i++)
        {
            {
                matrix_lines[j] |= (playboard[j][i] << (7 - i));
            }
        }
    }
}
