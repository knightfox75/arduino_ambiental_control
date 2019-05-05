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
	
	Menu de opciones

*******************************************************************************/



#ifndef __MENU_H
#define __MENU_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// N'gine
#include "ngn/ngn.h"
// Proyecto
#include "defines.h"
#include "eeprom_data.h"



/*** Definicion de la clase ***/
class Menu {
	
	public:
	
		// Constructor
		Menu();
		
		// Destructor
		~Menu();
		
		// Incia la clase
		void Start(Eeprom_d _data);
		
		// Ejecucion
		int Run();
		
		// Opten los datos actualizados desde el menu
		Eeprom_d GetData();
		
	
	private:
	
		// Parametros de trabajo
		EepromData eeprom;
		Eeprom_d data, old_data;
		
		// Lectura del teclado
		bool kb_up, kb_down, kb_fwd, kb_back;
		void Keyboard();
		int auto_key_delay;					// Temporizador de la autorepeticion
		int auto_key_repeat;
		long unsigned int held_time;		// Temporizacion de la autosuma
		
		// Menu principal
		int MenuMain();
		
		// Menu de temperatura
		int MenuTemperature();
		// Menu de humedad
		int MenuHumidity();
		// Menu de la lampara de luz diurna
		int MenuSunLight();
		// Menu de configuracion de fecha y hora
		int MenuDateTime();
		// Menu de configuracion del sistema
		int MenuSystem();
		
		// Cambia el valor de un parametro
		int SetValue(int &value, int min_val, int max_val, byte unit, byte width);
		static const byte UNIT_GRADES = 1;
		static const byte UNIT_PERCENT = 2;
		static const byte UNIT_SECONDS = 3;
		
		// Maquina de estados
		int st, next_st;								// Control del menu
		
		// Opciones del menu principal
		static const int MENU_ST_MAIN = 1;				// Menu principal
		static const int MENU_ST_TEMPERATURE = 2;		// Submenus
		static const int MENU_ST_HUMIDITY = 3;
		static const int MENU_ST_SUNLIGHT = 4;
		static const int MENU_ST_DATETIME = 5;
		static const int MENU_ST_SYSTEM = 6;
		
		// Opciones de el menu "Temperatura"
		static const int TEMPERATURE_ST_MIN = 101;
		static const int TEMPERATURE_ST_MAX = 102;
		static const int TEMPERATURE_ST_LOWALARM = 103;
		static const int TEMPERATURE_ST_HIALARM = 104;
		
		// Opciones de el menu "Humedad"
		static const int HUMIDITY_ST_MIN = 201;
		static const int HUMIDITY_ST_MAX = 202;
		static const int HUMIDITY_ST_LOWALARM = 203;
		static const int HUMIDITY_ST_HIALARM = 204;
		static const int HUMIDITY_ST_ONTIME = 205;
		static const int HUMIDITY_ST_OFFTIME = 206;
		
		// Parametros comunes a todos los menus
		static const int MENU_OP_EXIT = 0x7FFF;
		const int AUTO_KEY_DELAY = 20;				// 20 ticks, 1s
		const int AUTO_KEY_REPEAT = 2;				// 2 ticks, 0.1s
		const String CURSOR_CHAR = ">";				// Caracter para el cursor
		
		// Variables adicionales de control
		int temp_value, param_value;
		
		// Menu principal
		int main_menu_op, main_menu_op_last;				// Control de opciones
		static const int MAIN_MENU_OPTIONS = 5;				// Numero de opciones
		const String main_menu_text[MAIN_MENU_OPTIONS] = {
			"Temperature",
			"Humidity",
			"Sun Light",
			"Date & Time",
			"System"
		};
		static const int MAIN_MENU_OP_TEMPERATURE = 0;
		static const int MAIN_MENU_OP_HUMIDITY = 1;
		static const int MAIN_MENU_OP_SUNLIGHT = 2;
		static const int MAIN_MENU_OP_DATETIME = 3;
		static const int MAIN_MENU_OP_SYSTEM = 4;
		
		
		// Menu de configuracion de la temperatura
		int temperature_menu_op, temperature_menu_op_last;		// Control de opciones
		static const int TEMPERATURE_MENU_OPTIONS = 4;
		const String temperature_menu_text[TEMPERATURE_MENU_OPTIONS] = {
			"Min",
			"Max",
			"Low Alarm",
			"Hi Alarm"
		};
		static const int TEMPERATURE_MENU_OP_MIN = 0;
		static const int TEMPERATURE_MENU_OP_MAX = 1;
		static const int TEMPERATURE_MENU_OP_LOWALARM = 2;
		static const int TEMPERATURE_MENU_OP_HIALARM = 3;
		
		// Menu de configuracion de la humedad relativa
		int humidity_menu_op, humidity_menu_op_last;		// Control de opciones
		static const int HUMIDITY_MENU_OPTIONS = 6;
		const String humidity_menu_text[HUMIDITY_MENU_OPTIONS] = {
			"Min",
			"Max",
			"Low Alarm",
			"Hi Alarm",
			"ON Time",
			"OFF Time"
		};
		static const int HUMIDITY_MENU_OP_MIN = 0;
		static const int HUMIDITY_MENU_OP_MAX = 1;
		static const int HUMIDITY_MENU_OP_LOWALARM = 2;
		static const int HUMIDITY_MENU_OP_HIALARM = 3;
		static const int HUMIDITY_MENU_OP_ONTIME = 4;
		static const int HUMIDITY_MENU_OP_OFFTIME = 5;
		
		
		// Convierte Tics a Segundos y viceversa
		const unsigned int BASE = (1000 / CORE_FREQ_DIVIDER);
		const unsigned int TICK = CORE_MAIN_UPDATE_FREQ;
		unsigned int Ticks2Seconds(unsigned long int ticks);
		unsigned long int Seconds2Ticks(unsigned int seconds);
		
					
};



#endif