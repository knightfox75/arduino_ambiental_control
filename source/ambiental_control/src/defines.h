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
	
	Definiciones, variables, constantes y objetos estaticos (singletons)

*******************************************************************************/



#ifndef __DEFINES_H
#define __DEFINES_H


/*** Includes ***/
#include <Arduino.h>


/*** Configuracion de los tiempos de ejecucion ***/
const long int CORE_FREQ_DIVIDER = 10;			// Base de division del tiempo de ejecucion para los milisegundos (10 por defecto, para escalar los milisegundos a centesimas de segundo)
const long int CORE_MAIN_UPDATE_FREQ = 5;		// Frecuencia de actualizacion del programa (principal)
const int CORE_LED_ACTIVITY = 0;				// Led de actividad SI/NO



/*** Caracteres personalizados ***/
const byte char_off[8] = {
	B00000000,
	B00000000,
	B00000100,
	B00001110,
	B00001110,
	B00000100,
	B00000000,
	B00000000
};
const byte char_heater_on[8] = {
	B00000100,
	B00010101,
	B00010101,
	B00011011,
	B00010001,
	B00010001,
	B00010001,
	B00001110
};
const byte char_humidifier_on[8] = {
	B00000100,
	B00001110,
	B00001110,
	B00011111,
	B00011111,
	B00011101,
	B00011111,
	B00001110
};
const byte char_daylight_on[8] = {
	B00000000,
	B00010101,
	B00001110,
	B00011011,
	B00001110,
	B00010101,
	B00000000,
	B00011111
};
const byte char_arrow_down[8] = {
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00011111,
	B00001110,
	B00000100
};
const byte char_arrow_up[8] = {
	B00000100,
	B00001110,
	B00011111,
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00000100
};



/*** Metodos de entrada ***/
const unsigned int NUMBER_OF_KEYS = 6;
const unsigned int SENSOR_WATER_LOW_ID = 0;
const unsigned int SENSOR_WATER_LOW_PIN = 30;
const unsigned int SENSOR_WATER_EMPTY_ID = 1;
const unsigned int SENSOR_WATER_EMPTY_PIN = 31;
const unsigned int KEY_UP_ID = 2;
const unsigned int KEY_UP_PIN = 32;
const unsigned int KEY_DOWN_ID = 3;
const unsigned int KEY_DOWN_PIN = 33;
const unsigned int KEY_LEFT_ID = 4;
const unsigned int KEY_LEFT_PIN = 34;
const unsigned int KEY_RIGHT_ID = 5;
const unsigned int KEY_RIGHT_PIN = 35;



/*** Datos por defecto ***/
const int TEMP_MIN_TRIGGER = 25;		// Temperatura minima
const int TEMP_MAX_TRIGGER = 30;		// Temperatura maxima
const int TEMP_MIN_ALARM = 18;			// Alarma de temperatura minima
const int TEMP_MAX_ALARM = 35;			// Alarma de temperatura maxima
const int HUMIDITY_MIN_TRIGGER = 60;	// Humedad minima
const int HUMIDITY_MAX_TRIGGER = 70;	// Humedad maxima
const int HUMIDITY_MIN_ALARM = 50;		// Alarma de humedad baja
const int HUMIDITY_MAX_ALARM = 80;		// Alarma de humedad alta
const int SUNRISE_HOUR = 7;				// Hora de salida del sol
const int SUNRISE_MINUTE = 30;
const int SUNSET_HOUR = 20;				// Hora de la puesta del sol
const int SUNSET_MINUTE = 30;
const int BUZZER_ALARM = 0;				// Alarma sonora SI/NO



/*** Configuracion del control ambiental ***/
// Configuracion de entradas
const unsigned int DHT_PIN = 50;			// Sensor de temperatura y humedad
// Configuracion de salidas
const unsigned int IR_LIGHT_PIN = 40;		// Pin para activar la luz IR
const unsigned int HUMIDIFIER_PIN = 42;		// Pin para activar el humidificador
const unsigned int DAY_LIGHT_PIN = 44;		// Pin para activar la luz de dia
const unsigned int BUZZER_PIN = 52;			// Pin Buzzer de Alarma
// Parametros de la alarma
const int ALARM_TONE = 440;				// Tono de la alarma
const int ALARM_TONE_ON = 500;			// Duracion del tono
const int ALARM_TONE_OFF = 50;			// Pausa entre tonos (ticks de ejecucion)
const int ALARM_BLINK_SPEED = 10;		// Velocidad del parpadeo en ticks;
const int SENSOR_ERROR_TIMEOUT = 100;	// Time out del sensor	



/*** Prototipos de datos de la EEPROM***/
struct Eeprom_d {
	unsigned int checksum;
	byte min_temp;
	byte max_temp;
	byte min_temp_alarm;
	byte max_temp_alarm;
	byte min_humi;
	byte max_humi;
	byte min_humi_alarm;
	byte max_humi_alarm;
	byte sunrise_hour;
	byte sunrise_minute;
	byte sunset_hour;
	byte sunset_minute;
	byte alarm_buzzer;
};



#endif