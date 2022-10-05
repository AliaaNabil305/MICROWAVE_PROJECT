#include "KPD.h"
#include "STD_TYPES.h"
#include "tm4c123gh6pm.h"
#include "functions.h"

u8 symbol[N_row][N_col] = {{ '1', '2',  '3', 'A'},      
                           { '4', '5',  '6', 'B'},      
                           { '7', '8',  '9', 'C'},      
                           { '*', '0',  '#', 'D'}};

													 
// Keypad_Init() configures PORTC and PORTA to scan keypad keys
void Keypad_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x00000005;        //Enable clock for PORTA and PORTC  
  while ((SYSCTL_PRGPIO_R&0x05) == 0){};  //Wait for clock to be setted
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTC_LOCK_R = 0x4C4F434B;
  GPIO_PORTC_CR_R |= 0xF0;             //Allow settings for pins (4,5,6,7) of PORTC
  GPIO_PORTA_CR_R |= 0x3C;             //Allow settings for pins (2,3,4,5) of PORTA
	GPIO_PORTC_DIR_R |= 0xF0;             //PC4-PC7 are used with row and set them as digital output pins
  GPIO_PORTA_DIR_R = 0x00;             //PA2-PA5 are used with col and set them as digital input pins
  GPIO_PORTA_PDR_R = 0x3C;             //Enable pull down resistor on PORTA for rows
  GPIO_PORTC_DEN_R |= 0xF0;
  GPIO_PORTA_DEN_R = 0x3C;
	GPIO_PORTA_AMSEL_R = 0x00;
	GPIO_PORTA_AFSEL_R = 0x00;
	GPIO_PORTA_PCTL_R = 0x00000000;
}

//Keypad_getkey() function returns the value of key pressed by the user and returns 'S' if SW1 is pressed
u8 Keypad_Getkey(void)
{
	unsigned long i;
	unsigned long j;
  while(1)
  {
    if((Read_SW()&0x10)==0x00)
		{
			return 'S';
		}
    
		for(i = 0; i < N_col; i++)    //Scan columns loop
    {
      GPIO_PORTC_DATA_R = (1 << (i+4));
      delay_us(2);
      for(j = 0; j < N_row; j++)  //Scan rows loop
      {
        if((GPIO_PORTA_DATA_R & 0x3C) & (1 << (j+2)))
          return symbol[j][i];
      }
    }
  }
}

// Micro seconds delay function
void delay_us(int t)
{
 int i,j;
 for(i=0;i<t;i++)
 for(j=0;j<3;j++)
 {}
 
}
