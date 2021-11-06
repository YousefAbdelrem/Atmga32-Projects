/*
 * DIO.c
 *
 *  Created on: Oct 16, 2017
 *      Author: Ahmed Abdelrehem
 */
/*********************Description*****************
 DIO.c used to set the Direction of any bit in PORTX
 contain function that write the value to the OUTPUT
 contain function to read the value from the input

 **********************************************************/
#include "../LIB/calcbit.h"
#include "../LIB/datatypes.h"
#include "../LIB/calcbit.h"
#include "DIO_REG.h"
#include "DIO_INTERFACE.h"

/**************************************************************************************************
 * Description:void DIO_vSetPinDirection(port Copy_u8PORT,u8 Copy_u8PinNumber,DDRX copy_u8state)
 * set the direction of PinX as input with pull up resistor or without pull up resistor or as OUTPUT
 * input: portX,pin_number
 * OUTPUT: Nothing
 **************************************************************************************************/
void DIO_vSetPinDirection(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber,
		uint8 copy_u8state) {
	switch (Copy_u8PORT) {
	case PORT_A:
		switch (copy_u8state) {
		case OUTPUT:
			setbit(DDRA, Copy_u8PinNumber);
			break;
		case IPWR:
			clearbit(DDRA, Copy_u8PinNumber);
			setbit(PORTA, Copy_u8PinNumber);
			break;
		case IPWOR:
			clearbit(DDRA, Copy_u8PinNumber);
			clearbit(PORTA, Copy_u8PinNumber);
			break;
		}
		break;
	case PORT_B:
		switch (copy_u8state) {
		case OUTPUT:
			setbit(DDRB, Copy_u8PinNumber);
			break;
		case IPWR:
			clearbit(DDRB, Copy_u8PinNumber);
			setbit(PORTB, Copy_u8PinNumber);
			break;
		case IPWOR:
			clearbit(DDRB, Copy_u8PinNumber);
			clearbit(PORTB, Copy_u8PinNumber);
			break;
		}
		break;
	case PORT_C:
		switch (copy_u8state) {
		case OUTPUT:
			setbit(DDRC, Copy_u8PinNumber);
			break;
		case IPWR:
			clearbit(DDRC, Copy_u8PinNumber);
			setbit(PORTC, Copy_u8PinNumber);
			break;
		case IPWOR:
			clearbit(DDRC, Copy_u8PinNumber);
			clearbit(PORTC, Copy_u8PinNumber);
			break;
		}
		break;
	case PORT_D:
		switch (copy_u8state) {
		case OUTPUT:
			setbit(DDRD, Copy_u8PinNumber);
			break;
		case IPWR:
			clearbit(DDRD, Copy_u8PinNumber);
			setbit(PORTD, Copy_u8PinNumber);
			break;
		case IPWOR:
			clearbit(DDRD, Copy_u8PinNumber);
			clearbit(PORTD, Copy_u8PinNumber);
			break;
		}
		break;
	}
}

/*******************************************************************
 * Description: void DIO_vWritePIN(port Copy_u8PORT,u8 Copy_u8PinNumber,u8 value)
 * write 1 or 0 on the OUTPUTPin
 * input:PORTx , PIN Number and Value(1 or 0)
 * OUTPUT:Nothing
 ***********************************************************************/
void DIO_vWritePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber,
		uint8 Copy_u8value) {
	switch (Copy_u8PORT) {
	case PORT_A:
		switch (Copy_u8value) {
		case LOW:
			clearbit(PORTA, Copy_u8PinNumber);
			break;
		case HIGH:
			setbit(PORTA, Copy_u8PinNumber);
			break;
		}
		break;
	case PORT_B:
		switch (Copy_u8value) {
		case LOW:
			clearbit(PORTB, Copy_u8PinNumber);
			break;
		case HIGH:
			setbit(PORTB, Copy_u8PinNumber);
			break;
		}
		break;
	case PORT_C:
		switch (Copy_u8value) {
		case LOW:
			clearbit(PORTC, Copy_u8PinNumber);
			break;
		case HIGH:
			setbit(PORTC, Copy_u8PinNumber);
			break;
		}
		break;
	case PORT_D:
		switch (Copy_u8value) {
		case LOW:
			clearbit(PORTD, Copy_u8PinNumber);
			break;
		case HIGH:
			setbit(PORTD, Copy_u8PinNumber);
			break;
		}
		break;
	}
}
/************************************************************************
 * description:u8 DIO_u8GetpinValue(port Copy_u8PORT,u8 Copy_u8PinNumber)
 * get the value of PInx
 * input:portx and pin number
 * OUTPUT:returns value of Pin (1 or 0)
 *
 ************************************************************************/
