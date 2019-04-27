/*******************************************************************************

	N'gine para Arduino
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com

	Control ambiental se distribuye bajo la licencia CREATIVE COMMONS
	"Attribution-NonCommercial 4.0 International"
	https://creativecommons.org/licenses/by-nc/4.0/
	
	Sensor DHT

*******************************************************************************/



#ifndef __NGN_DHT_H
#define __NGN_DHT_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Modulos
#include "libs/SimpleDHT.h"    	// Sensor Humedad y temperatura DHT11
// N'gine
#include "ngn_settings.h"		// Parametros de la configuracion



/*** Definicion de la clase ***/
class NGN_Dht {
	
	public:
	
		// Constructor
		NGN_Dht();
		
		// Destructor
		~NGN_Dht();
		
		// Propiedades
		int temperature;		// Temperatura
		int humidity;			// Humedad
		
		// Metodos
		void Start(unsigned int pin);	// Inicia el sensor
		bool Read();					// Lee la informacion del sensor
		bool sensor_status;				// Estado del sensor

	
	private:

		// Objeto de la libreria del sensor
		SimpleDHT11 dht;
		
		// Pin donde esta conectado el sensor
		unsigned int pin_id;
		
		// Propiedades
		bool _update;
		
		// Metodos
		bool Update();
	
};



#endif