/*
 * LCD_Interface.h
 *
 *  Created on: Aug 17, 2019
 *      Author: Ahmed Abdelrehem
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_


/********** EightBit mode pins ************/
#define DATA_PORT PORT_A
#define CONFIG_PORT PORT_C

#define RS_PIN  5
#define RW_PIN  6
#define ENABLE  7

#define CONSTANT 4

#define DATA_PIN4 4
#define DATA_PIN5 5
#define DATA_PIN6 6
#define DATA_PIN7 7
/********************commands**************************/
/* define Commands *///
#define LCD_INIT_PHASE_ONE 0x33
#define LCD_INIT_PHASE_TWO 0x32
#define LCD_INIT_PHASE_THREE 0x28
#define LCD_DISPLAY_OPTIONS 0x0E
#define LCD_CLEAR 0x01
#define LCD_INCREMENT_CURSOR 0x06

/************************************/
#define ROW_ONE 1
#define ROW_TWO 2

/********** APIS *******************************/
extern void LCD_vWriteCommand(uint8 Command);
extern void LCD_vWriteChar(uint8 Data);
extern void LCD_vInit();
extern void LCD_vGotoxy(uint8 Row,uint8 Col);
extern void LCD_vClear();
extern void LCD_vSendString(uint8 String[]);


void Log_voidPrintNumber(u16 Copy_u16Val);
void HLCD_voidWriteNumber(u16 Copy_u16Number);

#endif /* HAL_LCD_LCD_INTERFACE_H_ */
