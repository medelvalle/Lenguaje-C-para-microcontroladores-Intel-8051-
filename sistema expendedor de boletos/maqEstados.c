//*****************************************************************************
// maqEstados.c
//*****************************************************************************
//#include <regx52.h>
#include <reg52.h>

#define REPOSO			100
#define VENTA			101
#define ANULACION		102

#define OFF		0
#define ON		1
#define	FALSE	0
#define TRUE	1

#define OFFSET_IMPRIMIR_BOLETO	0
#define OFFSET_SECCION			1
#define OFFSET_NUMERO_BOLETO	2
#define OFFSET_VUELTO			3

#define TIME_OUT_VENTA		6000
#define TIME_OUT_LED		100

extern bit flagNuevaVenta;
extern bit flagNuevaMoneda;

void MaquinaEstados( unsigned short int * );
void InitMaqEstados( void );
unsigned short int LeerSeccion( void );
unsigned short int LeerMonedero( void );

static char estado;
static unsigned short int numeroBoleto;	//Contador de numero de boletos

sbit LED_VENTA  = P1^0;
sbit REPOSICION = P1^1;

code unsigned short int tarifaCentavos[]  = { 110, 120, 125 };

/*---[ MaquinaEstados() ]------------------------------------------------------
** Maquina de estado disparada por tic de 100 ms desde main().
** Recibe:   puntero a arreglo para intercambio de datos con main()
** Devuelve: nada 
*/
void MaquinaEstados( unsigned short int *ptr )
{

  char seccion;
  unsigned short int dineroIngresado;
  unsigned int timeOut;
  

  switch(estado)
   {	
	 case REPOSO:
	 
	 	if (flagNuevaVenta==TRUE) 
	   	  {
		 	flagNuevaVenta=FALSE;
		 	LED_VENTA=0; //prendo led
		 	ptr[OFFSET_SECCION] = LeerSeccion();
			seccion = ptr[OFFSET_SECCION];
		 	estado=VENTA;
		 	dineroIngresado=0;
		 	timeOut=0;
	      }
	 break;

	 case VENTA:
	
	 	timeOut++;
	 	if (timeOut==TIME_OUT_VENTA)
	   	  {
		 	dineroIngresado=0;
		 	estado=ANULACION;
		 	timeOut=0;
	      }
	 	else if (flagNuevaMoneda==TRUE)
			{
			  flagNuevaMoneda=FALSE;
			  dineroIngresado=dineroIngresado+LeerMonedero();	/* (5) completar */
              if (dineroIngresado>=tarifaCentavos[seccion])
	       		{ //vender boleto
				  numeroBoleto++;
			      LED_VENTA=1;
			      estado=REPOSO;
				  ptr[OFFSET_IMPRIMIR_BOLETO] = TRUE;
				  ptr[OFFSET_NUMERO_BOLETO]=numeroBoleto;
				  ptr[OFFSET_VUELTO]= dineroIngresado-tarifaCentavos[seccion];
			    }
			}
	 break;

	 case ANULACION:
			 	
	    timeOut++;
		if (REPOSICION==0)
		  {
		    estado=REPOSO;
			LED_VENTA=1;
		  }
		else if (timeOut==TIME_OUT_LED)
			{
		      timeOut=0;
			  if (LED_VENTA==1) 
				{
				 LED_VENTA=0;
				}
			  else LED_VENTA=1;   
	        }
	 break;
   }
 // return estado;
}
/*---[ InitMaqEstados() ]------------------------------------------------------
** Inicializa la máquina de estados
*/
void InitMaqEstados( void )
{
	estado = REPOSO;
	numeroBoleto = 0;
}

unsigned short int LeerSeccion( void )
{
	switch( P0 & 0xe0 )
	{
		case 0xc0:  return 1;
		case 0xa0:  return 2;
		case 0x60:  return 3;
		default:	return 1;
	}
}

unsigned short int LeerMonedero( void )
{
	switch( P0 & 0x1f )
	{
		case 0x01: 	return   5;
		case 0x02: 	return  10;
		case 0x04: 	return  25;
		case 0x08: 	return  50;
		case 0x10: 	return 100;
		default:	return   0;
	}
}