uint8 DIO_u8GetPinValue(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber) {
	uint8 pin_value;
	switch (Copy_u8PORT) {
	case PORT_A:
		pin_value = getbit(PINA, Copy_u8PinNumber);
		break;
	case PORT_B:
		pin_value = getbit(PINB, Copy_u8PinNumber);
		break;
	case PORT_C:
		pin_value = getbit(PINC, Copy_u8PinNumber);
		break;
	case PORT_D:
		pin_value = getbit(PIND, Copy_u8PinNumber);
		break;
	}
	return pin_value;
}
/***********************************************************************
 * Description :void DIO_u8TogglePin(port Copy_u8PORT,u8 Copy_u8PinNumber)
 * toggle PinX
 * input:PortX and Pin number
 * OUTPUT:Nothing
 *************************************************************************/
void DIO_vTogglePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber) {
	switch (Copy_u8PORT) {
	case PORT_A:
		togglebit(PORTA, Copy_u8PinNumber);
		break;
	case PORT_B:
		togglebit(PORTB, Copy_u8PinNumber);
		break;
	case PORT_C:
		togglebit(PORTC, Copy_u8PinNumber);
		break;
	case PORT_D:
		togglebit(PORTD, Copy_u8PinNumber);
		break;
	}
}

/*************************************************************************************
 * Description:void DIO_vSetPortDirection(port Copy_u8PORT,u8 DDRX copy_u8state)
 * set the Direction of the port
 * input:portX and desired direction
 * OUTPUT:Nothing
 *********************************************************************************/
void DIO_vSetPortDirection(uint8 Copy_u8PORT, uint8 copy_u8state) {
	switch (Copy_u8PORT) {
	case PORT_A:
		switch (copy_u8state) {
		case OUTPUT:
			DDRA = SET_PORT;
			break;
		case IPWR:
			DDRA = CLEAR_PORT;
			PORTA = SET_PORT;
			break;
		case IPWOR:
			DDRA = CLEAR_PORT;
			PORTA = CLEAR_PORT;
			break;
		}
		break;
	case PORT_B:
		switch (copy_u8state) {
		case OUTPUT:
			DDRB = SET_PORT;
			break;
		case IPWR:
			DDRB = CLEAR_PORT;
			PORTB = SET_PORT;
			break;
		case IPWOR:
			DDRB = CLEAR_PORT;
			PORTB = CLEAR_PORT;
			break;
		}
		break;
	case PORT_C:
		switch (copy_u8state) {
		case OUTPUT:
			DDRC = SET_PORT;
			break;
		case IPWR:
			DDRC = CLEAR_PORT;
			PORTC = SET_PORT;
			break;
		case IPWOR:
			DDRC = CLEAR_PORT;
			PORTC = CLEAR_PORT;
			break;
		}
		break;
	case PORT_D:
		switch (copy_u8state) {
		case OUTPUT:
			DDRD = SET_PORT;
			break;
		case IPWR:
			DDRD = CLEAR_PORT;
			PORTD = SET_PORT;
			break;
		case IPWOR:
			DDRD = CLEAR_PORT;
			PORTD = CLEAR_PORT;
			break;
		}
		break;
	}

}
/****************************************************************************
 * Description:void DIO_vWritePort(port Copy_u8PORT,u8 value)
 * Set or Clear PortX
 * Input:POrtX and value
 * OUTPUT:Nothing
 *
 *******************************************************************************/
void DIO_vWritePort(uint8 Copy_u8PORT, uint8 Copy_u8value) {
	switch (Copy_u8PORT) {
	case PORT_A:
		switch (Copy_u8value) {
		case LOW:
			PORTA = CLEAR_PORT;
			break;
		case HIGH:
			PORTA = SET_PORT;
			break;

		}
		break;
	case PORT_B:
		switch (Copy_u8value) {
		case LOW:
			PORTB = CLEAR_PORT;
			break;
		case HIGH:
			PORTB = SET_PORT;
			break;

		}
		break;
	case PORT_C:
		switch (Copy_u8value) {
		case LOW:
			PORTC = CLEAR_PORT;
			break;
		case HIGH:
			PORTC = SET_PORT;
			break;

		}
		break;
	case PORT_D:
		switch (Copy_u8value) {
		case LOW:
			PORTD = CLEAR_PORT;
			break;
		case HIGH:
			PORTD = SET_PORT;
			break;

		}
		break;
	}
}
/*****************************************************************************
 * Description:void DIO_vTogglrPort(port Copy_u8PORT)
 * toggle port
 * input:PORTX
 * OUTPUT:Nothing
 ****************************************************************************/
void DIO_vTogglrPort(uint8 Copy_u8PORT) {
	switch (Copy_u8PORT) {
	case PORT_A:
		PORTA ^= PORTA;
		break;
	case PORT_B:
		PORTB ^= PORTB;
		break;
	case PORT_C:
		PORTC ^= PORTC;
		break;
	case PORT_D:
		PORTD ^= PORTD;

	}

}

void DIO_vWritePortValue(uint8 Copy_u8PORT, uint8 Copy_u8value) {
	switch (Copy_u8PORT) {
	case PORT_A:
		PORTA = Copy_u8value;
		break;
	case PORT_B:
		PORTB = Copy_u8value;
		break;
	case PORT_C:
		PORTC = Copy_u8value;
		break;
	case PORT_D:
		PORTD = Copy_u8value;
		break;

	}
}
