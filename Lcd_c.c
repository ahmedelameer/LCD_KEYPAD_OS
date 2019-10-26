/*
 * Lcd_c.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */


#include "LCD.h"

uint8_t key=0;

uint8_t OR=0;
uint8_t DIS_CHAR_REQUESTED=0;
uint8_t LCD_CLEAR_REQUESTED=0;
uint8_t LCD_Position_REQUESTED=0;

uint8_t*char_Ptr='\0';

static uint8_t init_flag=0;

void LCD_init(void)
{

	static uint8_t Init_next_command=0;

	if(  init_flag== 0  )
	{
		if( Init_next_command==0 )
		{
			DIRECTION_CTRL_PINS |=(1<<RS)|(1<<RW)|(1<<E);
			DIRECTION_DATA_PINS|=0xF0;
			Init_next_command++;
		}
		else if(Init_next_command==1)
		{
			LCD_sendCommand(BITS_4_MODES);

			if(key==1)
			{
				Init_next_command++;
				key=0;
			}
		}
		else if(Init_next_command==2)
		{
			LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
			if(key==1)
			{
				Init_next_command++;
				key=0;
			}
		}
		else if(Init_next_command==3)
		{
			LCD_sendCommand(CURSOR_OFF);
			if(key==1)
			{
				Init_next_command++;
				key=0;
			}
		}
		else if(Init_next_command==4)
		{
			LCD_sendCommand(CLEAR_LCD);
			if(key==1)
			{
				Init_next_command++;/*protection*/
				init_flag=1;
				//key=0;
			}

		}


	}

}


void LCD_sendCommand(uint8_t command)
{

	static uint8_t SNB_flag=1;
	static uint8_t SNC_next_command=0;



	if(key==0)
	{

		if(SNC_next_command==0)
		{
			Pin_clear(CTRL_OUTPUT_PINS  ,RS);
			Pin_clear(CTRL_OUTPUT_PINS ,RW);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==1)
		{
			Pin_output(CTRL_OUTPUT_PINS  ,E);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==2)
		{
			TAKE_FTCOMMAND(DATA_OUTPUT_PINS,command);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==3)
		{
			Pin_clear(CTRL_OUTPUT_PINS,E);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==4)
		{
			Pin_output(CTRL_OUTPUT_PINS  ,E);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==5)
		{
			TAKE_SCCOMMAND(DATA_OUTPUT_PINS,command);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==6)
		{
			Pin_clear(CTRL_OUTPUT_PINS,E);
			SNC_next_command++;
		}
		//_delay_ms(1);
		else if(SNC_next_command==7)
		{

			SNC_next_command=0;
			SNB_flag=0;

			key=1;   /* command finished*/
		}


	}
}



void LCD_display(void)
{
	uint8_t data=0;
	static uint8_t SNC_next_data=0;


	if(key==1 )
	{

		if(DIS_CHAR_REQUESTED==1) {



			if (*char_Ptr !='\0' )
			{
				data=*char_Ptr;



				if(SNC_next_data==0)
				{
					Pin_output(CTRL_OUTPUT_PINS  ,RS);
					Pin_clear(CTRL_OUTPUT_PINS ,RW);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==1)
				{
					Pin_output(CTRL_OUTPUT_PINS  ,E);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==2)
				{
					TAKE_FTCOMMAND(DATA_OUTPUT_PINS,data);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==3)
				{
					Pin_clear(CTRL_OUTPUT_PINS,E);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==4)
				{
					Pin_output(CTRL_OUTPUT_PINS  ,E);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==5)
				{
					TAKE_SCCOMMAND(DATA_OUTPUT_PINS,data);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==6)
				{
					Pin_clear(CTRL_OUTPUT_PINS,E);
					SNC_next_data++;
				}
				//_delay_ms(1);
				else if(SNC_next_data==7)
				{
					SNC_next_data=0;
					char_Ptr++;




				}
			}
			else
			{
				DIS_CHAR_REQUESTED=0;

			}
		}
  }

}

void LCD_gotoRawCol(void)
{
	static uint8_t row=1;
	static uint8_t col=0;
	static uint8_t inilization=0;
	static uint8_t address=0;
	if(inilization == 0)
	{

		switch(row)
		{
		case 0:
			address=col;
			break;
		case 1:
			address=0x40+col;
			break;
		default:
			break;
		}

		inilization=1;
	}

	if(LCD_Position_REQUESTED == 1)
	{

		DIS_CHAR_REQUESTED=0;
		key=0;
		LCD_sendCommand(address|CURSOR_MoveToFirstLoc);
		if(key==1)
		{
			LCD_Position_REQUESTED=0;

			inilization=0;
		}
	}

}

void Clear_LCD(void)
{
	if(LCD_CLEAR_REQUESTED==1)
	{
		DIS_CHAR_REQUESTED=0;
		key=0;
		LCD_sendCommand(CLEAR_LCD);
		if(key==1)
		{
			LCD_CLEAR_REQUESTED=0;
			// DIS_CHAR_REQUESTED=1;
		}
	}
}
