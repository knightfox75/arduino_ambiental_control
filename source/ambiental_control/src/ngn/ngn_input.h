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
	
	Metodos de entrada

*******************************************************************************/



#ifndef __NGN_INPUT_H
#define __NGN_INPUT_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// N'gine
#include "ngn_settings.h"



/*******************************************************************************

	Clase de los metodos de entrada

*******************************************************************************/

/*** Definicion de la clase ***/
class NGN_Input {
	
	private:
	

	
	
	public:
	
		// Constructor
		NGN_Input();
		
		// Destructor
		~NGN_Input();
		
		// Metodos de configuracion
		void Start(unsigned int number_of_keys);					// Inicia la libreria
		void KeyAssign(unsigned int key_slot, unsigned int pin);	// Registra una tecla
		
		// Metodos de lectura
		void Read();						// Lee el estado de las teclas
		bool KeyHeld(unsigned int id);		// Devuelve el estado HELD
		bool KeyDown(unsigned int id);		// Devuelve el estado DOWN
		bool KeyUp(unsigned int id);		// Devuelve el estado UP
	
	private:
	
		const static int _PIN = 0;
		const static int _HELD = 1;
		const static int _UP = 2;
		const static int _DOWN = 3;
		const static int _LAST = 4;
		const static int SIZE_OF_KEY = 5;		// Area de memoria de cada tecla
		
		byte* key;					// Puntero a las teclas
		unsigned int key_num;		// Numero de teclas
	
};



#endif