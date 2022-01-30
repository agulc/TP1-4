#include <spi_config.h>
#include <stm32f103x6.h>

void spi_init(void);
void spi_send(uint8_t data);

void spi_init(void)
{
   RCC->APB2ENR |= 0xFC|(1<<12);
   GPIOA->CRL = 0xB4B34444; /* MOSI (PA7) and SCLK(PA5): alt. func. out, MISO (PA6): input, PA4 output */ 
   SPI1->CR1 = 0x37C; /* SPE = 1, BR = 7, FFD = 0, SSI and SSM = 1, CPHA = 0*/
}

void spi_send(uint8_t data)
{
   SPI1->DR = data; 
   while((SPI1->SR & (1<<0)) == 0);
}
