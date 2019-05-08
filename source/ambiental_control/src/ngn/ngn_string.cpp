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



/*** Includes ***/
// Includes de N'gine
#include "ngn_string.h"



/*** Constructor ***/
NGN_String::NGN_String() {
}



/*** Destructor ***/
NGN_String::~NGN_String() {
}



/*** Convierte un numero entero a cadena de texto (primera sobrecarga) ***/
String NGN_String::Int2String(S32 number) {
	
	return String(number);
	
}



/*** Convierte un numero entero a cadena de texto (segunda sobrecarga) ***/
String NGN_String::Int2String(S32 number, U8 min_width) {
	
	// Si se ha especificado solo 1 digito, conversion directa
	if (min_width <= 1) return String(number);
	
	// Variables de control
	String text = "";
	U8 digits = min_width;
	S32 value = 0;
	
	// Si se trata de un numero negativo...
	if (number < 0) {
		text += "-";
		value = abs(number);
		digits --;
	} else {
		value = number;
	}
	
	// Añade el numero de ceros necesarios
	for (U8 i = 1; i < digits; i ++) {
		if (value < pow(10, i)) text += "0";
	}
	
	// Añadele el numero convertido
	text += String(value);
	
	// Devuelve el resultado
	return text;
	
}
