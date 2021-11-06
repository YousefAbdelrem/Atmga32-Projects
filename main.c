#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#undef F_CPU
#define F_CPU 8000000UL

#include "MCAL/LIB/datatypes.h"
#include "MCAL/LIB/calcbit.h"
#include "MCAL/DIO/DIO_INTERFACE.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/Keybad/keybad.h"
#include "RTOS/FreeRTOS.h"
#include "RTOS/list.h"
#include "RTOS/task.h"
#include "RTOS/croutine.h"
#include "RTOS/timers.h"
#include "RTOS/FreeRTOSConfig.h"
#include "RTOS/semphr.h"
#include "RTOS/queue.h"

void System_Intia(void);
void SIGN_IN(void *pvParmater);
void CHECK(void *pvParmater);
void LOG_IN(void *pvParmater);
void LEDS(void *pvParmater);
void Motor(void *pvParmater);



#define Max_num_of_passowrd 10
u8 password_desired[Max_num_of_passowrd]={0};
u8 password_desired2[Max_num_of_passowrd]={0};
u8 address=0;

#ifndef NULL
#define NULL   ((void *) 0)
#endif


xTaskHandle SIGN;
xSemaphoreHandle Syc;
xSemaphoreHandle Syc2;
xSemaphoreHandle MUTEX;
xSemaphoreHandle TASK;
xSemaphoreHandle TASK2;
u8 flag=0;
u8 choose[1]={0};
void System_Intia(void)
{
	DIO_vSetPinDirection(PORT_A,0,OUTPUT);
	DIO_vSetPortDirection(PORT_B,OUTPUT);
	Syc=xSemaphoreCreateCounting(1,0);
	Syc2=xSemaphoreCreateCounting(1,0);
	MUTEX =xSemaphoreCreateMutex();
	TASK=xSemaphoreCreateCounting(1,0);
	TASK2=xSemaphoreCreateCounting(1,0);
	LCD_vInit();
	Keybad_Initia();

}



int main(void)
{

	System_Intia();
	xTaskCreate(SIGN_IN,NULL,150,NULL,2,&SIGN);
	xTaskCreate(CHECK,NULL,80,NULL,1,NULL);
	xTaskCreate(LOG_IN,NULL,150,NULL,1,NULL);
	xTaskCreate(LEDS,NULL,80,NULL,1,NULL);
	xTaskCreate(Motor,NULL,80,NULL,1,NULL);

	vTaskStartScheduler();

return 0;
}

void SIGN_IN(void *pvParmater)
{
	u8 ret ;
	u8 counter=0 ;

	LCD_vSendString("Enter New Pass:");
				while(address<=Max_num_of_passowrd)
				{


				*(password_desired+address)=Keybad_getpressed(); // assign numbers into array1
				if(*(password_desired+address) == '=')
				  {
					*(password_desired+address)=0;
					 LCD_vClear();
				     LCD_vGotoxy(1,0);
				     LCD_vSendString("Enter Pass Again:");
				     address=0;
				     repeat :
				     while(address<=Max_num_of_passowrd)
				     	{

				    *(password_desired2+address)=Keybad_getpressed(); // assign numbers into array2
				  	if(*(password_desired2+address) == '=')
				       {
				     	    *(password_desired2+address)=0;
				     			 LCD_vClear();
				     			 LCD_vGotoxy(1,0);
				     			xSemaphoreGive(Syc2);
				     			vTaskDelay(200);
				     			 if(flag == 1) // check password
				     			 {
				     			 LCD_vSendString("*Password Saved*");
				     		    	flag=0;
				     			 vTaskDelay(250);
					     		xSemaphoreGive(Syc);
				     			vTaskDelete(SIGN);

				     			 }else
				     			 {
				     				LCD_vClear();
				     				 LCD_vGotoxy(1,0);
					     			 if(counter<=1)
					     			 {
					     				LCD_vSendString("*Wrong pass Try again*");
					     				address=0;
					     				counter++;
					     		        goto repeat;
					     			 }else
					     			 {
					     				LCD_vClear();
					     				LCD_vGotoxy(1,0);
					     				LCD_vSendString("*System Locked*");
					     				vTaskDelete(SIGN);
					     			 }
				     			 }
				     	 }
				     	 if(*(password_desired2+address)>0)
				     	{
				     		 LCD_vGotoxy(2,0+address);
				     		 LCD_vWriteChar('*');

				     		 address++;

				     	}
				     	 if(address == 10 )
				     		{
				     		 LCD_vClear();
				     	   LCD_vGotoxy(1,0);
				     	   LCD_vSendString("Max Pass 10 Num");
				     	   LCD_vGotoxy(2,3);
				     	   LCD_vSendString(" *Try Again*");
			     		     address=0;
			     		    goto repeat;

				     	   }
				     	}

				 }
				else if(*(password_desired+address)>0)
				{
					LCD_vGotoxy(2,0+address);
					LCD_vWriteChar('*');

					 address++;

				}
				  if(address == 10 )
				   {
					   LCD_vClear();
					   LCD_vGotoxy(1,0);
					   LCD_vSendString("Max Pass 10 Num");
					   LCD_vGotoxy(2,3);
					 LCD_vSendString(" *Try Again*");

					 address=0;

				   }
				}
}


