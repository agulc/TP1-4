#include <spi_config.h>
#include <stm32f103x6.h>

void spi_init(void);
void spi_send(uint8_t data);

void spi_init(void)
{
   RCC->APB2ENR |= (1<<2)|(1<<12);
   GPIOA->CRL = 0xB4B34444;
   SPI1->CR1 = 0x37C;
}

void spi_send(uint8_t data)
{
   SPI1->DR = data; 
   while((SPI1->SR & (1<<0)) == 0);
}
