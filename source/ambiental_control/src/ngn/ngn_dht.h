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
	
	*** Se requieren las siguientes librerias ***
	DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
	Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

*******************************************************************************/



#ifndef __NGN_DHT_H
#define __NGN_DHT_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Arduino Libs
#include <DHT.h>
// N'gine
#include "ngn_defines.h"		// Definiciones propietarias
#include "ngn_settings.h"		// Parametros de la configuracion



/*** Constantes y estaticas ***/
// Objeto estatico de la clase
static DHT dht(DHT_PIN, DHT_TYPE);



/*** Definicion de la clase ***/
class NGN_Dht {
	
	public:
	
		// Constructor
		NGN_Dht();
		
		// Destructor
		~NGN_Dht();
		
		// Propiedades
		S8 temperature;				// Temperatura
		S8 humidity;				// Humedad
		
		// Metodos
		void Start();				// Inicia el sensor
		bool Read();				// Lee la informacion del sensor
		bool sensor_status;			// Estado del sensor

	
	private:
		
		// Propiedades
		bool _update;
		
		// Metodos
		bool Update();
	
};



#endif