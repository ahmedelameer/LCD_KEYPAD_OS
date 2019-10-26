

#include"OS.h"
#include"LCD.h"
#include"k-Pad.h"

#define NUM_OF_QUESTIONS 5

void LCD_init_data(void);
void display_next_questions(void );
void CLear_After_3sec(void);
void GoToRowCol_1_0(void);
void wait_ans_from_keypad(void);
void display_next_ANS(void );
void get_key(void);
void Ans_from_choosing_num(void);

uint8_t DIS_QUS_REQUESTED=0;
uint8_t CleanIsReady=0;
static uint8_t FIRST_TIME=0;
static uint8_t NEXT_TIME=0;
static uint8_t lOCK_QUES=0;
static uint8_t lOCK_open=0;
static uint8_t tricky_next=0;
static uint8_t lOCK_trick=0;
static uint8_t pressed=0;
uint8_t g_KEYPAD = '\0' ;


uint8_t OPEN[]="READY!!!";

uint8_t QUES1[]="ARE U OK ?";
uint8_t QUES2[]="DO U EXCIST ?";
uint8_t QUES3[]="Joker ?";


uint8_t ANS1[]="2: NO?";
uint8_t ANS2[]="3:YES? 2:NO";
uint8_t ANS3[]="2: YES?";


uint8_t trick1[]="1: ARE U MAD NOw!";
uint8_t trick2[]="NO";
uint8_t trick3[]="NO U ARE NOT";




int main()
{
	DDRB=0xFF;
	PORTB=0;

	OS_ConfigType Config={2,Timer0};
	OS_ConfigType* ConfigPtr=&Config;



	OS_Init( ConfigPtr);

	OS_Creat_Task(1,LCD_init,0);


	OS_Creat_Task(100,LCD_init_data,1);

	OS_Creat_Task(1,LCD_display,2);

	OS_Creat_Task(1,LCD_gotoRawCol,3);

	OS_Creat_Task(3090,GoToRowCol_1_0,1);

	OS_Creat_Task(1,Clear_LCD,4);

	OS_Creat_Task(2950,CLear_After_3sec,3);

	OS_Creat_Task(3000,display_next_questions,5);

	OS_Creat_Task(3160,display_next_ANS,6);

	//OS_Creat_Task(1,get_key,4);

	OS_Creat_Task(4890,CLear_After_3sec,7);

	/*OS_Creat_Task(4990,Ans_from_choosing_num,8);

	OS_Creat_Task(4250,wait_ans_from_keypad,8);*/


	SREG|=(1<<7);

	OS_Run();
}


void LCD_init_data(void)
{

	if(LCD_CLEAR_REQUESTED==0)
	{
		if(LCD_Position_REQUESTED==0)
		{
			if(lOCK_open==0)
			{

				char_Ptr = OPEN;
				DIS_CHAR_REQUESTED=1;

				lOCK_open++;
				FIRST_TIME++;
				lOCK_QUES=0;
			}



		}

	}
}


void display_next_questions(void )
{

		if(lOCK_QUES==0)

		{
			if(LCD_Position_REQUESTED==0)
			{
				if(LCD_CLEAR_REQUESTED==0)
				{
					if(FIRST_TIME==1)
					{
						char_Ptr = QUES1;
						DIS_CHAR_REQUESTED=1;
						NEXT_TIME++;
						lOCK_QUES=1;

					}
					else if(FIRST_TIME==2)
					{

						char_Ptr = QUES2;
						DIS_CHAR_REQUESTED=1;
						NEXT_TIME++;
						lOCK_QUES=1;
					}
					else if(FIRST_TIME==3)
					{

						char_Ptr = QUES3;
						DIS_CHAR_REQUESTED=1;
						NEXT_TIME++;
						lOCK_QUES=1;
					}
				}
			}
		}
	}


void display_next_ANS(void )
{

		if(lOCK_QUES==1)
		{
			if(LCD_Position_REQUESTED==0)

			{
				if(LCD_CLEAR_REQUESTED==0)
				{
					if(NEXT_TIME==1)
					{
						char_Ptr = ANS1;
						DIS_CHAR_REQUESTED=1;
						FIRST_TIME++;
						lOCK_QUES=0;
						lOCK_trick=1;


					}
					else if(NEXT_TIME==2)
					{

						char_Ptr = ANS2;
						DIS_CHAR_REQUESTED=1;
						FIRST_TIME++;
						lOCK_QUES=0;
						lOCK_trick=1;
					}
					else if(NEXT_TIME==3)
					{

						char_Ptr = ANS3;
						DIS_CHAR_REQUESTED=1;
						FIRST_TIME++;
						lOCK_QUES=0;
						lOCK_trick=1;

					}
				}
			}
		}
	}




void CLear_After_3sec(void)
{
	LCD_CLEAR_REQUESTED=1;
	DIS_CHAR_REQUESTED=0;

}

void GoToRowCol_1_0(void)
{
	LCD_CLEAR_REQUESTED=0;
	DIS_CHAR_REQUESTED=0;
	LCD_Position_REQUESTED=1;

}




void Ans_from_choosing_num(void)
{
	if(pressed ==1)
	{
		if(lOCK_trick==1)
		{
			if(LCD_Position_REQUESTED==0)

			{
				if(LCD_CLEAR_REQUESTED==0)
				{
					if(tricky_next==1)
					{
						char_Ptr = trick1;
						DIS_CHAR_REQUESTED=1;
						lOCK_trick=0;



					}
					else if(tricky_next==2)
					{

						char_Ptr = trick2;
						DIS_CHAR_REQUESTED=1;
						lOCK_trick=0;

					}
					else if(tricky_next==3)
					{

						char_Ptr = trick3;
						DIS_CHAR_REQUESTED=1;

						tricky_next=0;

					}
				}
			}

		}
	}
}




void get_key(void)
{
	if(pressed ==1)
	{
		uint8_t key_pressed = 0;


		KeyPad_3x3_getPressedKey(&key_pressed);
		if(key_pressed > 0 && key_pressed <=9){
			switch(key_pressed)
			{
			case 1:
				tricky_next=1;
				pressed=0;
				break;
			case 2:
				tricky_next=2;
				pressed=0;
				break;
			default:
				pressed=0;
				tricky_next=3;

			}


		}
	}
}


void wait_ans_from_keypad(void)
{
	pressed =1;
}
