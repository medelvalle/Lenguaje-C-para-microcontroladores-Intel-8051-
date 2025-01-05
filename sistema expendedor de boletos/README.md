Código C para microcontrolador 8051

Compidador: Keil, SDCC (http://sdcc.sourceforge.net)
IDE: Code::Block (http://www.codeblocks.org)

# Sistema expendedor de boletos

El sistema cuenta con las siguientes características:
   + 5 Entradas de monedero (P0.0 ... P0.4 activas nivel alto)
   + 3 Entradas selectoras de viaje (P0.5 ... P0.7 activas nivel bajo)
   + 1 Salida (LED) indicadora de venta de boleto (P1.0: 0 = LED ON, 1 = LED OFF)
   + 1 Entrada (REPOSICIÓN) para reestablecer una venta inválida (P1.1 activa bajo)

La orden de "inicio de venta" llega a través de la interrupción externa 1, cuando se indica el tipo de tarifa que se va a cobrar.

Las entradas del monedero (que solo acepta una moneda por vez) están conectadas también al pin de interrupción externa 0 con una conexión NOR, de forma tal que al ingresar una moneda, se activa una petición de interrupción externa 0.
La asignación de las entradas de monedero son las siguientes:
   + P0.0: Detección moneda de   5 centavos
   + P0.1: Detección moneda de 10 centavos
   + P0.2: Detección moneda de 25 centavos
   + P0.3: Detección moneda de 50 centavos
   + P0.4: Detección moneda de   1 peso (100 centavos)

El objetivo del sistema a implementar es realizar la venta de un pasaje, de acuerdo con la siguiente secuencia:

1.	Al detectar una orden de "inicio de venta" indicarla en el LED respectivo, numerar el boleto y luego leer por el puerto P0 que tipo de tarifa que se va a cobrar, según el siguiente cuadro tarifario:
   + P0.5: SECCION 1, tarifa  $1,10 (110 centavos).
   + P0.6: SECCION 2, tarifa  $1,20 (120 centavos).
   + P0.7: SECCION 3, tarifa  $1,25 (125 centavos).

2.	Detectar las monedas ingresadas hasta alcanzar (o superar) el precio del boleto solicitado
3.	Una vez que se ingreso el dinero suficiente:
   + Indicar el "fin de venta" apagando el LED de venta de boleto (LED P1.0 = OFF)
   + Enviar por línea serie dos cadenas de caracteres que indican lo siguiente:
 		Cadena 1: sección y precio del boleto
		Cadena 2: número de boleto
   + Enviar por línea serie el importe del vuelto (expresado en centavos).
4.	Si el dinero ingresado no es suficiente durante el tiempo de venta, esta finaliza. Si esto ocurriese, debe quedar titilando el led de venta y descontar el boleto no vendido. La máquina se  reestablece a su estado de reposo activando la entrada REPOSICIÓN (activa bajo). 
5.	El sistema expendedor debe quedar operativo para otra venta de boleto.

La máquina de estados se realiza directamente en el superlazo, y se ejecuta cada 100 ms.
 
