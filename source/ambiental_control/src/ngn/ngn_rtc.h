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
	
	*** Se requieren las siguientes librerias ***
	DS3231 real-time clock (RTC) : https://github.com/NorthernWidget/DS3231 

*******************************************************************************/



#ifndef __NGN_RTC_H
#define __NGN_RTC_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
#include <Wire.h>
// Arduino Libs
#include <DS3231.h>
// N'gine
#include "ngn_defines.h"		// Definiciones propietarias
#include "ngn_settings.h"		// Parametros de la configuracion



/*** Definicion de la clase ***/
class NGN_Rtc {
	
	public:
	
		// Constructor
		NGN_Rtc();
		
		// Destructor
		~NGN_Rtc();
		
		// Metodos
		void Start();					// Inicia el sensor
		void Read();					// Lee la fecha y hora actuales
		void Save();					// Guarda en el reloj los valores actuales
		void AlarmOff(U8 alarm);		// Apaga la alarma
		
		
		// Propiedades
		S8 hour;			// Hora
		S8 minute;
		S8 second;
		
		S8 day;				// Fecha
		S8 day_of_week;
		S8 month;
		S16 year;

	
	private:
	
		// Objeto de la libreria DS3231
		DS3231 ds3231;
		// Objeto de la libreria RTC
		RTClib clock;
		// Formato de fecha y hora
		DateTime dt;
	
};



#endif