/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Control del display LCD

*******************************************************************************/



#ifndef __LCD_H
#define __LCD_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Proyecto
#include "defines.h"



/*** Definicion de la clase ***/
class Lcd {
		
	public:
	
		// Constructor
		Lcd();
		
		// Destructor
		~Lcd();
		
		// Inicializa la clase
		void Start();
		
		// Imprime un texto
		void Print(String txt);
		void Print(unsigned int x, unsigned int y, String txt);
		void PrintChar(unsigned int x, unsigned int y, byte b);
		
		// Borra la pantalla
		void Cls();
		void Cls(unsigned int x, unsigned int y, unsigned int length);
		
		// Añade un caracter personalizado
		void AddChar(int id, byte character[]);

		
	private:
		

		
};



#endif