void CHECK(void *pvParmater)
{
	u8 x=0;
	 u8 ret;

	for(;;)
{

 	 ret=xSemaphoreTake(Syc2,0xffff);
 	 if(ret == 1 )
 	  {

 	 	 for (int i = 0; i < Max_num_of_passowrd; i++)
		 {
		        if (password_desired[i] == password_desired2[i])
		        {
		        	++x;
		        	if(x == Max_num_of_passowrd)
		        	{

		       	     flag=1;

		        	}

		        }else
		        {
		        	PORTB=0x00;
		        	 flag=0;
		        }
		   }
 	 	 x=0;
}

}
}



void LOG_IN(void *pvParmater)
{
	u8 counter=0 ;
	u8 ret;
for(u8 i=0 ;i<10;i++)
{
	*(password_desired2+i)=0;

}

	for(;;)
{

	    	address=0;
		 ret=xSemaphoreTake(Syc,0xffff);
		 if(ret == 1)
		 {

		   LCD_vClear();
		   LCD_vGotoxy(1,0);
		   LCD_vSendString("LOGIN :");
		   repeat :
		   while(address<=Max_num_of_passowrd)
		  	{

			    *(password_desired2+address)=Keybad_getpressed(); // assign numbers into array2
		  		if(*(password_desired2+address) == '=')
		  		{
		  		  *(password_desired2+address)=0;
		  			LCD_vClear();
		  			LCD_vGotoxy(1,0);
		  			xSemaphoreGive(Syc2);
		  			vTaskDelay(200);
		  			 if(flag == 1) // check password
		  			 {	LCD_vClear();
		  				LCD_vGotoxy(1,0);
		  			   LCD_vSendString("*Welcome*");
		  		    	 vTaskDelay(350);
		  		    	 flag=0;

		  		    	LCD_vClear();
		  		    	LCD_vGotoxy(1,0);
		  		       LCD_vSendString("1.Light LEDS ");
		  		       	 LCD_vGotoxy(2,0);
		  		       LCD_vSendString("2.OPEN DOOR ");
		  		     reapet2 :
		  		     *(choose)=Keybad_getpressed();
		  		 	 vTaskDelay(200);
		  		   if (*(choose)== 49)
		  		   {
				     	xSemaphoreGive(TASK);
		  		       	vTaskDelay(200);
		  		   }
		  		       	   if (*(choose) == 50)
		  		       	  {
		  		       		xSemaphoreGive(TASK2);
		  		       		vTaskDelay(200);
		  		       	  }

		  		       	  goto reapet2;
		  			 }else
		  			{
		  				LCD_vClear();
		  				LCD_vGotoxy(1,0);
		  				 if(counter<=1)
		  				 {
		  				LCD_vSendString("*Wrong Password:");
		  				address=0;
		  			   counter++;
		  				goto repeat;
		  		      }else
		  		     	{
		  					 LCD_vClear();
		  					   LCD_vGotoxy(1,0);
		  					   LCD_vSendString("*System Locked*");
		  			    }
		  			 }
		  	      }
		  				 	 if(*(password_desired2+address)>0)
		  				     	{
		  				     		 LCD_vGotoxy(2,0+address);
		  				     		 LCD_vWriteChar('*');

		  				     		 address++;

		  				     	}
		  				     	 if(address == 10 )
		  				     		{
		  				     		 LCD_vClear();
		  				     	   LCD_vGotoxy(1,0);
		  				     	   LCD_vSendString("Max Pass 10 Num");
		  				     	   LCD_vGotoxy(2,3);
		  				     	   LCD_vSendString(" *Try Again*");
		  			     		     address=0;
		  			     		    goto repeat;

		  				     	   }
		  	}
	}
}

}

void Motor(void *pvParmater)
{

	u8 ret;

for(;;)
{
	 ret=xSemaphoreTake(TASK2,0xffff);
	 if(ret == 1)
	 {

		DIO_vWritePin(PORT_A,0,HIGH);
		 vTaskDelay(5000);
			DIO_vWritePin(PORT_A,0,LOW);





	}

}
}

void LEDS(void *pvParmater)
{

	u8 ret;

for(;;)
{
	 ret=xSemaphoreTake(TASK,0xffff);
if(ret == 1)
{

		for(u8 i=0 ;i < 7 ;i++)
		  {
			 PORTB=(1<<i);
			 vTaskDelay(250);

		  }



}
}
}







