//*****************************************************************************
// main.c
//*****************************************************************************
#include <reg52.h>

extern bit tic100ms;
extern char LeeTeclado( void );
extern void InitTimer0( void );
extern void InitUart( void );
extern void InitMaqEstados( void );
extern void MaqEstados( char );

void main( void );

//----------------------------------- main() ----------------------------------
void main( void )
{
	char tecla;

	InitTimer0();
	InitUart();
	InitMaqEstados();

	ET0 = 1;
	EA  = 1;

	while( 1 )
	{
		if( tic100ms == 1 )
		{
			tic100ms = 0;

			tecla = LeeTeclado();
			MaqEstados( tecla );
		}
	}
}

