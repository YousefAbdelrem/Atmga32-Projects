/*
 * LCD_Program.c

 *
 *  Created on: Aug 17, 2019
 *      Author: Ahmed Abdelrehem
 */
#include "../../MCAL/LIB/datatypes.h"
#include "../../MCAL/LIB/calcbit.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "LCD_Interface.h"
#include <util/delay.h>

/**********************LCD_vWriteCommand****************************
 * Description:
 * Input:
 * OUTPUT:
 * ***************************************************************/
void LCD_vWriteCommand(uint8 Command)
{
	/*1- R/S equal to zero */
	DIO_vWritePin(CONFIG_PORT,RS_PIN,LOW);
	/*2- R/W equal to zero */
	DIO_vWritePin(CONFIG_PORT,RW_PIN,LOW);
	/*3- send high nibble */
	DIO_vWritePin(DATA_PORT,DATA_PIN4,((Command & 0x10)>>DATA_PIN4));
	DIO_vWritePin(DATA_PORT,DATA_PIN5,((Command & 0x20)>>DATA_PIN5));
	DIO_vWritePin(DATA_PORT,DATA_PIN6,((Command & 0x40)>>DATA_PIN6));
	DIO_vWritePin(DATA_PORT,DATA_PIN7,((Command & 0x80)>>DATA_PIN7));
	DIO_vWritePin(CONFIG_PORT,ENABLE,HIGH);
	_delay_ms(2);
	DIO_vWritePin(CONFIG_PORT,ENABLE,LOW);
	/* send low Nibble */
	DIO_vWritePin(DATA_PORT,DATA_PIN4,((Command & 0x01)));
	DIO_vWritePin(DATA_PORT,DATA_PIN5,((Command & 0x02)>>(DATA_PIN5-CONSTANT)));
	DIO_vWritePin(DATA_PORT,DATA_PIN6,((Command & 0x04)>>(DATA_PIN6-CONSTANT)));
	DIO_vWritePin(DATA_PORT,DATA_PIN7,((Command & 0x08)>>(DATA_PIN7-CONSTANT)));
	DIO_vWritePin(CONFIG_PORT,ENABLE,HIGH);
	_delay_ms(2);
	DIO_vWritePin(CONFIG_PORT,ENABLE,LOW);

}
/**********************LCD_vWriteChar****************************
 * Description:
 * Input:
 * OUTPUT:
 * ***************************************************************/
void LCD_vWriteChar(uint8 Data)
{
	/*1- R/S equal to one */
	DIO_vWritePin(CONFIG_PORT,RS_PIN,HIGH);
	/*2- R/W equal to zero */
	DIO_vWritePin(CONFIG_PORT,RW_PIN,LOW);
	/*3- send high nibble */
	DIO_vWritePin(DATA_PORT,DATA_PIN4,((Data & 0x10)>>DATA_PIN4));
	DIO_vWritePin(DATA_PORT,DATA_PIN5,((Data & 0x20)>>DATA_PIN5));
	DIO_vWritePin(DATA_PORT,DATA_PIN6,((Data & 0x40)>>DATA_PIN6));
	DIO_vWritePin(DATA_PORT,DATA_PIN7,((Data & 0x80)>>DATA_PIN7));
	DIO_vWritePin(CONFIG_PORT,ENABLE,HIGH);
	_delay_ms(2);
	DIO_vWritePin(CONFIG_PORT,ENABLE,LOW);
	/* send low Nibble */
	DIO_vWritePin(DATA_PORT,DATA_PIN4,((Data & 0x01)));
	DIO_vWritePin(DATA_PORT,DATA_PIN5,((Data & 0x02)>>(DATA_PIN5-CONSTANT)));
	DIO_vWritePin(DATA_PORT,DATA_PIN6,((Data & 0x04)>>(DATA_PIN6-CONSTANT)));
	DIO_vWritePin(DATA_PORT,DATA_PIN7,((Data & 0x08)>>(DATA_PIN7-CONSTANT)));
	DIO_vWritePin(CONFIG_PORT,ENABLE,HIGH);
	_delay_ms(2);
	DIO_vWritePin(CONFIG_PORT,ENABLE,LOW);

}
/**********************LCD_Init****************************
 * Description:
 * Input:
 * OUTPUT:
 * ********************************************************/
void LCD_vInit()
{
	/* Init Pins direction for the lcd */
	DIO_vSetPinDirection(CONFIG_PORT,RS_PIN,OUTPUT);
	DIO_vSetPinDirection(CONFIG_PORT,RW_PIN,OUTPUT);
	DIO_vSetPinDirection(CONFIG_PORT,ENABLE,OUTPUT);
	DIO_vSetPinDirection(DATA_PORT,DATA_PIN4,OUTPUT);
	DIO_vSetPinDirection(DATA_PORT,DATA_PIN5,OUTPUT);
	DIO_vSetPinDirection(DATA_PORT,DATA_PIN6,OUTPUT);
	DIO_vSetPinDirection(DATA_PORT,DATA_PIN7,OUTPUT);
	DIO_vWritePin(CONFIG_PORT,ENABLE,LOW);
	_delay_ms(50);
	/* Init the LCD*/
	LCD_vWriteCommand(LCD_INIT_PHASE_ONE);
	LCD_vWriteCommand(LCD_INIT_PHASE_TWO);
	LCD_vWriteCommand(LCD_INIT_PHASE_THREE);
	LCD_vWriteCommand(LCD_DISPLAY_OPTIONS);
	LCD_vWriteCommand(LCD_CLEAR);
	LCD_vWriteCommand(LCD_INCREMENT_CURSOR);
	_delay_ms(1);
}
/**********************LCD_vGotoxy****************************
 * Description:
 * Input:
 * OUTPUT:
 * ********************************************************/
