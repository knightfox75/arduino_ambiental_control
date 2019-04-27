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



/*** Includes ***/
// Includes de N'gine
#include "ngn_input.h"




/*******************************************************************************

	Clase de los metodos de entrada

*******************************************************************************/

/*** Constructor ***/
NGN_Input::NGN_Input() {	

	key = NULL;		// Puntero a null
	key_num = 0;	// Ninguna tecla asignada
	
}



/*** Destructor ***/
NGN_Input::~NGN_Input() {
	
	free(key);
	
}



/*** Inicia la clase ***/
void NGN_Input::Start(unsigned int number_of_keys) {
	
	// Si el numero de teclas es menor a 1, sal
	if ((number_of_keys < 1) || (number_of_keys >= INPUT_MAX_KEY_SLOTS)) return;
	
	if (key_num != 0) {
		free(key);
		key = NULL;
	}
	
	// Asigna el espacio
	key = (byte*)calloc(number_of_keys, (sizeof(byte) * SIZE_OF_KEY));
	if (!key) return;
	
	// Guarda el numero de teclas creadas
	key_num = number_of_keys;
	
	// Inicia el espacio de memoria
	for (unsigned int i = 0; i < key_num; i ++) {
		int p = (i * SIZE_OF_KEY);
		key[(p + _PIN)] = 0xFF;
		key[(p + _HELD)] = 0x00;
		key[(p + _UP)] = 0x00;
		key[(p + _DOWN)] = 0x00;
		key[(p + _LAST)] = 0x00;
	}
	
	
}



/*** Registra una tecla ***/
void NGN_Input::KeyAssign(unsigned int key_slot, unsigned int pin) {
	
	// Proteccion de desborde
	if (key_slot >= key_num) return;
	if (pin > INPUT_MAX_PIN_ID) return;
	
	// Configura el pin en modo Lectura
	pinMode(pin, INPUT);
	
	// Guarda los parametros de la tecla
	key[((key_slot * SIZE_OF_KEY) + _PIN)] = pin;
	
}



/*** Actualiza el estado de las teclas ***/
void NGN_Input::Read() {
	
	unsigned int p = 0;
	
	// Lee todas las teclas
	for (unsigned int i = 0; i < key_num; i ++) {
		
		// Calcula el puntero de memoria
		p = (i * SIZE_OF_KEY);
		
		// Si tiene un PIN valido asignado
		if (key[(p + _PIN)] < 128) {
			// Estados por defecto de UP y DOWN
			key[(p + _UP)] = 0x00;
			key[(p + _DOWN)] = 0x00;
			// Lee el PIN
			if (digitalRead(key[(p + _PIN)])) {
				// Tecla pulsada
				key[(p + _HELD)] = 0xFF;
				if (key[(p + _LAST)] == 0x00) key[(p + _DOWN)] = 0xFF;
			} else {
				// Tecla sin pulsar
				key[(p + _HELD)] = 0x00;
				if (key[(p + _LAST)] == 0xFF) key[(p + _UP)] = 0xFF;
			}
			// Guarda el estado
			key[(p + _LAST)] = key[(p + _HELD)];
		}
		
	}
		
}



/*** Estado HELD de la tecla ***/
bool NGN_Input::KeyHeld(unsigned int id) {
	
	if (id >= key_num) return false;
	
	if (key[((id * SIZE_OF_KEY) + _HELD)] == 0xFF) return true; else return false;
	
}



/*** Estado DOWN de la tecla ***/
bool NGN_Input::KeyDown(unsigned int id) {
	
	if (id >= key_num) return false;
	
	if (key[((id * SIZE_OF_KEY) + _DOWN)] == 0xFF) return true; else return false;
	
}



/*** Estado UP de la tecla ***/
bool NGN_Input::KeyUp(unsigned int id) {
	
	if (id >= key_num) return false;
	
	if (key[((id * SIZE_OF_KEY) + _UP)] == 0xFF) return true; else return false;
	
}
