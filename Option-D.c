#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "string.h"
#include "stdlib.h"
#include "KPD.h"
#include "LCD.h"
#include "GPIO_INIT.h"
#include "functions.h"
#include "GPIO_INIT.h"

extern int m,s;

//take_cooking_time function returns "1" if taking the time is successful,
//returns "0" if the entered time is invalid *not between 1-30*,
//returns *2* if letters are entered.

uint32_t take_cooking_time(void)
{
	char D1='I',D2='I',D3='I',D4='I';    //variables to store numbers entered from keypad
  char text_s[10] = {'0','0',0};       //temp array to store the digits entered
	char text_m[10] = {'0','0',0};       //variables to store the changed values(m and s) from char to integers
	m=0,s=0;
	lcd_gotoxy(7,2);
	lcd_write_string("00:00");
	
	D1=Keypad_Getkey();                 //taking the first digit from the keypad
	lcd_gotoxy(11,2);
	lcd_write(D1);
	if((D1=='A') || (D1=='B') || (D1=='C') || (D1=='D') || (D1=='#') || (D1=='*'))
	{
		return 2;
	}
	Systick_n10ms(30);
	if((D1!='I') && (D2=='I') && (D3=='I') && (D4=='I') )  //converting digits from *char* to *int*
	{
		text_s[1]= D1;
		s=atoi(text_s);
		if(Keypad_Getkey()=='S')             //time taken, go to cook
		{
			return 1;
		}
	}
	
	D2=Keypad_Getkey();               //taking the second digit from the keypad
	lcd_gotoxy(10,2);
	lcd_write(D1);
	lcd_gotoxy(11,2);
	lcd_write(D2);
	if((D2=='A') || (D2=='B') || (D2=='C') || (D2=='D') || (D2=='#') || (D2=='*'))
	{
		return 2;
	}
	Systick_n10ms(30);
	if((D1!='I') && (D2!='I') && (D3=='I') && (D4=='I'))  //converting digits from *char* to *int*
	{
			text_s[0]=D1;
			text_s[1]=D2;
			s=atoi(text_s);
		
		  if(s==60)
			{
				s=0;
				m=1;
			}
			else if(s>60)
			{
				s=s-60;
				m=1;
			}
			
		  if(Keypad_Getkey()=='S')            //time taken, go to cook
		  {
				return 1;
		  }
	}
	
	D3=Keypad_Getkey();            //taking the third digit from the keypad
	lcd_gotoxy(8,2);
	lcd_write(D1);
	lcd_gotoxy(10,2);
	lcd_write(D2);
	lcd_gotoxy(11,2);
	lcd_write(D3);
	if((D3=='A') || (D3=='B') || (D3=='C') || (D3=='D') || (D3=='#') || (D3=='*'))
	{
		return 2;
	}
  Systick_n10ms(30);
	if((D1!='I') && (D2!='I') && (D3!='I') && (D4=='I'))  //converting digits from *char* to *int*
	{
  	  text_s[0]=D2;
	    text_s[1]=D3;
	    s=atoi(text_s);
		
	  	text_m[1]=D1;
	  	m=atoi(text_m);
	    
      if(s==60)
			{
				s=0;
				m++;
			}
      else if(s>60)
			{
				s=s-60;
				m++;
			}				
		
      
      if(Keypad_Getkey()=='S')     //time taken, go to cook
		  {
				return 1;
		  }		
	}
	
	D4=Keypad_Getkey();           //taking the fourth digit from the keypad
	lcd_gotoxy(7,2);
	lcd_write(D1);
	lcd_gotoxy(8,2);
	lcd_write(D2);
	lcd_gotoxy(10,2);
	lcd_write(D3);
	lcd_gotoxy(11,2);
	lcd_write(D4);
	if((D4=='A') || (D4=='B') || (D4=='C') || (D4=='D') || (D4=='#') || (D4=='*'))
	{
		return 2;
	}
	Systick_n10ms(30);
	if((D1!='I') && (D2!='I') && (D3!='I') && (D4!='I'))  //converting digits from *char* to *int*
	{
		text_s[1]=D4;
		text_s[0]=D3;
		s=atoi(text_s);
	
		text_m[1]=D2;
		text_m[0]=D1;
		m=atoi(text_m);
		if(s==60)
		{
			s=0;
			m++;
		}
		else if(s>60)
		{
			s=s-60;
			m++;
		}
		
		if((m>30)||((m>=30)&&(s>=1)))  //checking if the time entered is valid
		{
			return 0;
		}
		
		while(1)
		{
			if(Keypad_Getkey()=='S')   //time taken, go to cook
		  {
				return 1;
		  }
		
		}
		
	}	
}

void Option_D()
{
	uint32_t take_cooking_time_return;
	lcd_cmd(lcd_Clear);
	lcd_cmd(first_line1);
	Vaild:
	lcd_write_string("Cooking Time?");
	take_cooking_time_return=take_cooking_time();
	if(take_cooking_time_return==1)
	{ 
        lcd_cmd(lcd_Clear);
        Systick_n10ms(200);
	      counts_min_sec(m,s);
        food_ready();
	}
	else if(take_cooking_time_return==0)
	{
		lcd_cmd(lcd_Clear);
 	  lcd_write_string("Enter valid time");
		Systick_n10ms(300);
		lcd_cmd(lcd_Clear);
		goto Vaild;
	}
	else if(take_cooking_time_return==2)
	{
		Systick_n10ms(30);
		lcd_cmd(lcd_Clear);
 	  lcd_write_string(" Enter numbers ");
		lcd_cmd(first_line2);
		lcd_write_string("      Only      ");
		Systick_n10ms(300);
		lcd_cmd(lcd_Clear);
		goto Vaild;
	}
}