/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com

	Control ambiental se distribuye bajo la licencia CREATIVE COMMONS
	"Attribution-NonCommercial 4.0 International"
	https://creativecommons.org/licenses/by-nc/4.0/
	
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
	core.Run();
}
