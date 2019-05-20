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
		S16 Run();
		
		// Opten los datos actualizados desde el menu
		Eeprom_d GetData();
		
	
	private:
	
		// Parametros de trabajo
		EepromData eeprom;
		Eeprom_d data, old_data;
		
		// Lectura del teclado
		bool kb_up, kb_down, kb_fwd, kb_back;
		void Keyboard();
		U16 auto_key_delay;					// Temporizador de la autorepeticion
		U16 auto_key_repeat;
		U16 held_time;						// Temporizacion de la autosuma
		
		// Menu principal
		S16 MenuMain();
		
		// Menu de temperatura
		S16 MenuTemperature();
		// Menu de humedad
		S16 MenuHumidity();
		// Menu de la lampara de luz diurna
		S16 MenuSunLight();
		// Menu de configuracion de fecha y hora
		S16 MenuDateTime();
		// Menu de configuracion del sistema
		S16 MenuSystem();
		
		// Cambia el valor de un parametro
		S16 SetValue(S16 &value, S16 min_val, S16 max_val, U8 unit, U8 width);
		static const U8 UNIT_NONE = 255;
		static const U8 UNIT_GRADES = 1;
		static const U8 UNIT_PERCENT = 2;
		static const U8 UNIT_SECONDS = 3;
		static const U8 UNIT_MINUTES = 4;
		static const U8 UNIT_HOURS = 5;
		
		// Maquina de estados
		S16 st, next_st;								// Control del menu
		
		// Opciones del menu principal
		static const S16 MENU_ST_MAIN = 1;				// Menu principal
		static const S16 MENU_ST_TEMPERATURE = 2;		// Submenus
		static const S16 MENU_ST_HUMIDITY = 3;
		static const S16 MENU_ST_SUNLIGHT = 4;
		static const S16 MENU_ST_DATETIME = 5;
		static const S16 MENU_ST_SYSTEM = 6;
		
		// Opciones de el menu "Temperatura"
		static const S16 TEMPERATURE_ST_MIN = 101;
		static const S16 TEMPERATURE_ST_MAX = 102;
		static const S16 TEMPERATURE_ST_LOWALARM = 103;
		static const S16 TEMPERATURE_ST_HIALARM = 104;
		
		// Opciones de el menu "Humedad"
		static const S16 HUMIDITY_ST_MIN = 201;
		static const S16 HUMIDITY_ST_MAX = 202;
		static const S16 HUMIDITY_ST_LOWALARM = 203;
		static const S16 HUMIDITY_ST_HIALARM = 204;
		static const S16 HUMIDITY_ST_ONTIME = 205;
		static const S16 HUMIDITY_ST_OFFTIME = 206;
		
		// Opciones de el menu "Luz diurna"
		static const S16 SUNLIGHT_ST_RISE_H = 301;
		static const S16 SUNLIGHT_ST_RISE_M = 302;
		static const S16 SUNLIGHT_ST_SET_H = 303;
		static const S16 SUNLIGHT_ST_SET_M = 304;
		
		// Opciones de el menu "Fecha y hora"
		static const S16 DATETIME_ST_SECOND = 401;
		static const S16 DATETIME_ST_MINUTE = 402;
		static const S16 DATETIME_ST_HOUR = 403;
		static const S16 DATETIME_ST_DAY = 404;
		static const S16 DATETIME_ST_MONTH = 405;
		static const S16 DATETIME_ST_YEAR = 406;

		// Parametros comunes a todos los menus
		static const S16 MENU_OP_EXIT = 0x7FFF;
		const U16 AUTO_KEY_DELAY = 20;				// 20 ticks, 1s
		const U16 AUTO_KEY_REPEAT = 2;				// 2 ticks, 0.1s
		const String CURSOR_CHAR = ">";				// Caracter para el cursor
		
		// Variables adicionales de control
		S16 temp_value, param_value;
		
		// Menu principal
		S16 main_menu_op, main_menu_op_last;				// Control de opciones
		static const S16 MAIN_MENU_OPTIONS = 5;				// Numero de opciones
		const String main_menu_text[MAIN_MENU_OPTIONS] = {
			"Temperature",
			"Humidity",
			"Sun Light",
			"Date & Time",
			"System"
		};
		static const S16 MAIN_MENU_OP_TEMPERATURE = 0;
		static const S16 MAIN_MENU_OP_HUMIDITY = 1;
		static const S16 MAIN_MENU_OP_SUNLIGHT = 2;
		static const S16 MAIN_MENU_OP_DATETIME = 3;
		static const S16 MAIN_MENU_OP_SYSTEM = 4;
		
		
		// Menu de configuracion de la temperatura
		S16 temperature_menu_op, temperature_menu_op_last;		// Control de opciones
		static const S16 TEMPERATURE_MENU_OPTIONS = 4;
		const String temperature_menu_text[TEMPERATURE_MENU_OPTIONS] = {
			"Min",
			"Max",
			"Low Alarm",
			"Hi Alarm"
		};
		static const S16 TEMPERATURE_MENU_OP_MIN = 0;
		static const S16 TEMPERATURE_MENU_OP_MAX = 1;
		static const S16 TEMPERATURE_MENU_OP_LOWALARM = 2;
		static const S16 TEMPERATURE_MENU_OP_HIALARM = 3;
		
		// Menu de configuracion de la humedad relativa
		S16 humidity_menu_op, humidity_menu_op_last;		// Control de opciones
		static const S16 HUMIDITY_MENU_OPTIONS = 6;
		const String humidity_menu_text[HUMIDITY_MENU_OPTIONS] = {
			"Min",
			"Max",
			"Low Alarm",
			"Hi Alarm",
			"ON Time",
			"OFF Time"
		};
		static const S16 HUMIDITY_MENU_OP_MIN = 0;
		static const S16 HUMIDITY_MENU_OP_MAX = 1;
		static const S16 HUMIDITY_MENU_OP_LOWALARM = 2;
		static const S16 HUMIDITY_MENU_OP_HIALARM = 3;
		static const S16 HUMIDITY_MENU_OP_ONTIME = 4;
		static const S16 HUMIDITY_MENU_OP_OFFTIME = 5;
		
		// Menu de configuracion de la luz diurna
		S16 sunlight_menu_op, sunlight_menu_op_last;		// Control de opciones
		static const S16 SUNLIGHT_MENU_OPTIONS = 4;
		const String sunlight_menu_text[SUNLIGHT_MENU_OPTIONS] = {
			"Sunrise",
			"Sunrise",
			"Sunset",
			"Sunset"
		};
		static const S16 SUNLIGHT_MENU_OP_RISE_H = 0;
		static const S16 SUNLIGHT_MENU_OP_RISE_M = 1;
		static const S16 SUNLIGHT_MENU_OP_SET_H = 2;
		static const S16 SUNLIGHT_MENU_OP_SET_M = 3;
		
		// Menu de configuracion de la fecha y hora
		S16 datetime_menu_op, datetime_menu_op_last;		// Control de opciones
		static const S16 DATETIME_MENU_OPTIONS = 6;
		const String datetime_menu_text[DATETIME_MENU_OPTIONS] = {
			"Second",
			"Minute",
			"Hour",
			"Day",
			"Month",
			"Year"
		};
		static const S16 DATETIME_MENU_OP_SECOND = 0;
		static const S16 DATETIME_MENU_OP_MINUTE = 1;
		static const S16 DATETIME_MENU_OP_HOUR = 2;
		static const S16 DATETIME_MENU_OP_DAY = 3;
		static const S16 DATETIME_MENU_OP_MONTH = 4;
		static const S16 DATETIME_MENU_OP_YEAR = 5;
		
		// Convierte Tics a Segundos y viceversa
		const U16 BASE = (1000 / CORE_FREQ_DIVIDER);
		const U16 TICK = CORE_MAIN_UPDATE_FREQ;
		U16 Ticks2Seconds(U32 ticks);
		U32 Seconds2Ticks(U16 seconds);
		
		// Marca de tiempo
		struct {
			S8 second;
			S8 minute;
			S8 hour;
			S8 day;
			S8 month;
			S16 year;
		} time_snap;
		
		void ReadDateTime();
		void SaveDateTime();
					
};



#endif