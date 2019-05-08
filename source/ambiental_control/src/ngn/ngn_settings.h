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
	
	Archivo de configuracion de la libreria

*******************************************************************************/



#ifndef __NGN_SETTINGS_H
#define __NGN_SETTINGS_H



/*** Includes ***/
// N'gine
#include "ngn_defines.h"		// Definiciones propietarias



/*** Configuracion de la clase NGN_Dht (ngn_dht.h) ***/
// Activacion del modulo
#define NGN_DHT_ENABLE true
// Configuracion del modulo
#if NGN_DHT_ENABLE == true
	// Configuracion del sensor
	const U8 DHT_PIN = 50;					// Pin de datos del sensor
	const U8 DHT_TYPE = 11;					// Tipo de sensor (DHTxx: 11, 12, 21, 22)
	// Parametros del sensor
	const U8 DHT_FREQ_DIVIDER = 10;			// Base de division de tiempo
	const U16 DHT_UPDATE_FREQ = 300;		// Frecuencia de actualizacion del sensor
#endif



/*** Configuracion de la clase NGN_Input (ngn_input.h) ***/
// Activacion del modulo
#define NGN_INPUT_ENABLE true
// Configuracion del modulo
#if NGN_INPUT_ENABLE == true
	const U8 INPUT_MAX_KEY_SLOTS = 64;		// Maximo numero de teclas
	const U8 INPUT_MAX_PIN_ID = 53;			// Ultimo PIN asignable
#endif



/*** Configuracion de la clase NGN_Lcd (ngn_lcd.h) ***/
// Activacion del modulo
#define NGN_LCD_ENABLE true
// Configuracion del modulo
#if NGN_LCD_ENABLE == true
	// Pines de conexion de la pantalla
	const U8 LCD_PIN_RS = 22; 
	const U8 LCD_PIN_ENABLE = 24;
	const U8 LCD_PIN_D4 = 26;
	const U8 LCD_PIN_D5 = 28;
	const U8 LCD_PIN_D6 = 30;
	const U8 LCD_PIN_D7 = 32;
	// Parametros de la pantalla
	const U8 LCD_ROWS = 2;
	const U8 LCD_COLUMNS = 16;
#endif


/*** Configuracion de la clase NGN_Rtc (ngn_rtc.h) ***/
// Activacion del modulo
#define NGN_RTC_ENABLE true
// Configuracion del modulo
#if NGN_RTC_ENABLE == true
#endif



#endif
