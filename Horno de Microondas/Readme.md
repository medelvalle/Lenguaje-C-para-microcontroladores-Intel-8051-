
# Horno de microondas

Control de un horno de microondas. Para esto se cuenta con un microcontrolador AT89s52 que controla a través de sus puertos de E/S los siguientes sensores y actuadores.

+	1 teclado de 10 teclas numéricas, y 4 teclas de funciones (“Potencia”, “Tiempo”, “Inicio”, “Cancelar”), conectado a través de la línea      serie. Para los valores numéricos se recibe por línea serie el código ASCII de la tecla numérica pulsada, para las teclas de funciones se reciben el código ASCII de la inicial de la función seleccionada (‘P’-‘T’-‘I’-‘C’)
+	1 salida para control PWM del generador de microondas, conectada a P0.0 (1: enciende, 0: apaga).
+	1 salida para encender/apagar la luz interna del horno, conectada a P0.1 (1: enciende, 0: apaga).
+	1 interruptor para indicar si la puerta está abierta (0) o cerrada (1). Esta llave está conectada al puerto P0.7.
+	Un módulo display LCD, conectado a la línea serie

El sistema trabaja de la siguiente manera:
1.	Al encender el sistema, éste está en reposo.
2.	En el estado de reposo, se pueden realizar 3 funciones
2.1.	Seleccionar potencia de cocción: Aquí se ingresa 1 dígito que indicará el nivel de cocción (‘1’ mínimo, ‘5’: máximo)
2.2.	Seleccionar el tiempo de cocción: Aquí se ingresan, obligatoriamente, 4 dígitos, de a uno por vez, donde los 2 primeros ingresados indican los minutos de cocción (‘0’’0’ a ‘5’’9’) y los 2 últimos indican los segundos (‘0’’0’ a ‘5’’9’)
2.3.	Seleccionar el inicio de cocción: Con esta función se da comienzo a la cocción. Esta comienza solamente si la puerta esta cerrada. Si esto no ocurre se indica en el display y se vuelve a reposo. Cuando comienza la cocción se programa el controlador de PWM con el nivel de potencia seleccionado, y se enciende la luz interna del horno
Cualquiera de las funciones que se están llevando a cabo pueden ser canceladas, pulsando la tecla de “Cancelar”.
El orden en que se seleccionan estas opciones no interesa, cuando se selecciona “Inicio”, la cocción se realizará con los últimos valores de “Potencia” y “Tiempo” disponibles.
3.	Cuando se está “cocinando” pueden ocurrir 3 eventos:
3.1.	Finalización del tiempo de cocción: Esta es la salida normal, ocurre cuando finaliza el tiempo de cocción seleccionado.
3.2.	Tecla de “Cancelar” oprimida: El usuario decidió finalizar la cocción antes de tiempo.
3.3.	Apertura de puerta: Se detectó que la puerta del horno se ha abierto.
Cualquiera de los eventos presentados, se indican en el display y se pasa al estado de reposo, apagando el control PWM (nivel = ‘0’) y apagando la luz interna.

Realizar el diagrama de estados indicando claramente los estados y explicando los eventos que producen cambios de estados y las acciones a realizar en cada caso.

Realizar el programa de control del sistema, teniendo en cuenta las siguientes consideraciones:
+	No pueden declararse nuevas variables globales, ni dentro del main().
+	No puede cambiarse la visibilidad de las variables.
+	Todos los eventos que ocurren en superlazo - while(1) - se analizan cada 100 ms de forma tal que ninguna de las tareas allí realizadas frenen el recorrido del programa. 
