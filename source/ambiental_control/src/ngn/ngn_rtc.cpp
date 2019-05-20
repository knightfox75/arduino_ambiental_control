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



/*** Includes ***/
// Includes de N'gine
#include "ngn_rtc.h"



/*** Constructor ***/
NGN_Rtc::NGN_Rtc() {
}



/*** Destructor ***/
NGN_Rtc::~NGN_Rtc() {
}



/*** Inicia el sensor ***/
void NGN_Rtc::Start() {
	
	// Hora y fecha a 0
	hour = 0;
	minute = 0;
	second = 0;
	year = 0;
	month = 0;
	day = 0;
	day_of_week = 0;
	
	// Inicia el interfaz I2C 
	Wire.begin();
	
	// Reloj en modo 24H
	ds3231.setClockMode(false);
	
	// Actualiza los valores
	Read();
	
}



/*** Lee la hora y fecha actual ***/
void NGN_Rtc::Read() {
	
	// Lee los datos en RAW
	dt = clock.now();
	
	// Asigna los valores
	second = (S8)dt.second();
	minute = (S8)dt.minute();
	hour = (S8)dt.hour();
	day_of_week = (S8)ds3231.getDoW();
	day = (S8)dt.day();
	month = (S8)dt.month();
	year = (S16)dt.year();
	
}



/*** Guarda los valores actuales en el modulo RTC ***/
void NGN_Rtc::Save() {
	
	// Almacena los valores
	ds3231.setYear(year - 2000);
	ds3231.setMonth(month);
	ds3231.setDate(day);
	ds3231.setDoW(day_of_week);
	ds3231.setHour(hour);
	ds3231.setMinute(minute);
	ds3231.setSecond(second);
	
}



/*** Apaga la alarma ***/
void NGN_Rtc::AlarmOff(U8 alarm) {
	
	ds3231.turnOffAlarm(alarm);
	
}
