#include <stdint.h>
#include "LCD.h"
#include "KPD.h"
#include "functions.h"
#include "GPIO_INIT.h"


void pop_corn(void)
{
	lcd_cmd(lcd_Clear);
	counts_min_sec(1,0); 
	food_ready();
}