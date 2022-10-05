#ifndef LCD_H_
#define LCD_H_


#include "STD_TYPES.h"

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Value Options */
#define HIGH   1
#define LOW    0

/*
 -----------                   ----------
 |  TM4C123  |                 |   LCD    |
 |           |                 |          |
 |        PB7|---------------->|D7        |
 |        PB6|---------------->|D6        |
 |        PB5|---------------->|D5        |
 |        PB4|---------------->|D4        |
 |        PB3|---------------->|D3        |
 |        PB2|---------------->|D2        |
 |        PB1|---------------->|D1        |
 |        PB0|---------------->|D0        |
 |           |                 |          |
 |        PE3|---------------->|E         |
 |        PE2|---------------->|RW        |
 |        PE1|---------------->|RS        |
 -----------                   ----------
 */

#define lcd_Clear            0x01          // replace all characters with ASCII 'space'
#define lcd_Home             0x02          // return cursor to first position on first line
#define lcd_EntryMode        0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff       0x08          // turn display off
#define lcd_DisplayOn        0x0F          // display on
#define lcd_FunctionReset    0x30          // reset the LCD
#define lcd_FunctionSet8bit  0x38          // 8-bit data, 2-line display, 5 x 7 font
#define first_line1          0x80          // set cursor position in first row
#define first_line2          0xC0          // set cursor position in second row



//Interface to send the configuration commands to the LCD Driver
void lcd_cmd(u8 cmd);

//Apply initialization sequence for LCD module
void init_lcd(void);   

//Interface to write character on LCD screen        
void lcd_write(u8 data);    

//Interface to write string on LCD screen
void lcd_write_string(); 

//Interface to start the writing process at certain digit in the LCD
void lcd_gotoxy(u8 x,u8 y);

#endif