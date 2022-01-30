#include <max7219.h>
#include <spi_config.h>
#include <stm32f103x6.h>


uint16_t matrix_lines[8] = {0};

void max7219_send(uint8_t cmd, uint8_t data);
void max7219_init(void);

void delay_msm(uint16_t time)
{  //Funcion de retardo
	volatile unsigned long l = 0;
	uint16_t i;
	
	for(i = 0; i < time; i++)
	{
		for(l = 0; l < 800; l++);
	}
}


void max7219_send(uint8_t cmd, uint8_t data)
{
    delay_msm(1);
    GPIOA->BRR = (1<<4); //Low signal enables chip selection
    spi_send(cmd);
    spi_send(data);
    GPIOA->BSRR = (1<<4); //High signal disables chip selection
}

void max7219_init(void)
{
    max7219_send(0x09, 0x00); //decode mode: No decode
    max7219_send(0x0a, 0x08); //brightness PWM: dutty cycle = 17/32
    max7219_send(0x0b, 0x07); //scan limit: 8 leds
    max7219_send(0x0c, 0x01); //Shutdown mode: Normal operation
    max7219_send(0x0f, 0x00); //test mode: No test
}

void max7219_refresh(void)
{
    uint8_t i;
    for (i = 1; i < 9; i++)
    {
	 max7219_send(i, matrix_lines[i - 1] );
    }
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
