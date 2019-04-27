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
	
	Real Time Clock

*******************************************************************************/



#ifndef __NGN_RTC_H
#define __NGN_RTC_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Modulos
#include "libs/DS3231.h"



/*** Definicion de la clase ***/
class NGN_Rtc {
	
	public:
	
		// Constructor
		NGN_Rtc();
		
		// Destructor
		~NGN_Rtc();
		
		// Metodos
		void Start();		// Inicia el sensor
		void Read();		// Lee la fecha y hora actuales
		
		// Propiedades
		int hour;			// Hora
		int minute;
		int second;
		
		int day;			// Fecha
		int month;
		int year;

	
	private:
	
		// Objeto de la libreria RTC
		DS3231 clock;
		RTCDateTime dt;
	
};



#endif