//*****************************************************************************
// main.c
//
// Programacion aplicada en lenguaje de alto nivel
//*****************************************************************************
#include <reg52.h>
#include <stdio.h>

#define OFFSET_IMPRIMIR_BOLETO	0
#define OFFSET_SECCION			1
#define OFFSET_NUMERO_BOLETO	2
#define OFFSET_VUELTO			3

#define	FALSE	0
#define TRUE	1

extern void InitUart( void );
extern void InitTimer0( void );
extern void InitMaqEstados( void );
extern void MaquinaEstados( unsigned short int * );

extern bit tic100ms;

code char *precio[] = { "1.10" , "1.20" , "1.25" };

void main( void );

unsigned short int *pGlobal;
 
//----------------------------------- main() ----------------------------------
void main(void)
{
	unsigned short int intercambio[5];
   
	InitUart();
	InitTimer0();
	InitMaqEstados();

	IT0 = 1;			
	IT1 = 1;			
	ET0 = 1;
	EX0 = 1;
	EX1 = 1;
	EA  = 1; 

//--- Aqui debe inicializar variables, punteros globales y sistema interrupcion
	/* (1) completar */
	pGlobal = intercambio;
//--- Fin de inicializaciones

	while( 1 )
	{
		if( TRUE == tic100ms )
		{
			tic100ms = FALSE;
			MaquinaEstados (pGlobal);
			if ( *(pGlobal+OFFSET_IMPRIMIR_BOLETO)== TRUE)
			  {
			  pGlobal++;
			    intercambio[OFFSET_SECCION] = pGlobal[OFFSET_SECCION];
				intercambio[OFFSET_NUMERO_BOLETO]=pGlobal[OFFSET_NUMERO_BOLETO];
				intercambio[OFFSET_VUELTO]=pGlobal[OFFSET_VUELTO];
				if (intercambio[OFFSET_SECCION] == 1) 
				intercambio[OFFSET_IMPRIMIR_BOLETO]= *precio[0];
				if (intercambio[OFFSET_SECCION] == 2) 
				intercambio[OFFSET_IMPRIMIR_BOLETO]= *precio[1];
				if (intercambio[OFFSET_SECCION] == 3) 
				intercambio[OFFSET_IMPRIMIR_BOLETO]= *precio[2];
				printf ("sec:%bu  $%03bu",intercambio[); 	 
			  	printf ("num:%03bu", intercambio[pGlobal[2]]);
				printf ("vuelto: $0,%02bu", intercambio[pGlobal[3]]);
			  }
			 
			/* (2) completar
			** Aqui debe llamar a la máquina de estados y realizar la impresion
			** de Sección, Precio, Número de boleto y Vuelto, cuando reciba la
			** orden de "imprimir"
			*/
		}
	}
}

