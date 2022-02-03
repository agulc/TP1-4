/* Main.c file generated by New Project wizard
 *
 * Created:   Tue Jan 18 2022
 * Processor: STM32F103C6
 * Compiler:  Keil for ARM
 */

#include <stm32f103x6.h>
#include <spi_config.h>
#include <max7219.h>
#include <stdlib.h>
#include <delay.h>
#include <definitions.h>
#include <fsm.h>

int main (void)
{ 
// Write your code here

   uint8_t led_matrix[8][8] = {
                           {0},
                           {0},
                           {0},
                           {0},
                           {0},
                           {0},
                           {0},
                           {0},
   };
   int i;

   spi_init();
   max7219_init();

   fsm_state_selector(0, led_matrix);
   fsm_state_selector(0, led_matrix);
   max7219_load(led_matrix);
   max7219_refresh();


   while (1)
   {
      fsm_state_selector(START, led_matrix);
      max7219_load(led_matrix);
      max7219_refresh();
      delay_ms(1000);
      for (i = 0; i < 40; i++)
      {
         fsm_state_selector(0, led_matrix);
         max7219_load(led_matrix);
         max7219_refresh();
         delay_ms(100);
      }
      fsm_state_selector(START, led_matrix);
      max7219_load(led_matrix);
      max7219_refresh();
      fsm_state_selector(0, led_matrix);
      delay_ms(1000);
      fsm_state_selector(UP, led_matrix);
      max7219_load(led_matrix);
      max7219_refresh();
      delay_ms(1000);
      fsm_state_selector(0, led_matrix);
      delay_ms(1000);
   }
}   
