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
const int CORE_LED_ACTIVITY = 1;				// Led de actividad SI/NO
const int CORE_LED_PIN = 46;



/*** Caracteres personalizados ***/
const byte CHAR_OFF[8] = {
	B00000000,
	B00000000,
	B00000100,
	B00001110,
	B00001110,
	B00000100,
	B00000000,
	B00000000
};
const byte CH_OFF = 0;

const byte CHAR_HEATER_ON[8] = {
	B00000100,
	B00010101,
	B00010101,
	B00011011,
	B00010001,
	B00010001,
	B00010001,
	B00001110
};
const byte CH_HEATER_ON  = 1;

const byte CHAR_HUMIDIFIER_ON[8] = {
	B00000100,
	B00001110,
	B00001110,
	B00011111,
	B00011111,
	B00011101,
	B00011111,
	B00001110
};
const byte CH_HUMIDIFIER_ON = 2;

const byte CHAR_DAYLIGHT_ON[8] = {
	B00000000,
	B00010101,
	B00001110,
	B00011011,
	B00001110,
	B00010101,
	B00000000,
	B00011111
};
const byte CH_DAYLIGHT_ON = 3;

const byte CHAR_ARROW_DOWN[8] = {
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00011111,
	B00001110,
	B00000100
};
const byte CH_ARROW_DOWN = 4;

const byte CHAR_ARROW_UP[8] = {
	B00000100,
	B00001110,
	B00011111,
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00000100
};
const byte CH_ARROW_UP = 5;

const byte CHAR_GRADES[8] = {
	B00000110,
	B00001001,
	B00001001,
	B00000110,
	B00000000,
	B00000000,
	B00000000,
	B00000000
};
const byte CH_GRADES = 6;

const byte CHAR_TANK_FULL[8] = {
	B00010001,
	B00011111,
	B00011111,
	B00011111,
	B00011111,
	B00011111,
	B00011111,
	B00011111
};

const byte CHAR_TANK_HALF[8] = {
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00011111,
	B00011111,
	B00011111,
	B00011111
};

const byte CHAR_TANK_EMPTY[8] = {
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00011011,
	B00011111
};

const byte CHAR_TANK_ERROR[8] = {
	B00010001,
	B00010001,
	B00011011,
	B00010101,
	B00011011,
	B00010001,
	B00011011,
	B00011111
};

const byte CH_TANK = 7;



/*** Metodos de entrada ***/
const unsigned int NUMBER_OF_KEYS = 6;
const unsigned int KEY_RIGHT_ID = 0;
const unsigned int KEY_RIGHT_PIN = 23;
const unsigned int KEY_DOWN_ID = 1;
const unsigned int KEY_DOWN_PIN = 25;
const unsigned int KEY_LEFT_ID = 2;
const unsigned int KEY_LEFT_PIN = 27;
const unsigned int KEY_UP_ID = 3;
const unsigned int KEY_UP_PIN = 29;
const unsigned int KEY_B_ID = 4;
const unsigned int KEY_B_PIN = 31;
const unsigned int KEY_A_ID = 5;
const unsigned int KEY_A_PIN = 33;



/*** Datos por defecto ***/
const int TEMP_MIN_TRIGGER = 25;			// Temperatura minima
const int TEMP_MAX_TRIGGER = 30;			// Temperatura maxima
const int TEMP_MIN_ALARM = 18;				// Alarma de temperatura minima
const int TEMP_MAX_ALARM = 35;				// Alarma de temperatura maxima
const int HUMIDITY_MIN_TRIGGER = 75;		// Humedad minima
const int HUMIDITY_MAX_TRIGGER = 85;		// Humedad maxima
const int HUMIDITY_MIN_ALARM = 70;			// Alarma de humedad baja
const int HUMIDITY_MAX_ALARM = 95;			// Alarma de humedad alta
const long int HUMIDITY_DUTY_CYCLE_ON = 100;		// Ciclo de activacion del humidificador (ON) en ticks (5s)
const long int HUMIDITY_DUTY_CYCLE_OFF = 400;		// Ciclo de activacion del humidificador (OFF) en ticks (20s)
const int SUNRISE_HOUR = 7;					// Hora de salida del sol
const int SUNRISE_MINUTE = 30;
const int SUNSET_HOUR = 20;					// Hora de la puesta del sol
const int SUNSET_MINUTE = 30;
const int BUZZER_ALARM = 1;					// Alarma sonora SI/NO



/*** Rango de valores absolutos ***/
const int ABS_TEMP_MIN = 5;					// Temperatura
const int ABS_TEMP_MAX = 60;
const int ABS_HUMI_MIN = 0;					// Humedad
const int ABS_HUMI_MAX = 100;
const int ABS_DUTY_MIN = 1;					// Limites del ciclo de trabajo (segundos)
const int ABS_DUTY_MAX = 7200;
const int ABS_DATETIME_YEAR_MIN = 2018;		// Fecha y hora
const int ABS_DATETIME_YEAR_MAX = 2199;		



/*** Configuracion del control ambiental ***/
// Configuracion de entradas
const unsigned int DHT_PIN = 50;				// Sensor de temperatura y humedad
const unsigned int TANK_LEVEL_EMPTY_PIN = 49;	// Sensor de la base del tanque
const unsigned int TANK_LEVEL_HALF_PIN = 47;	// Sensor de medio tanque
// Configuracion de salidas
const unsigned int IR_LIGHT_PIN = 40;		// Pin para activar la luz IR
const unsigned int HUMIDIFIER_PIN = 48;		// Pin para activar el humidificador
const unsigned int DAY_LIGHT_PIN = 42;		// Pin para activar la luz de dia
const unsigned int BUZZER_PIN = 41;			// Pin Buzzer de Alarma
// Parametros de la alarma
const int ALARM_TONE = 440;					// Tono de la alarma
const int ALARM_TONE_ON = 500;				// Duracion del tono
const int ALARM_TONE_OFF = 50;				// Pausa entre tonos (ticks de ejecucion)
const int ALARM_BLINK_SPEED = 10;			// Velocidad del parpadeo en ticks (5cent * 10 = 50cent, 0.5s);
const int SENSOR_ERROR_TIMEOUT = 100;		// Time out del sensor	



/*** Prototipos de datos de la EEPROM***/
struct Eeprom_d {
	unsigned long int checksum;
	unsigned long int humi_duty_cycle_on;
	unsigned long int humi_duty_cycle_off;
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