void LCD_vGotoxy(uint8 Row,uint8 Col)
{
	uint8 Local_Address=0;
	switch(Row)
	{
	case ROW_ONE:
		Local_Address = 0x80 + Col;
		break;
	case ROW_TWO:
		Local_Address= 0xC0 + Col;
		break;

	}
	/*send Command to go to that address*/
	LCD_vWriteCommand(Local_Address);

}
/**********************LCD_vClear****************************
 * Description:
 * Input:
 * OUTPUT:
 * ********************************************************/
void LCD_vClear()
{
	LCD_vWriteCommand(LCD_CLEAR);
}
/**********************LCD_vSendString****************************
 * Description:
 * Input:
 * OUTPUT:
 * ********************************************************/
void LCD_vSendString(uint8 String[])
{
	    uint8 n=0;
		while(String[n]!='\0')
		{
			LCD_vWriteChar(String[n]);
			n++;
		}
}



void Log_voidPrintNumber(u16 Copy_u16Val)
{
	u8 Local_u8Factor;

	if (Copy_u16Val >= (u16)10000)
	{
		Local_u8Factor = (u8)(Copy_u16Val / (u16) 10000);
		LCD_vWriteChar(Local_u8Factor+48);
		Copy_u16Val = Copy_u16Val - (u16)(Local_u8Factor * (u16)10000);

		Local_u8Factor = (u8)(Copy_u16Val / (u16) 1000);
		LCD_vWriteChar(Local_u8Factor+48);
		Copy_u16Val = Copy_u16Val - (u16)(Local_u8Factor * (u16)1000);

		Local_u8Factor = (u8)(Copy_u16Val / (u16) 100);
		LCD_vWriteChar(Local_u8Factor+48);
		Copy_u16Val = Copy_u16Val - (u16)(Local_u8Factor * (u8)100);

		Local_u8Factor = (u8)(Copy_u16Val / (u16) 10);
		LCD_vWriteChar(Local_u8Factor+48);
		Local_u8Factor = Copy_u16Val - (u16)(Local_u8Factor * (u8)10);
		LCD_vWriteChar(Local_u8Factor+48);

	}

	else if (Copy_u16Val >= (u16) 1000 )
	{
		Local_u8Factor = (u8)(Copy_u16Val / (u16) 1000);
		LCD_vWriteChar(Local_u8Factor+48);
		Copy_u16Val = Copy_u16Val - (u16)(Local_u8Factor * (u16)1000);

		Local_u8Factor = (u8)(Copy_u16Val / (u16) 100);
		LCD_vWriteChar(Local_u8Factor+48);
		Copy_u16Val = Copy_u16Val - (u16)(Local_u8Factor * (u8)100);

		Local_u8Factor = (u8)(Copy_u16Val / (u16) 10);
		LCD_vWriteChar(Local_u8Factor+48);
		Local_u8Factor = Copy_u16Val - (u16)(Local_u8Factor * (u8)10);
		LCD_vWriteChar(Local_u8Factor+48);
	}

	else if (Copy_u16Val >= (u8)100 )
	{
		Local_u8Factor = (u8)(Copy_u16Val / (u16) 100);
		LCD_vWriteChar(Local_u8Factor+48);
		Copy_u16Val = Copy_u16Val - (u16)(Local_u8Factor * (u8)100);

		Local_u8Factor = (u8)(Copy_u16Val / (u16) 10);
		LCD_vWriteChar(Local_u8Factor+48);
		Local_u8Factor = Copy_u16Val - (u16)(Local_u8Factor * (u8)10);
		LCD_vWriteChar(Local_u8Factor+48);
	}

	else if (Copy_u16Val >= (u8) 10 )
	{
		Local_u8Factor = (u8)((u8)Copy_u16Val / (u8) 10);
		LCD_vWriteChar(Local_u8Factor+48);
		Local_u8Factor = Copy_u16Val - (u16)(Local_u8Factor * (u8)10);
		LCD_vWriteChar(Local_u8Factor+48);
	}

	else
	{
		LCD_vWriteChar(Copy_u16Val+48);
	}
}
void HLCD_voidWriteNumber(u16 Copy_u16Number){

	if(Copy_u16Number < 10 ){
		LCD_vWriteChar(Copy_u16Number + '0') ;

	}
	else if(Copy_u16Number < 100 ){
		LCD_vWriteChar((Copy_u16Number/10) + '0') ;
		LCD_vWriteChar((Copy_u16Number%10) + '0') ;
	}
	else if(Copy_u16Number < 1000 ){
		LCD_vWriteChar((Copy_u16Number/100)   + '0') ;
		LCD_vWriteChar((Copy_u16Number/10)%10 + '0') ;
		LCD_vWriteChar((Copy_u16Number%10)    + '0') ;
	}
	else if(Copy_u16Number < 10000 ){
		LCD_vWriteChar((Copy_u16Number/1000)   + '0') ;
		LCD_vWriteChar((Copy_u16Number/100)%10   + '0') ;
		LCD_vWriteChar((Copy_u16Number/10)%10 + '0') ;
		LCD_vWriteChar((Copy_u16Number%10)    + '0') ;
	}
	else if(Copy_u16Number < 100000 ){
		LCD_vWriteChar((Copy_u16Number/10000)   + '0') ;
		LCD_vWriteChar((Copy_u16Number/1000)%10   + '0') ;
		LCD_vWriteChar((Copy_u16Number/100)%10 + '0') ;
		LCD_vWriteChar((Copy_u16Number/10)%10    + '0') ;
		LCD_vWriteChar((Copy_u16Number%10)     + '0') ;
	}
}

