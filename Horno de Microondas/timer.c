//*********************************************************************
// TIMER.C
//*********************************************************************
#include <reg52.h>

#define TIMER0_COUNT    47103 	/* 20 ms @ 11,0592 MHz	*/  
#define TIC_100MS		10 		/* para simulador		*/  

void InitTimer0( void );
void TimerISR0( void );	// Atencion de interrupcion de timer 0
			
bit tic100ms;

/*---[ InitTimer0() ]--------------------------------------------------
** Setup timer 0.
*/
void InitTimer0( void )
{
	/* NO modificar */
	TMOD |= 0x01;		// TMOD: timer 0, mode 1, 16-bit sin auto recarga
    TR0 = 0;			// stop timer 0
    TL0 = ( TIMER0_COUNT & 0x00FF );
    TH0 = ( TIMER0_COUNT >> 8 );
    TR0 = 1;			// start timer 0
	ET0 = 1;
	EA  = 1;
}

//---[ TimerISR0() ]---------------------------------------------------
void TimerISR0() interrupt 1
{
	static unsigned char t;

    TR0 = 0;			// stop timer 0
    TL0 += ( TIMER0_COUNT & 0x00FF );
    TH0 += ( TIMER0_COUNT >> 8 );
    TR0 = 1;			// start timer 0
	TF0 = 0;

	t++;

	if( t >= TIC_100MS )	/* 100 ms */
	{	
		t = 0;
		tic100ms = 1;
	}
}

