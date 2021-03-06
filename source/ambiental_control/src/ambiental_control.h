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
	
	Monitorizacion de los sensores y activacion de los actuadores

*******************************************************************************/



#ifndef __AMBIENTAL_CONTROL_H
#define __AMBIENTAL_CONTROL_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// N'gine
#include "ngn/ngn.h"
// Proyecto
#include "defines.h"



/*** Declaracion de la clase ***/
class AmbientalControl {
	
	public:
	
		// Constructor de la clase
		AmbientalControl();
		
		// Destructor de la clase
		~AmbientalControl();
		
		// Incia la clase
		void Start(Eeprom_d _data);
		
		// Ejecucion
		void Run();
		
		// Muestra la informacion en pantalla
		void DisplayData();
		
		// Fuerza el refresco de la pantalla en el proximo ciclo y actualiza los datos de referencia
		void UpdateData(Eeprom_d _data);
	
	
	private:
			
		// Parametros de trabajo
		Eeprom_d data;
		
		// Muestra los datos ambientales
		void DisplayAmbientalData();
		bool ambiental_text_data;
		bool ambiental_text_error;
		S8 _temperature;
		S8 _humidity;
		
		// Muestra la fecha y la hora
		void DisplayTime();
		S8 _hour;
		S8 _minute;
		S8 _second;
		bool dot2;
		
		// Muestra los datos de las salidas
		void DisplayOutputState();
		
		// Control del sensor ambiental
		void AmbientalSensorControl();
		bool temperature_alarm;
		bool humidity_alarm;
		bool water_tank_alarm;
		bool sensor_alarm;
		U16 sensor_error_count;
		
		// Control de la temperatura
		void TemperatureControl();
		bool temp_too_high;
		bool temp_too_low;
		bool heater_active;
		
		// Control de la humedad
		void HumidityControl();
		bool humi_too_high;
		bool humi_too_low;
		bool humidifier_active;
		bool humidifier_on;
		U16 humidifier_counter;
		U8 tank_level;
		static const U8 TANK_LV_EMPTY = 0;
		static const U8 TANK_LV_HALF = 1;
		static const U8 TANK_LV_FULL = 2;
		U8 tank_char;
		
		// Control horario, salida y puesta del sol
		void DayLightControl();
		U16 sunrise_time;
		U16 sunset_time;
		bool daylight_active;
		
		// Alarmas
		void Alarm();
		bool alarm_on;
		U16 alarm_repeat_count;
		bool alarm_blink;
		U16 alarm_blink_count;
	
};




#endif