#ifndef KPD_H_
#define KPD_H_
#include "STD_TYPES.h"

#define N_col 4
#define N_row 4

void Keypad_Init(void);
u8 Keypad_Getkey(void);
void delay_us(int t);

#endif /* KPD_H_ */