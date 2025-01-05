//*********************************************************************
// INTE.C
// Funciones para el uso de las lineas de interrupciones externas 8052
//*********************************************************************
#include <reg52.h>

void atExt0( void );
void atExt1( void );

bit flagNuevaVenta;
bit flagNuevaMoneda;

#define	FALSE	0
#define TRUE	1

/*---[ atExt0() ]------------------------------------------------------
** Atencion de interrupcion externa 0
*/
void atExt0() interrupt 0
{
  flagNuevaMoneda=TRUE;	/* (3) completar */
}

/*---[ atExt1() ]------------------------------------------------------
** Atencion de interrupcion externa 1
*/
void atExt1() interrupt 2
{
  //inicio de venta
   flagNuevaVenta=TRUE;	/* (4) completar */
}


