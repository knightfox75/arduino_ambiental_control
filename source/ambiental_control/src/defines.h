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
// N'gine
#include "ngn/ngn.h"


/*** Configuracion de los tiempos de ejecucion ***/
const U8 CORE_FREQ_DIVIDER = 10;			// Base de division del tiempo de ejecucion para los milisegundos (10 por defecto, para escalar los milisegundos a centesimas de segundo)
const U8 CORE_MAIN_UPDATE_FREQ = 5;			// Frecuencia de actualizacion del programa (principal)
const U8 CORE_LED_ACTIVITY = 1;				// Led de actividad SI/NO
const U8 CORE_LED_PIN = 46;



/*** Caracteres personalizados ***/
const U8 CHAR_OFF[8] = {
	B00000000,
	B00000000,
	B00000100,
	B00001110,
	B00001110,
	B00000100,
	B00000000,
	B00000000
};
const U8 CH_OFF = 0;

const U8 CHAR_HEATER_ON[8] = {
	B00000100,
	B00010101,
	B00010101,
	B00011011,
	B00010001,
	B00010001,
	B00010001,
	B00001110
};
const U8 CH_HEATER_ON  = 1;

const U8 CHAR_HUMIDIFIER_ON[8] = {
	B00000100,
	B00001110,
	B00001110,
	B00011111,
	B00011111,
	B00011101,
	B00011111,
	B00001110
};
const U8 CH_HUMIDIFIER_ON = 2;

const U8 CHAR_DAYLIGHT_ON[8] = {
	B00000000,
	B00010101,
	B00001110,
	B00011011,
	B00001110,
	B00010101,
	B00000000,
	B00011111
};
const U8 CH_DAYLIGHT_ON = 3;

const U8 CHAR_ARROW_DOWN[8] = {
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00011111,
	B00001110,
	B00000100
};
const U8 CH_ARROW_DOWN = 4;

const U8 CHAR_ARROW_UP[8] = {
	B00000100,
	B00001110,
	B00011111,
	B00000100,
	B00000100,
	B00000100,
	B00000100,
	B00000100
};
const U8 CH_ARROW_UP = 5;

const U8 CHAR_GRADES[8] = {
	B00000110,
	B00001001,
	B00001001,
	B00000110,
	B00000000,
	B00000000,
	B00000000,
	B00000000
};
const U8 CH_GRADES = 6;

const U8 CHAR_TANK_FULL[8] = {
	B00010001,
	B00011111,
	B00011111,
	B00011111,
	B00011111,
	B00011111,
	B00011111,
	B00011111
};

const U8 CHAR_TANK_HALF[8] = {
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00011111,
	B00011111,
	B00011111,
	B00011111
};

const U8 CHAR_TANK_EMPTY[8] = {
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00010001,
	B00011011,
	B00011111
};

const U8 CHAR_TANK_ERROR[8] = {
	B00010001,
	B00010001,
	B00011011,
	B00010101,
	B00011011,
	B00010001,
	B00011011,
	B00011111
};

const U8 CH_TANK = 7;



/*** Metodos de entrada ***/
const U8 NUMBER_OF_KEYS = 6;
const U8 KEY_RIGHT_ID = 0;
const U8 KEY_RIGHT_PIN = 23;
const U8 KEY_DOWN_ID = 1;
const U8 KEY_DOWN_PIN = 25;
const U8 KEY_LEFT_ID = 2;
const U8 KEY_LEFT_PIN = 27;
const U8 KEY_UP_ID = 3;
const U8 KEY_UP_PIN = 29;
const U8 KEY_B_ID = 4;
const U8 KEY_B_PIN = 31;
const U8 KEY_A_ID = 5;
const U8 KEY_A_PIN = 33;



/*** Datos por defecto ***/
const S8 TEMP_MIN_TRIGGER = 25;				// Temperatura minima
const S8 TEMP_MAX_TRIGGER = 30;				// Temperatura maxima
const S8 TEMP_MIN_ALARM = 18;				// Alarma de temperatura minima
const S8 TEMP_MAX_ALARM = 35;				// Alarma de temperatura maxima
const S8 HUMIDITY_MIN_TRIGGER = 75;			// Humedad minima
const S8 HUMIDITY_MAX_TRIGGER = 85;			// Humedad maxima
const S8 HUMIDITY_MIN_ALARM = 70;			// Alarma de humedad baja
const S8 HUMIDITY_MAX_ALARM = 95;			// Alarma de humedad alta
const S32 HUMIDITY_DUTY_CYCLE_ON = 100;		// Ciclo de activacion del humidificador (ON) en ticks (5s)
const S32 HUMIDITY_DUTY_CYCLE_OFF = 400;	// Ciclo de activacion del humidificador (OFF) en ticks (20s)
const S8 SUNRISE_HOUR = 7;					// Hora de salida del sol
const S8 SUNRISE_MINUTE = 30;
const S8 SUNSET_HOUR = 20;					// Hora de la puesta del sol
const S8 SUNSET_MINUTE = 30;
const U8 BUZZER_ALARM = 1;					// Alarma sonora SI/NO



/*** Rango de valores absolutos ***/
const S8 ABS_TEMP_MIN = 0;					// Temperatura
const S8 ABS_TEMP_MAX = 50;
const S8 ABS_HUMI_MIN = 20;					// Humedad
const S8 ABS_HUMI_MAX = 90;
const S32 ABS_DUTY_MIN = 1;					// Limites del ciclo de trabajo (segundos)
const S32 ABS_DUTY_MAX = 7200;
const S16 ABS_DATETIME_YEAR_MIN = 2018;		// Fecha y hora
const S16 ABS_DATETIME_YEAR_MAX = 2199;		



/*** Configuracion del control ambiental ***/
// Configuracion de entradas
const U8 TANK_LEVEL_EMPTY_PIN = 49;			// Sensor de la base del tanque
const U8 TANK_LEVEL_HALF_PIN = 47;			// Sensor de medio tanque
// Configuracion de salidas
const U8 IR_LIGHT_PIN = 40;					// Pin para activar la luz IR
const U8 HUMIDIFIER_PIN = 48;				// Pin para activar el humidificador
const U8 DAY_LIGHT_PIN = 42;				// Pin para activar la luz de dia
const U8 BUZZER_PIN = 41;					// Pin Buzzer de Alarma
// Parametros de la alarma
const U16 ALARM_TONE = 440;					// Tono de la alarma
const U16 ALARM_TONE_ON = 500;				// Duracion del tono
const U16 ALARM_TONE_OFF = 50;				// Pausa entre tonos (ticks de ejecucion)
const U16 ALARM_BLINK_SPEED = 10;			// Velocidad del parpadeo en ticks (5cent * 10 = 50cent, 0.5s);
const U16 SENSOR_ERROR_TIMEOUT = 100;		// Time out del sensor	



/*** Prototipos de datos de la EEPROM***/
struct Eeprom_d {
	U32 checksum;
	S32 humi_duty_cycle_on;
	S32 humi_duty_cycle_off;
	S8 min_temp;
	S8 max_temp;
	S8 min_temp_alarm;
	S8 max_temp_alarm;
	S8 min_humi;
	S8 max_humi;
	S8 min_humi_alarm;
	S8 max_humi_alarm;
	S8 sunrise_hour;
	S8 sunrise_minute;
	S8 sunset_hour;
	S8 sunset_minute;
	U8 alarm_buzzer;
};



#endif