//*********************************************************************
// maqEstados.C
//*********************************************************************
#include <reg52.h>
#include <stdio.h>
//----- Definiciones generales
#define SI		1
#define NO 		0
#define ABIERTA 0
#define CERRADA 1

//----- Posibles estados del horno microondas
#define REPOSO					100
#define PROGRAMANDO_POTENCIA	101
#define PROGRAMANDO_TIEMPO		102
#define	COCINANDO				103


code char mensaje1[] = "Ingrese potencia [1-5]";
code char mensaje2[] = "Ingrese tiempo [mmss]";
code char mensaje3[] = "Cocinando...";
code char mensaje4[] = "Cocci�n finalizada";
code char mensaje5[] = "Cocci�n interrumpida, cancelaci�n";
code char mensaje6[] = "Cocci�n interrumpida, puerta abierta";

void InitMaqEstados( void );
void MaqEstados( char );
bit Puerta( void );
void ControlPWM( char );
void Luz( bit b );
unsigned int ConvierteTiempo( char *p );

char estado;
unsigned char potencia;
unsigned int  tiempoCoccion;
static int cuento;
static unsigned char ctiempo[5];
/* declaraciones para PWM, LUZ y PUERTA */
sbit PWM=P0^0;
sbit LUZ=P0^1;
sbit PUERTA=P0^7;


/*---[ MaqEstados() ]--------------------------------------------------
*/
void MaqEstados( char input )
{
 static char ctiempo[5];
 static int cuento;

	switch(estado)
	{
	  case REPOSO:
	  		if(input=='P'){
				estado=PROGRAMANDO_POTENCIA;}
			if(input=='T'){
				estado=PROGRAMANDO_TIEMPO;
				cuento=0;}
			if(input=='I'){
				estado=COCINANDO;}
			if(input=='C'){
				estado=REPOSO;
				//potencia=0;
				Luz(NO);}
	   break;
	   

      case PROGRAMANDO_POTENCIA:
	  		printf("%s",mensaje1);
			if(input=='C'){
			  estado=REPOSO;
			  }
			else
			{
			  potencia=input;
			  estado=REPOSO;}
		break;

	  case PROGRAMANDO_TIEMPO:
	  		printf("%",mensaje2);
			if(input=='C'){
			  estado=REPOSO;}
			else
			  cuento++;
			  if(cuento==5){
			    ctiempo[cuento]='\0';
				tiempoCoccion=ConvierteTiempo(&ctiempo);
				estado=REPOSO;
				}
			  else
			  {
				ctiempo[cuento]=input;}
		break;

	  case COCINANDO:
	  		
			if(input=='C'){
			  estado=REPOSO;
			  printf("%s",mensaje5); }
			else	  		
			  if(PUERTA){
				ControlPWM(potencia);
				printf("%s",mensaje3);
				Luz(SI);
				}
			  else
			  {
			    printf("%s",mensaje6);
				estado=REPOSO;
				Luz(SI);}
			

			if(tiempoCoccion==0){
				printf("%s",mensaje4);
				estado=REPOSO;
				Luz(NO);}
				
		break;
	 }
	}
/*---[ InitMaqEstados() ]--------------
*/
void InitMaqEstados( void )
{
	estado = REPOSO;
	potencia = 5;
	tiempoCoccion = 60;
	ControlPWM( NO );
	Luz(NO);
}

/*---[ ControlPWM() ]------------------
** Realiza el control de PWM
** (ESTA FUNCI�N ES FICTICIA SOLO INTERESA LA INDICACION EN LA SALIDA)
** Recibe:		nivel de potencia de cocci�n
** Devuelve:	nada
*/
void ControlPWM( char w )
{
	if( w == 0 )
		PWM = 0;
	else
		PWM = 1;
}

/*---[ ConvierteTiempo() ]---------------------------------------------
** Convierte el arreglo (cadena de caracteres ASCII) recibida como
** argumento, en un valor entero que representa el tiempo de cocci�n
** (expresado en tics de 100 ms)
** Recibe:		puntero a la cadena a convertir, formato de la cadena:
**				mmss'\0'. Ejemplo '1''5''3''0''\0' representa 15 m 30 s
** Devuelve:	valor entero del tiempo de cocci�n expresado en tic de
**				100 ms. Para el ejemplo anterior devuelve: 9300 
*/
unsigned int ConvierteTiempo( char *p )
{

	unsigned int minutos,segundos,ttotal;

	minutos=(p[0]-48)*10;		  // Ejemplo, convierto el 1 cadena a decena 10
	minutos=minutos + (p[1]-48);	  // convierto la unidad 5 cadena a unidad y sumo 10+5 ahora es int
	segundos=(p[2]-48)*10;		  // convierto decena cadena de segundos a decena int 30
	segundos=segundos + (p[3]-48); //convierto unidad cadena a unidad int y lo sumo a la decena int
    ttotal=((minutos*60)+segundos)*10;

	return ttotal;

}

/*---[ Puerta() ]------------------------------------------------------
** Consulta el estado del interruptor adosado a la puerta
** Recibe:		nada
** Devuelve:	estado de la puerta (ABIERTA/CERRADA) 
*/
bit Puerta( void )
{
static bit estadoPuerta;

	if(PUERTA)
	  estadoPuerta=CERRADA;
	else
	  estadoPuerta=ABIERTA;

	return estadoPuerta;
}

/*---[ Luz() ]--------------------------------------------------
** Enciende/apaga la luz del interior del horno
** Recibe:		acci�n que se realiza (encender/apagar)
** Devuelve:	nada
*/
void Luz( bit b )

{
	if(b==1)
	  LUZ=1;
	else	  
	  LUZ=0;
}
