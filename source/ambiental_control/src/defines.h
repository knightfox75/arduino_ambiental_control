/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Definiciones, variables, constantes y objetos estaticos (singletons)

*******************************************************************************/



#ifndef __DEFINES_H
#define __DEFINES_H


/*** Includes ***/
#include <Arduino.h>
#include <LiquidCrystal.h>			// Display LCD



/*** core.h ***/
const long int CORE_FREQ_DIVIDER = 10;			// Base de division del tiempo de ejecucion para los milisegundos (10 por defecto, para escalar los milisegundos a centesimas de segundo)
const long int CORE_MAIN_UPDATE_FREQ = 5;		// Frecuencia de actualizacion del programa (principal)
const int CORE_LED_ACTIVITY = 0;				// Led de actividad SI/NO
const int CORE_BUFFER_ALARM = 1;				// Alarma sonora SI/NO

const unsigned int CORE_IR_LIGHT_PIN = 40;		// Pin para activar la luz IR
const unsigned int CORE_HUMIDIFIER_PIN = 42;	// Pin para activar el humidificador
const unsigned int CORE_DAY_LIGHT_PIN = 44;		// Pin para activar la luz de dia
const unsigned int CORE_BUZZER_PIN = 52;		// Alarma

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

const int ALARM_TONE = 440;				// Tono de la alarma
const int ALARM_TONE_ON = 500;			// Duracion del tono
const int ALARM_TONE_OFF = 50;			// Pausa entre tonos (ticks de ejecucion)
const int ALARM_BLINK_SPEED = 10;		// Velocidad del parpadeo en ticks;

const long int SENSOR_ERROR_TIMEOUT = 100;		// Time out del sensor para la alarma en ticks de ejecucion



/*** lcd.h ***/
// Pines de conexion de la pantalla
const unsigned int LCD_PIN_RS = 7; 
const unsigned int LCD_PIN_ENABLE = 8;
const unsigned int LCD_PIN_D4 = 9;
const unsigned int LCD_PIN_D5 = 10;
const unsigned int LCD_PIN_D6 = 11;
const unsigned int LCD_PIN_D7 = 12;
// Parametros de la pantalla
const unsigned int LCD_ROWS = 2;
const unsigned int LCD_COLUMNS = 16;
// Crea el objeto estatico de la libreria
static LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);



/*** dht.h ***/
const unsigned int DHT_PIN_INPUT = 50;
const long int DHT_FREQ_DIVIDER = CORE_FREQ_DIVIDER;			// Base de division de tiempo
const long int DHT_UPDATE_FREQ = 150;							// Frecuencia de actualizacion del sensor



#endif