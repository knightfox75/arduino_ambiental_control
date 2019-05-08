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
	
	Manipulacion de cadenas de texto

*******************************************************************************/



#ifndef __NGN_STRING_H
#define __NGN_STRING_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// N'gine
#include "ngn_defines.h"		// Definiciones propietarias
#include "ngn_settings.h"		// Parametros de la configuracion



/*** Definicion de la clase ***/
class NGN_String {
	
	public:
	
		// Constructor
		NGN_String();
		
		// Destructor
		~NGN_String();
		
		// Convierte un numero Entero a String
		String Int2String(S32 number);
		String Int2String(S32 number, U8 min_width);

		
	
	private:
	
};



#endif