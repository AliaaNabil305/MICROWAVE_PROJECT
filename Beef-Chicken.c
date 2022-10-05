#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "LCD.h"
#include "KPD.h"
#include "GPIO_INIT.h"
#include "functions.h"

extern int s;
extern int m;
char N_K[3]={'0','0',0}; //declaring empty array
char * no_of_kilos=N_K;
char x='I'; //keypad input
char buffer[33];


void kilos_check_chicken (void) //calculating the timer from number fo kilos entered
{
	int int_no_of_kilos=0;
	float timer =0 ;
  no_of_kilos=itoa(0,buffer,10);
	m=0;
	s=0;
  if ((x== '1')||(x== '2')||(x== '3')||(x== '4')||(x== '5')	||(x== '6')||(x== '7')||(x== '8')||(x== '9')) //integer from 1 to 9
	{
		lcd_cmd(lcd_Clear);
		lcd_gotoxy(8,1);
		lcd_write(x);
		lcd_write_string("kg");
		no_of_kilos[0]=x;
		int_no_of_kilos=atoi(no_of_kilos);
		timer=(int_no_of_kilos*12) ; //12 seconds 
		no_of_kilos=itoa(timer,buffer,10);
		Systick_n10ms(200);
		while (timer>=60)
		{ 
			m=m+1;
			timer=timer-60;
		}
		s=timer;
		counts_min_sec(m,s);
			 
	}
		
	else //in case no integer or different type is entered
	{
		lcd_cmd(0x01);
		lcd_write_string("       Err");
		Systick_n10ms(200);
		lcd_cmd(lcd_Clear);
		lcd_write_string("Chicken weight:");
    x=Keypad_Getkey();
		kilos_check_chicken();
	}

}
	
	
void chicken (void) // C for chicken cooking
{
	lcd_cmd(lcd_Clear);
	lcd_write_string("Chicken weight:");
	Systick_n10ms(200);
  x=Keypad_Getkey();	
  kilos_check_chicken();
	food_ready();
}



void kilos_check_Beef (void) //calculating the timer from number fo kilos entered
{
	int int_no_of_kilos=0;
	float timer =0 ;
  no_of_kilos=itoa(0,buffer,10);
	m=0;
	s=0;
  if ((x== '1')||(x== '2')||(x== '3')||(x== '4')||(x== '5')	||(x== '6')||(x== '7')||(x== '8')||(x== '9')) //integer from 1 to 9
	{
		lcd_cmd(lcd_Clear);
		lcd_gotoxy(8,1);
		lcd_write(x) ; 
		lcd_write_string("kg");
		no_of_kilos[0]=x;
		int_no_of_kilos=atoi(no_of_kilos);
		timer=(int_no_of_kilos*30) ; //30 seconds 
		no_of_kilos=itoa(timer,buffer,10);
		Systick_n10ms(200);
		while (timer>=60)
		{ 
			m=m+1;
			timer=timer-60;
		}
		s=timer;
		counts_min_sec(m,s);
			 
	}
		
	else //in case no integer or different type is entered
	{
		lcd_cmd(0x01);
		lcd_write_string("       Err");
		Systick_n10ms(200);
		lcd_cmd(lcd_Clear);
		lcd_write_string("Beef weight:");
    x=Keypad_Getkey();
		kilos_check_Beef();
	}

}




void Beef (void) // B for beef cooking
{
	lcd_cmd(lcd_Clear);
	lcd_write_string("Beef weight:");
	Systick_n10ms(200);
  x=Keypad_Getkey();
  kilos_check_Beef();
  food_ready();
}