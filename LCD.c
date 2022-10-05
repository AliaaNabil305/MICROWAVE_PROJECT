#include "STD_TYPES.h"
#include "GPIO_INIT.h"
#include "tm4c123gh6pm.h"
#include "Lcd.h"

//Apply initialization sequence for LCD module
void init_lcd (void)                     
{
	/* Function Set  */
	lcd_cmd(lcd_FunctionSet8bit);
	delay_ms(1);

	
	/* Entry Mode Set  */
	lcd_cmd(lcd_EntryMode);
	delay_ms(1);
	
	/* Display ON OFF Control */
	lcd_cmd(lcd_DisplayOn);
	delay_ms(1);
	
	/* Clear Display */
	lcd_cmd(lcd_Clear);
	delay_ms(2);
	
	/* Return Home  */
	lcd_cmd(lcd_Home);
	delay_ms(2);
	
	return;
}



//Interface to send the configuration commands to the LCD Driver
void lcd_cmd(u8 cmd)            
{
	GPIO_PORTB_DATA_R=cmd;
	
	GPIO_PORTE_DATA_R=(LOW<<PIN1)|(LOW<<PIN2)|(HIGH<<PIN3);
	delay_ms(1);
	GPIO_PORTE_DATA_R=(LOW<<PIN1)|(LOW<<PIN2)|(LOW<<PIN3);
	delay_ms(50);
	
	return;
}




//Interface to write character on LCD screen
void lcd_write(u8 data)
{
	GPIO_PORTB_DATA_R=data;
	
	GPIO_PORTE_DATA_R=(HIGH<<PIN1)|(LOW<<PIN2)|(HIGH<<PIN3);
	delay_ms(1);
	GPIO_PORTE_DATA_R=(HIGH<<PIN1)|(LOW<<PIN2)|(LOW<<PIN3);
	delay_ms(50);
	
	return;
}



//Interface to write string on LCD screen
void lcd_write_string(u8 *str)  
{
	int		i=0;
	while(str[i]!='\0')
	{
		lcd_write(str[i]);
		i++;
		
	}
	
	delay_ms(100);
	
	return;
	
}


//Interface to start the writing process at certain digit in the LCD
void lcd_gotoxy(u8 x,u8 y)    
{
	u8 firstcharadr[]={first_line1, first_line2}; // FirstCharAddress[0]=0x80  ,,,, FirstCharAddress[1]=0xC0 
	lcd_cmd(firstcharadr[y-1] + x - 1);
	delay_ms(50);
}




