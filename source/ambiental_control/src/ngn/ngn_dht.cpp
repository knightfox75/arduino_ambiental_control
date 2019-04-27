/*******************************************************************************

	N'gine para Arduino
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com

	N'gine para Arduino se distribuye bajo la licencia CREATIVE COMMONS
	"Attribution-NonCommercial 4.0 International"
	https://creativecommons.org/licenses/by-nc/4.0/
	
	Sensor DHT

*******************************************************************************/



/*** Includes ***/
// Includes de N'gine
#include "ngn_dht.h"



/*** Constructor ***/
NGN_Dht::NGN_Dht() {
	
	pin_id = 0;
	
}



/*** Destructor ***/
NGN_Dht::~NGN_Dht() {
}



/*** Inicia el sensor ***/
void NGN_Dht::Start(unsigned int pin) {
	
	temperature = 0;
	humidity = 0;
	
	_update = false;
	
	pin_id = pin;
	pinMode(pin_id, INPUT);
	
	sensor_status = Update();
	delay((DHT_UPDATE_FREQ * 10));
	
}



/*** Lee la informacion del sensor ***/
bool NGN_Dht::Read() {
	
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
bool NGN_Dht::Update() {
	
	// Variables para la lectura de datos
	byte temp = 0, humi = 0, data[40] = {0};
	
	// Lee la informacion del sensor
	if (dht.read(pin_id, &temp, &humi, data)) {
		
		temperature = 0;
		humidity = 0;
		return false;
		
	} else {
		
		temperature = (int)temp;
		humidity = (int)humi;
		
	}
	
	return true;
	
}