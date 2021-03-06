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
	
	Control del display LCD

*******************************************************************************/



#ifndef __NGN_LCD_H
#define __NGN_LCD_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
#include <LiquidCrystal.h>			// Display LCD
// N'gine
#include "ngn_defines.h"		// Definiciones propietarias
#include "ngn_settings.h"		// Parametros de la configuracion



/*** Constantes y estaticas ***/
// Objeto estatico de la clase
static LiquidCrystal display(
						LCD_PIN_RS,
						LCD_PIN_ENABLE,
						LCD_PIN_D4,
						LCD_PIN_D5,
						LCD_PIN_D6,
						LCD_PIN_D7
						);



/*** Definicion de la clase ***/
class NGN_Lcd {
		
	public:
	
		// Constructor
		NGN_Lcd();
		
		// Destructor
		~NGN_Lcd();
		
		// Inicializa la clase
		void Start();
		
		// Imprime un texto
		void Print(String txt);
		void Print(U8 x, U8 y, String txt);
		void PrintChar(U8 x, U8 y, U8 b);
		
		// Borra la pantalla
		void Cls();
		void Cls(U8 x, U8 y, U8 length);
		
		// Añade un caracter personalizado
		void AddChar(U8 id, const U8* character);

		
	private:
	
		
		
};



#endif