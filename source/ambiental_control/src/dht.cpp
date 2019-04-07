/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Sensor DHT

*******************************************************************************/



/*** Includes ***/
// Includes del proyecto
#include "dht.h"



/*** Contructor ***/
Dht::Dht() {
}



/*** Destructor ***/
Dht::~Dht() {
}



/*** Inicia el sensor ***/
void Dht::Start() {
	
	temperature = 0;
	humidity = 0;
	
	_update = false;
	
	pinMode(DHT_PIN_INPUT, INPUT);
	
	sensor_status = Update();
	delay((DHT_UPDATE_FREQ * 10));
	
}



/*** Lee la informacion del sensor ***/
bool Dht::Read() {
	
	// Si no se ha alcanzado el tiempo de refresco, sal
	if ((((long int)(millis() / DHT_FREQ_DIVIDER)) % DHT_UPDATE_FREQ) != 0) {
		_update = false;
		return sensor_status;
	}
	// Si ya se ha actualizado en este ciclo, sal
	if (_update) return sensor_status;

	// Indica que ya se ha actualizado
	_update = true;
	
	// Actualiza el estado del sensor
	sensor_status = Update();
	
	return sensor_status;
	
}



/*** Actualiza el estado del sensor ***/
bool Dht::Update() {
	
	// Variables para la lectura de datos
	byte temp = 0, humi = 0, data[40] = {0};
	
	// Lee la informacion del sensor
	if (dht.read(DHT_PIN_INPUT, &temp, &humi, data)) {
		
		temperature = 0;
		humidity = 0;
		return false;
		
	} else {
		
		temperature = (int)temp;
		humidity = (int)humi;
		
	}
	
	return true;
	
}