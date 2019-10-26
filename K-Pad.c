/*
 * K-Pad.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Mohammed Nassar
 */


#include "common_macros.h"
#include "MICRO_setting.h"
#include "k-Pad.h"
#include "K-Pad_Precfg.h"
//  Functions Prototypes(Private)


/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 3

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the for 3x3 keypad
 */

void KeyPad_3x3_getPressedKey(uint8_t *key)
{
	static uint8_t KPad_Entry=0;
	uint8_t col,row;

	for(col=0;col<N_col;col++) /* loop for columns */
	{

		/*
		 * each time only one of the column pins will be output and
		 * the rest will be input pins include the row pins
		 */
		KEYPAD_PORT_DIR = (0b00100000<<col);

		/*
		 * clear the output pin column in this trace and enable the internal
		 * pull up resistors for the rows pins
		 */
		KEYPAD_PORT_VALUE = (~(0b00100000<<col));
		for(row=0;row<N_row;row++) /* loop for rows */
		{
			if(BIT_IS_CLEAR(KEYPAD_PORT_IN,(row+2))) /* if the switch is press in this row */
			{

				KPad_Entry++;
				if(KPad_Entry == 30)  // debouning
				{                                    /* if the switch is press in this row */
					*key = ((row * N_col)+col+1);
					KPad_Entry = 0 ;
				}
			}

		}
	}
}
