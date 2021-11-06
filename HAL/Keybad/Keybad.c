/*
 * Keybad.c



 *
 *  Created on: Oct 25, 2021
 *      Author:********* Yousef Abdelrhem********
 */
#include "../../MCAL/LIB/datatypes.h"
#include "../../MCAL/LIB/calcbit.h"
#include "../../MCAL/DIO/DIO_REG.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "keybad_confg.h"
#include "keybad.h"
#include <util/delay.h>

const u8 Keybad_value[keybad_rows][keybad_colum]={{55,56,57,45} ,{52,53,54,43} ,{49,50,51,42} ,{46,48,61,47}	};


void Keybad_Initia(void)
{
	DIO_vSetPinDirection(KEYBAD_PORT,R0,OUTPUT);
	DIO_vSetPinDirection(KEYBAD_PORT,R1,OUTPUT);
	DIO_vSetPinDirection(KEYBAD_PORT,R2,OUTPUT);
	DIO_vSetPinDirection(KEYBAD_PORT,R3,OUTPUT);

	DIO_vSetPinDirection(KEYBAD_PORT,C0,INPUT);
	DIO_vSetPinDirection(KEYBAD_PORT,C1,INPUT);
	DIO_vSetPinDirection(KEYBAD_PORT,C2,INPUT);
	DIO_vSetPinDirection(KEYBAD_PORT,C3,INPUT);

	DIO_vWritePort(KEYBAD_PORT,HIGH);

}

u8 Keybad_getpressed(void)
{
u8 Rowcount=0;
u8 Colcount=0;
u8 Result=0;
for(Rowcount=ROW_INITI;Rowcount<ROW_END;Rowcount++)
{
	DIO_vWritePin(KEYBAD_PORT,Rowcount,LOW);

	for(Colcount=COLUM_INITI;Colcount<COLUM_END;Colcount++)
	{
		if (DIO_u8GetPinValue(KEYBAD_PORT,Colcount)==LOW)
		{

			Result=Keybad_value[Rowcount-ROW_INITI][Colcount-COLUM_INITI];

			while(DIO_u8GetPinValue(KEYBAD_PORT,Colcount)==LOW);

			_delay_ms(10);
		}
	}

	DIO_vWritePin(KEYBAD_PORT,Rowcount,HIGH);


}
return Result;

}




