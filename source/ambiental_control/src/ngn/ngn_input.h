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
#include "ngn_defines.h"		// Definiciones propietarias
#include "ngn_settings.h"		// Parametros de la configuracion



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
		void Start(U8 number_of_keys);					// Inicia la libreria
		void KeyAssign(U8 key_slot, U8 pin);			// Registra una tecla
		
		// Metodos de lectura
		void Read();						// Lee el estado de las teclas
		bool KeyHeld(U8 id);		// Devuelve el estado HELD
		bool KeyDown(U8 id);		// Devuelve el estado DOWN
		bool KeyUp(U8 id);			// Devuelve el estado UP
	
	private:
	
		const static U8 _PIN = 0;
		const static U8 _HELD = 1;
		const static U8 _UP = 2;
		const static U8 _DOWN = 3;
		const static U8 _LAST = 4;
		const static U8 SIZE_OF_KEY = 5;		// Area de memoria de cada tecla
		
		U8* key;					// Puntero a las teclas
		U8 key_num;					// Numero de teclas
	
};



#endif