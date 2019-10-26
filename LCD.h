/*
 * LCD.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef LCD_H_
#define LCD_H_

#include"LCD_Precfg.h"

#include"INTERFACE.h"

#include"MICRO_setting.h"
#include<string.h>

extern uint8_t key;
#define FINISHED 1

extern uint8_t*char_Ptr;
void LCD_gotoRawCol(void);
extern uint8_t DIS_CHAR_REQUESTED;
extern uint8_t LCD_CLEAR_REQUESTED;
extern uint8_t LCD_Position_REQUESTED;

/* control pins*/

#define CURSOR_OFF            0x0c
#define CURSOR_MoveToFirstLoc 0x80

/* set functions*/
#define BITS_8_MODES               0x38
#define BITS_4_MODES               0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define CLEAR_LCD                  0x01


/*output pins */



/*command to write*/
#if  ( FIRST_PINS==1)
#define TAKE_FTCOMMAND(PORT,COMMAND)    PORT=(PORT&0xF0)|((COMMAND&0xF0)>>4)
#define TAKE_SCCOMMAND(PORT,COMMAND)    PORT=(PORT&0xF0)|(COMMAND&0x0F)

#elif (LAST_PINS ==1)
#define TAKE_FTCOMMAND(PORT,COMMAND)    PORT=(PORT&0x0F)|(COMMAND&0xF0)
#define TAKE_SCCOMMAND(PORT,COMMAND)    PORT=(PORT&0x0F)|((COMMAND&0x0F)<<4)
#endif








void Clear_LCD(void);
void LCD_sendCommand(uint8_t command );
void LCD_displayChar(void);
void LCD_init(void);
void LCD_displayString(void);

void LCD_IntToStr(uint8_t data);
void LCD_displayStrRowCol(uint8_t row,uint8_t col,const char *Str);
extern void LCD_clearScreen(void);
extern void LCD_display(void);
#endif /* LCD_H_ */
