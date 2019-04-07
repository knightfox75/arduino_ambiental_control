/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Real Time Clock

*******************************************************************************/



#ifndef __RTC_H
#define __RTC_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Modulos
#include "libs/DS3231.h"
// Proyecto
#include "defines.h"



/*** Definicion de la clase ***/
class Rtc {
	
	public:
	
		// Constructor
		Rtc();
		
		// Destructor
		~Rtc();
		
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