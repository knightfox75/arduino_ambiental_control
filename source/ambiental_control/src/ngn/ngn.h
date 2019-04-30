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
// N'gine (Metodos propios)
#include "ngn_input.h"
#include "ngn_string.h"
// N'gine (Acceso a modulos de hardware)
#include "ngn_dht.h"
#include "ngn_lcd.h"
#include "ngn_rtc.h"



/*** Declaracion de la clase ***/
class NGN {
	
	public:
	
		// Contructor
		NGN();
		
		// Destructor
		~NGN();
		
		// Modulos de la libreria
		NGN_Input input;			// Metodos de entrada
		NGN_String string;			// Manipulacion de cadenas de texto
		// Modulos de harware
		NGN_Lcd lcd;				// Display LCD
		NGN_Rtc rtc;				// Reloj de tiempo real
		NGN_Dht dht;				// Sensor de temperatura y humedad relativa
	
	private:
	
};



/*** Singleton de la clase ***/
extern NGN ngn;



#endif
