/*
 * LCD_Precfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef LCD_PRECFG_H_
#define LCD_PRECFG_H_

#define BITS_MODES    4   /* or 8*/

//#define FIRST_PINS
#define LAST_PINS     1

#define  RS     PA1
#define  RW     PA2
#define  E      PA3

#define DIRECTION_CTRL_PINS     DDRA
#define CTRL_OUTPUT_PINS        PORTA


#define DIRECTION_DATA_PINS     DDRA
#define DATA_OUTPUT_PINS        PORTA

#endif /* LCD_PRECFG_H_ */
