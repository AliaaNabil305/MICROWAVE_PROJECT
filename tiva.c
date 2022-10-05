#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "STD_TYPES.h"
#include "LCD.h"
#include "GPIO_INIT.h"
#include "KPD.h"
#include "functions.h"
#include "PopCorn.h"
#include "Beef-Chicken.h"
#include "Option-D.h"

int s;
int m ;
int SW1 ;
int SW2 ;
int SW3 ;
u8 Return_;

enum Options {PopCorn='A', beef='B', Chicken='C', CustomTime='D'};


int main()
{
	PortE_Init();
	PortF_Init();
	PortB_Init();
	Keypad_Init();
	init_lcd();
	Intialize_Systick();
	lcd_cmd(first_line1); //first line
	lcd_write_string("CSE211s Project");
	Systick_n10ms(100); //delay
	
	
	
		
	while(1)
  {
		SW3=SW3_input();
		SW1=(Read_SW()&0x10);
		
		
		if (SW3!=0)
		{ 
			lcd_cmd(lcd_Clear);
			lcd_cmd(first_line1); //first line
			lcd_write_string("Cooking Option");
			lcd_cmd(first_line2);
			lcd_write_string("enter option :");
		
			Return_=Keypad_Getkey(); //Return_ contain the option pressed
		
			switch(Return_)
			{
				case PopCorn:  //popcorn cooking
				{
					pop_corn();
				}
				break;
			
				case beef:  //beef cooking

				{
				  Beef();
				}
				break;
			
				case Chicken:  //chicken cooking
				{
					chicken();
		  	}
			  break;
			
				case CustomTime:  //manual cooking time
				{
					Option_D();
				}
				break;
				
			default:
			{
				lcd_cmd(lcd_Clear);
				lcd_write_string("   Please choose");
	      lcd_cmd(first_line2);
		    lcd_write_string(" a valid option ");
				Systick_n10ms(100);
				
			}
			break;
		}
	}
	
	
	else if (SW3 ==0)  // open door alert
	{
		lcd_cmd(first_line1); 
	  lcd_write_string("  Please close  ");
	  lcd_cmd(first_line2);
		lcd_write_string("    the door    ");
	}
 }
}