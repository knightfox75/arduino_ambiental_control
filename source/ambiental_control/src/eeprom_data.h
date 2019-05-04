/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com

	Control ambiental se distribuye bajo la licencia CREATIVE COMMONS
	"Attribution-NonCommercial 4.0 International"
	https://creativecommons.org/licenses/by-nc/4.0/
	
	Gestion de datos en la EEPROM

*******************************************************************************/



#ifndef __EEPROM_DATA_H
#define __EEPROM_DATA_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
#include <EEPROM.h>
// Proyecto
#include "defines.h"




/*** Definicion de la clase ***/
class EepromData {
	
	public:
	
		// Constructor
		EepromData();
		
		// Destructor
		~EepromData();
				
		// Carga los datos desde la EEPROM
		Eeprom_d Load();
		
		// Guarda los datos en la EEPROM
		void Save(Eeprom_d data);
		
		// Compara dos estructuras de datos
		bool Compare(Eeprom_d data_a, Eeprom_d data_b);
		

	private:
	
		// Lectura de datos en la EEPROM
		Eeprom_d Read();
		
		// Escritura de datos
		void Write(Eeprom_d data);
		
		// Valores por defecto
		Eeprom_d DefaultValues();
		
		// Vacia la EEPROM
		void EraseEeprom();
		
		// Checksum
		unsigned long int CheckSum(Eeprom_d data);
	
};



#endif