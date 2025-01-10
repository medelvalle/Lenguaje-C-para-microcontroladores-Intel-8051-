//*********************************************************************
// SERIE_IO.C
//*********************************************************************
#include <reg52.h>
#include <stdio.h>

void InitUart( void );
char LeeTeclado( void );

/*---[ InitUart() ]----------------------------------------------------
** Setup the serial port for 9600 baud at 11,059 MHz.
** Baud rate generator: timer #1
*/
void InitUart( void )
{
    SCON = 0x50;           /* SCON: mode 1, 8-bit UART, enable receiver    */
    TMOD|= 0x20;           /* TMOD: timer 1, mode 2, 8-bit reload          */
    TH1  = 253;            /* TH1:  reload value for 9600 baud @ 11,059 MHz*/
    TR1  = 1;              /* TR1:  timer 1 run                            */
    TI   = 1;              /* TI:   set TI to send first char of UART      */
}

/*---[ LeeTeclado() ]--------------------------------------------------
** Devuelve el c�digo ASCII de la tecla oprimida o null si no hay tecla
** oprimida
** Recibe:		nada
** Devuelve:	c�digo ASCII de la tecla/null si no hay tecla oprimida
*/
char LeeTeclado( void )
{
	char c;

	c = '\0';

	if( RI == 1 )
	{
		c = getchar();
		putchar('\n');
		RI = 0;
	}
	
	return c;
}


