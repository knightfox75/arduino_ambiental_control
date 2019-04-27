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
	
	Nucleo de Ejecucion

*******************************************************************************/



#ifndef __CORE_H
#define __CORE_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// N'gine
#include "ngn/ngn.h"
// Proyecto
#include "defines.h"
#include "eeprom_data.h"
#include "ambiental_control.h"


/*** Definicion de la clase ***/
class Core {
	
	public:
	
		// Constructor
		Core();
		
		// Destructor
		~Core();
		
		// Al iniciar el programa
		void Start();
		
		// Ejecuta regularmente
		void Run();
		
	
	private:
	
		// Variables de control
		bool _led_blink;			// Control del blink del led
		bool _update;				// Control de ejecucion del programa
		
		// Objetos adicionales de codigo
		AmbientalControl ambiental;		// Control de los sensores
		EepromData eeprom;				// Gestion de la EEPROM

		// Datos del control del programa
		Eeprom_d data;
		
		// Funciones privadas
		void Logic();		// Logica del programa
		void Common();		// Metodos comunes a todos los estados
				
};



#endif