#include "GPIO_INIT.h"
#include "tm4c123gh6pm.h"
#include <Math.h>
#define PI 3.14159265359
#include <string.h> // For strtok function
#include <stdlib.h> // For strtod function
#include "LCD.h"

/* IO Ports Initialization Functions Implementations*/


void PortE_Init()
{ // for RS , RW , E pins (1,2,3) ,  buzzer,switch 3 respectivily(4,5)
	SYSCTL_RCGCGPIO_R |= 0x00000010;
  while ((SYSCTL_PRGPIO_R&0x10) == 0){};
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R |= 0x3E;
	GPIO_PORTE_DIR_R = 0x1F;
	GPIO_PORTE_DEN_R = 0x3F;
	GPIO_PORTE_AMSEL_R = 0x00;
	GPIO_PORTE_AFSEL_R = 0x00;
	GPIO_PORTE_PCTL_R = 0x000000;
  GPIO_PORTE_PUR_R = 0x20;
  
}



void PortB_Init ()
{ 
	SYSCTL_RCGCGPIO_R |= 0x00000002;
  while ((SYSCTL_PRGPIO_R&0x02) == 0){};
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00; 
	GPIO_PORTB_PCTL_R = 0x00000000;
  GPIO_PORTB_PUR_R = 0x00;
  
}
void PortF_Init ()
{
	
	SYSCTL_RCGCGPIO_R |= 0x00000020;
  while ((SYSCTL_PRGPIO_R&0x20) == 0){};
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_PCTL_R = 0x00000000; 
	GPIO_PORTF_DIR_R = 0x0E;
  GPIO_PORTF_AFSEL_R = 0x00; 
  GPIO_PORTF_PUR_R = 0x11;
  GPIO_PORTF_DEN_R = 0x1F;
}



void delay_ms(int t) // Milli seconds delay function
{
	int i;
	int j;
	for(i=0 ; i<t ; i++)
	{
		for(j=0; j<3180; j++)
		{
			
		}
	}
}