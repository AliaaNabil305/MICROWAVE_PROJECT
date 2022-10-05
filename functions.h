#include <stdint.h>
#include "STD_TYPES.h"
void Intialize_Systick();
void Systick(uint32_t delay);
void Systick_n10ms(uint32_t n);
void counts_min_sec(int m, int s );
int SW3_input(void);
uint32_t Read_SW(void);
void runing_time_leds(void);
void paused_time_leds(void);
void counts_min_sec(int m, int s );
void food_ready(void);
void pause (void);
void stop (void) ;
char* itoa(int value, char* buffer, int base);