#include <stm32f103x6.h>
#include <spi_config.h>
#include <max7219.h>
#include <stdlib.h>
#include <definitions.h>


typedef struct cells
{
   uint8_t previous_state;
   uint8_t current_state;
   uint8_t neighbors;
} cell;

cell playboard[BOARD_SIZE][BOARD_SIZE];
cell playboard_copy[BOARD_SIZE][BOARD_SIZE];


uint8_t state = BEGIN;

void fsm_state_selector(int button, uint8_t (*led_matrix)[BOARD_SIZE]);
uint8_t fsm_1_begin(void);
uint8_t fsm_2_ready(int button);
uint8_t fsm_3_reset(void);
uint8_t fsm_4_play(int button);
uint8_t fsm_5_set(int button);
uint8_t fsm_6_clear(void);
void fsm_clear_playboard(void);
void fsm_copy_playboard(void);
void fsm_to_led_matrix(uint8_t (*led_matrix)[BOARD_SIZE]);
uint8_t fsm_check_neighbors(void);


void fsm_state_selector(int button, uint8_t (*led_matrix)[BOARD_SIZE])
{
    switch (state)
    {
    case BEGIN:
        state = fsm_1_begin();
        break;
    case READY:
        state = fsm_2_ready(button);
        break;
    case RESET:
        state = fsm_3_reset();
        break;
    case PLAY:
        state = fsm_4_play(button);
        break;
    case SET:
        state = fsm_5_set(button);
        break;
    case CLEAR:
        state = fsm_6_clear();
        break;

    default:
        state = 2;
        break;
    }

    fsm_to_led_matrix(led_matrix);

}

uint8_t fsm_1_begin(void)
{
    uint8_t next_state = READY;

    fsm_clear_playboard();
    fsm_save_copy();
    fsm_first_draw();

    return next_state;
}

uint8_t fsm_2_ready(int button)
{
    uint8_t next_state = READY;

    switch (button)
    {
    case UP:
        next_state = RESET;
        break;
    case START:
        next_state = PLAY;
        break;
    default:
        break;
    }
    return next_state;
}

uint8_t fsm_3_reset(void)
{
    uint8_t next_state = READY;

    fsm_load_copy();

    return next_state;
}

uint8_t fsm_4_play(int button)
{
    uint8_t i, j, next_state = READY;
    if (button != START)
    {
        uint8_t next_state = PLAY;
        for (i = 0; i < BOARD_SIZE; i++)
        {
            for (j = 0; j < BOARD_SIZE; j++)
            {
                playboard[i][j].previous_state = playboard[i][j].current_state;
            }
        }

        for (i = 0; i < BOARD_SIZE; i++)
        {
            for (j = 0; j < BOARD_SIZE; j++)
            {
                playboard[i][j].neighbors = fsm_check_neighbors(i, j);

                if (playboard[i][j].current_state == 0)
                {
                    if (playboard[i][j].neighbors == 3)
                    {
                        playboard[i][j].current_state = 1;
                    }
                }
                else
                {
                    if (playboard[i][j].neighbors < 2 || playboard[i][j].neighbors > 3)
                    {
                        playboard[i][j].current_state = 0;
                    }
                }
            }
        }
        
    }
    return next_state;
}

uint8_t fsm_5_set(int button)
{
    uint8_t next_state = 5;
    return next_state;
}

uint8_t fsm_6_clear(void)
{
    uint8_t next_state = 5;
    return next_state;
}

void fsm_first_draw(void)
{
    playboard[0][3].current_state = 1;
    playboard[1][3].current_state = 1;
    playboard[2][3].current_state = 1;
    playboard[4][0].current_state = 1;
    playboard[4][2].current_state = 1;
    playboard[4][3].current_state = 1;
    playboard[4][4].current_state = 1;
    playboard[4][6].current_state = 1;
    playboard[4][7].current_state = 1;
    playboard[6][3].current_state = 1;
    playboard[7][3].current_state = 1;
}

void fsm_clear_playboard(void)
{
    uint8_t i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            playboard[i][j].previous_state = 0;
            playboard[i][j].current_state = 0;
            playboard[i][j].neighbors = 0;
        }
    }
}

void fsm_save_copy(void)
{
    uint8_t i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            playboard_copy[i][j].previous_state = playboard[i][j].previous_state;
            playboard_copy[i][j].current_state = playboard[i][j].current_state;
            playboard_copy[i][j].neighbors = playboard[i][j].neighbors;
        }
    }
}

void fsm_load_copy(void)
{
    uint8_t i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            playboard[i][j].previous_state = playboard_copy[i][j].previous_state;
            playboard[i][j].current_state = playboard_copy[i][j].current_state;
            playboard[i][j].neighbors = playboard_copy[i][j].neighbors;
        }
    }
}

void fsm_to_led_matrix(uint8_t (*led_matrix)[BOARD_SIZE])
{
    uint8_t i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            led_matrix[i][j] = playboard[i][j].current_state;
        }
    }
}

uint8_t fsm_check_neighbors(uint8_t i, uint8_t j)
{
    uint8_t neighbors = 0;

    if(i - 1 >= 0)
    {
        if (playboard[i-1][j].previous_state == 1)
        {
            neighbors++;
        }
    }

    if(i-1 >= 0 && j + 1 < BOARD_SIZE)
    {
        if (playboard[i-1][j+1].previous_state == 1)
        {
            neighbors++;
        }
    }

    if(j + 1 < BOARD_SIZE)
    {
        if (playboard[i][j+1].previous_state == 1)
        {
            neighbors++;
        }
    }

    if(i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE)
    {
        if (playboard[i+1][j+1].previous_state == 1)
        {
            neighbors++;
        }
    }

    if(i + 1 < BOARD_SIZE)
    {
        if (playboard[i+1][j].previous_state == 1)
        {
            neighbors++;
        }
    }

    if(i + 1 < BOARD_SIZE && j - 1 >= 0)
    {
        if (playboard[i+1][j-1].previous_state == 1)
        {
            neighbors++;
        }
    }

    if(j - 1 >= 0)
    {
        if (playboard[i][j-1].previous_state == 1)
        {
            neighbors++;
        }
    }
    
    if(i - 1 >= 0 && j - 1 >= 0)
    {
        if (playboard[i-1][j-1].previous_state == 1)
        {
            neighbors++;
        }
    }

    return neighbors;
}
