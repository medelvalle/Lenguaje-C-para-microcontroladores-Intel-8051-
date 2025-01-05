//*********************************************************************
// SERIE_IO.C
// Funciones para utilizar la UART interna del 8051/2
// Funciones para recibir la programacion de las salidas, desde PC
//*********************************************************************
#include <reg52.h>

void InitUart( void );

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


