#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "string.h"
#include "KPD.h"
#include "LCD.h"
#include "stdlib.h"
#include "GPIO_INIT.h"
#include "timer_min_sec.h"
#include "functions.h"
#define Delay_Value 800000

extern int s;
extern int m;
extern int SW1 ;
extern int SW2 ;
extern int SW3 ;
extern int temp_value_sec;
extern int temp_value_min;


//systic function
void Intialize_Systick() //here we intialize the systick timer
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R =0x00FFFFFF;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R |= 0x00000005;
}

void Systick(uint32_t delay) // function that makes systick timer count 10ms
{ 
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R=0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){}
}


void Systick_n10ms(uint32_t n) // timer= n*10ms
{
	unsigned long i;
	for(i=0;i<n;i++)
	{
		Systick(Delay_Value);
	}
}


// convertin integers to characters

// Function to swap two numbers
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
	int n = abs(value);
 
    int i = 0;
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}



//Leds options

// to end cooking function (blinking and buzzer)
void food_ready(void)
{
	unsigned long i;
	lcd_cmd(lcd_Clear);
	lcd_write_string(" Cooking done ");
	lcd_cmd(first_line2);
	lcd_write_string("     Hmmmm!     ");
	s=0;
	for(i=0;i<3;i++)
	{
		GPIO_PORTE_DATA_R |=0x11;
		GPIO_PORTF_DATA_R |=0x0E;
		Systick_n10ms(100);
		GPIO_PORTE_DATA_R &= ~(0x11);
		GPIO_PORTF_DATA_R &=~0x0E;
		Systick_n10ms(100);
	}
	lcd_cmd(lcd_Clear);
	lcd_cmd(first_line2);
	lcd_write_string("00:00");
}



//runing blinkig mode
void runing_time_leds(void)
{
	PortF_Init ();
	GPIO_PORTF_DATA_R |=0x0E; 
}

// pause blinking mode
void paused_time_leds (void)
{
	 while (1)
	 {
		GPIO_PORTF_DATA_R |=0x0E; 
	  Systick_n10ms(50);
		GPIO_PORTF_DATA_R &=~0x0E;
		Systick_n10ms(50);
	  if ((Read_SW()&0x01)==0||(Read_SW()&0x10)==0)
		{
			break;
		}
		else if (SW1!=0 && SW3_input()!=0)
		{
			break;
		}
	 }
}

//switches return

//SW3

int SW3_input(void){
		
	return(GPIO_PORTE_DATA_R&0X20);
}

//SW1 & SW2

uint32_t Read_SW()
{
	return (GPIO_PORTF_DATA_R) & 0x11;	
}

//Switches pressed cases
void pause () //sw1 is pressed for 1st time
{					
	lcd_cmd(lcd_Home);
	lcd_write_string("      Paused     ");		
}
		
		
void stop () //sw1 is pressed for 2nd time
{
	lcd_cmd(lcd_Clear);
	lcd_cmd(first_line2);
	lcd_write_string("      00:00     ");
	lcd_cmd(first_line1);
	lcd_write_string("   Reset timer  ");
	s=0;
	m=0;
}

