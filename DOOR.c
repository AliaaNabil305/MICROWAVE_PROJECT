#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "stdlib.h"
#include "GPIO_INIT.h"
#include "timer_min_sec.h"
#include "functions.h"
#include "stdlib.h"

void switch_cases();
extern int s;
extern int m;
extern int SW1 ;
extern int SW2 ;
extern int SW3 ;
extern u8 Return_;
extern int temp_value_sec;
extern int temp_value_min;
char button;

//checking if any switches is pressed
void switches ()
{ 
	  while (1)
   	{		     	  
			SW3=SW3_input();
			if (SW3!=0)	
		  { 
				SW1=(Read_SW()&0x10);				
			  if (SW1==0) 
			  {
					button='1';
		    	switch_cases();
					while (1)
					{
						SW2=(Read_SW()&0x01);
						SW1=(Read_SW()&0x10);
						SW3=SW3_input();
					
						if (SW2==0 && SW3!=0)
						{
							button='2';
							switch_cases();
							break;
						}
						
						else if (SW1==0 && SW3!=0)
						{	
							button='3';
							switch_cases();
							break;
						}
					}	
				 }
				}	

	 else if (SW3==0)
		    {
					button='1';
					switch_cases();
					if(SW3_input()!=0)
					{
						  button='2';
							switch_cases();
							break;
					}
					break;
				}


				
			if (SW1 !=0)
			{
				break;
			}
	  }	
		
  }

	void switch_cases()
	{
				switch(button)
			{
				case '1': //pause
				{	
					 pause();
				   paused_time_leds();
			 }
				
				break;
				
					case '2': //continue
				{
				lcd_cmd(lcd_Clear);
				lcd_cmd(first_line1);
			  if (Return_=='A')
        {
					lcd_cmd(lcd_Home);
					lcd_write_string("Popcorn...");
				}
				else if (Return_=='B')
        {
					lcd_cmd(lcd_Home);
					lcd_write_string("Beef...");
				}
				else if (Return_=='C')
        {
					lcd_cmd(lcd_Home);
					lcd_write_string("Chicken...");
				}
				else if (Return_=='D')
        {
					lcd_cmd(lcd_Home);
					lcd_write_string("Cooking...");
				}		
				counts_min_sec(temp_value_min,temp_value_sec);
				}
				break;
				
					case '3': //reset
				{
					stop(); 
				} 
				break;		
			}
		}		
		