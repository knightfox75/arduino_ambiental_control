/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Archivo principal del proyecto (ejecucion)
	
*******************************************************************************/



/*** Includes ***/
#include "src/core.h"



/*** Crea los objetos ***/
Core core;



/*** Al iniciar ***/
void setup() {
	core.Start();
}



/*** Bucle principal ***/
void loop() {
	core.Update();
}