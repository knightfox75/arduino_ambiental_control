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
	
	Archivo principal de la libreria

*******************************************************************************/



#ifndef __NGN_H
#define __NGN_H



/*** Includes ***/

// Arduino
#include <Arduino.h>

// N'gine
#include "ngn_defines.h"		// Definiciones propietarias
#include "ngn_settings.h"		// Parametros de la configuracion
#include "ngn_string.h"

// N'gine (Acceso a modulos de hardware)
#if NGN_INPUT_ENABLE == true
	#include "ngn_input.h"
#endif

#if NGN_DHT_ENABLE == true
	#include "ngn_dht.h"
#endif

#if NGN_LCD_ENABLE == true
	#include "ngn_lcd.h"
#endif

#if NGN_RTC_ENABLE == true
	#include "ngn_rtc.h"
#endif



/*** Declaracion de la clase ***/
class NGN {
	
	public:
	
		// Contructor
		NGN();
		
		// Destructor
		~NGN();
		
		/*** Modulos de la libreria ***/
		// Manipulacion de cadenas de texto
		NGN_String string;
		
		/*** Modulos de harware ***/
		// Metodos de entrada
		#if NGN_INPUT_ENABLE == true
			NGN_Input input;
		#endif
		// Display LCD
		#if NGN_LCD_ENABLE == true
			NGN_Lcd lcd;
		#endif
		// Reloj de tiempo real
		#if NGN_RTC_ENABLE == true
			NGN_Rtc rtc;
		#endif
		// Sensor de temperatura y humedad relativa
		#if NGN_DHT_ENABLE == true
			NGN_Dht dht;
		#endif
	
	private:
	
};



/*** Singleton de la clase ***/
extern NGN ngn;



#endif
