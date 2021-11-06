/*
 * DIO_INTERFACE.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Ahmed Abdelrehem
 */
#ifndef DIO_INTERFACE
#define DIO_INTERFACE

/***** Available ports **********/
#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
/********************************/
#define LOW 0
#define HIGH 1
/********************************/
#define INPUT 0

/******* Directions **************/
#define IPWR 0
#define IPWOR 1
#define OUTPUT 2

/*********** Port values *********/
#define SET_PORT 0xFF
#define CLEAR_PORT 0x00

extern void DIO_vSetPinDirection(uint8 Copy_u8PORT,uint8 Copy_u8PinNumber,uint8 copy_u8state);
extern void DIO_vWritePin(uint8 Copy_u8PORT,uint8 Copy_u8PinNumber,uint8 Copy_u8value);
extern void DIO_vTogglePin(uint8 Copy_u8PORT,uint8 Copy_u8PinNumber);
extern void DIO_vSetPortDirection(uint8 Copy_u8PORT,uint8 copy_u8state);
extern void DIO_vWritePort(uint8 Copy_u8PORT,uint8 Copy_u8value);
extern uint8 DIO_u8GetPinValue(uint8 Copy_u8PORT,uint8 Copy_u8PinNumber);
extern void DIO_vTogglrPort(uint8 Copy_u8PORT);
extern void DIO_vWritePortValue(uint8 Copy_u8PORT,uint8 Copy_u8value);

#endif

