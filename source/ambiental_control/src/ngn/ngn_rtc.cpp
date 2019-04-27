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
	
	// Inicia el modulo RTC
	clock.begin();
	
	// Fecha y horas iniciales con el tiempo de compilacion
	//clock.setDateTime(__DATE__, __TIME__);
	
	// Actualiza los valores
	Read();
	
}



/*** Lee la hora y fecha actual ***/
void NGN_Rtc::Read() {
	
	// Lee los datos en RAW
	dt = clock.getDateTime();
	
	// Asigna los valores
	second = dt.second;
	minute = dt.minute;
	hour = dt.hour;
	day = dt.day;
	month = dt.month;
	year = dt.year;
	
}