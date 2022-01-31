#include <stm32f103x6.h>
void delay_ms(uint16_t time);

void delay_ms(uint16_t time)
{  //Funcion de retardo
	volatile unsigned long l = 0;
	uint16_t i;
	
	for(i = 0; i < time; i++)
	{
		for(l = 0; l < 667; l++);
	}
}
