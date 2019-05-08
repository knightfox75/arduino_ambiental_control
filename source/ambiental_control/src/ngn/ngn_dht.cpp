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
	
	*** Se requieren las siguientes librerias ***
	DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
	Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

*******************************************************************************/



/*** Includes ***/
// Includes de N'gine
#include "ngn_dht.h"



/*** Constructor ***/
NGN_Dht::NGN_Dht() {	
}



/*** Destructor ***/
NGN_Dht::~NGN_Dht() {
}



/*** Inicia el sensor ***/
void NGN_Dht::Start() {
	
	temperature = 0;
	humidity = 0;
	
	_update = false;
	
	dht.begin();

	delay((DHT_UPDATE_FREQ * DHT_FREQ_DIVIDER));
	
	sensor_status = Update();
	
}



/*** Lee la informacion del sensor ***/
bool NGN_Dht::Read() {
	
	// Si no se ha alcanzado el tiempo de refresco, sal
	if ((((U32)(millis() / DHT_FREQ_DIVIDER)) % DHT_UPDATE_FREQ) != 0) {
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
	
	// Variables
	bool r = true;
	
	// Lee la temperatura
	float temp = dht.readTemperature();
	// Si hay error de temperatura
	if (isnan(temp)) {
		// Informa del error
		temperature = 0;
		r = false;
	} else {
		// Lee los datos
		temperature = (S8)temp;
	}
	
	// Lee la humedad relativa
	float humi = dht.readHumidity();
	// Si hay error de temperatura
	if (isnan(humi)) {
		// Informa del error
		humidity = 0;
		r = false;
	} else {
		// Lee los datos
		humidity = (S8)humi;
	}
	
	// Devuelve el resultado
	return r;
	
}