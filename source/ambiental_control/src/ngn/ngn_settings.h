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




/*** Configuracion de la clase NGN_Lcd (ngn_lcd.h) ***/
// Pines de conexion de la pantalla
const unsigned int LCD_PIN_RS = 22; 
const unsigned int LCD_PIN_ENABLE = 24;
const unsigned int LCD_PIN_D4 = 26;
const unsigned int LCD_PIN_D5 = 28;
const unsigned int LCD_PIN_D6 = 30;
const unsigned int LCD_PIN_D7 = 32;
// Parametros de la pantalla
const unsigned int LCD_ROWS = 2;
const unsigned int LCD_COLUMNS = 16;



/*** Configuracion de la clase NGN_Dht (ngn_dht.h) ***/
// Parametros del sensor
const long int DHT_FREQ_DIVIDER = 10;	// Base de division de tiempo
const long int DHT_UPDATE_FREQ = 150;	// Frecuencia de actualizacion del sensor



/*** Configuracion de la clase NGN_Input (ngn_input.h) ***/
const unsigned int INPUT_MAX_KEY_SLOTS = 128;	// Maximo numero de teclas
const unsigned int INPUT_MAX_PIN_ID = 53;		// Ultimo PIN asignable



#endif
