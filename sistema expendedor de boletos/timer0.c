//*****************************************************************************
// TIMER0.C
// Funciones para el uso de los temporizadores/contadores del 8051/2
//*****************************************************************************
//#include <regx52.h>
#include <reg52.h>
#include <stdio.h>

#define CARGA_INICIAL_T0	(0xdc00)
#define TIC_100MS			10

bit tic100ms;

void InitTimer0( void );

/*---[ InitTimer0() ]----------------------------------------------------------
** Setup timer 0.
** ¡NO MODIFICAR! 
*/
void InitTimer0( void )
{
    TMOD &= 0xF0;
    TMOD |= 0x01;	// TMOD: timer 0, mode 1, 16-bit without reload

    TR0 = 0;		// stop timer 0
    TL0 = (CARGA_INICIAL_T0 & 0x00ff);		
	TH0 = (CARGA_INICIAL_T0 >> 8);
    TR0 = 1;		// start timer 0
}


/*---[ Timer0IRQ() ]-----------------------------------------------------------
** Genera una interrupción por desborde de timer 0.
** ¡NO MODIFICAR!
*/
void Timer0IRQ( void ) interrupt 1
{
	/* Realizar esta función, colocando el código que considere necesario */
	static unsigned char tic;

    TR0 = 0;		// stop timer 0
    TL0 = (CARGA_INICIAL_T0 & 0x00ff) + TL0;		
	TH0 = (CARGA_INICIAL_T0 >> 8) + TH0;
    TR0 = 1;		// start timer 0

	tic++;

	if( tic == TIC_100MS )
	{
		tic = 0;
		tic100ms = 1;
	}
}

								