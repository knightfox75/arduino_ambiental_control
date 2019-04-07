/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Sensor DHT

*******************************************************************************/



#ifndef __DHT_H
#define __DHT_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Modulos
#include "libs/SimpleDHT.h"           // Sensor Humedad y temperatura DHT11
// Proyecto
#include "defines.h"



/*** Definicion de la clase ***/
class Dht {
	
	public:
	
		// Constructor
		Dht();
		
		// Destructor
		~Dht();
		
		// Propiedades
		int temperature;		// Temperatura
		int humidity;			// Humedad
		
		// Metodos
		void Start();			// Inicia el sensor
		bool Read();			// Lee la informacion del sensor
		bool sensor_status;		// Estado del sensor

	
	private:
	
		// Objeto de la libreria del sensor
		SimpleDHT11 dht;
		
		// Propiedades
		bool _update;
		
		// Metodos
		bool Update();
	
};



#endif