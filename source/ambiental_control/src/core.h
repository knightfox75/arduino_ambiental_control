/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Nucleo de Ejecucion

*******************************************************************************/



#ifndef __CORE_H
#define __CORE_H



/*** Includes ***/
// Arduino
#include <Arduino.h>
// Proyecto
#include "defines.h"
#include "lcd.h"
#include "dht.h"
#include "rtc.h"


/*** Definicion de la clase ***/
class Core {
	
	public:
	
		// Constructor
		Core();
		
		// Destructor
		~Core();
		
		// Al iniciar el programa
		void Start();
		
		// Ejecuta regularmente
		void Update();
		
	
	private:
	
		// Variables de control
		bool _led_blink;			// Control del blink del led
		bool _update;				// Control de ejecucion del programa
		
		// Objetos adicionales de codigo
		Lcd lcd;
		Dht dht;
		Rtc rtc;
		
		// Funciones privadas
		void Logic();		// Logica del programa
		void Common();		// Metodos comunes a todos los estados
		
		// Muestra los datos ambientales
		void DisplayAmbientalData();
		bool ambiental_text_data;
		bool ambiental_text_error;
		int _temperature;
		int _humidity;
		
		// Muestra la fecha y la hora
		void DisplayTime();
		int _hour;
		int _minute;
		int _second;
		bool dot2;
		
		// Muestra los datos de las salidas
		void DisplayOutputState();
		
		// Control del sensor ambiental
		void AmbientalSensorControl();
		bool temperature_alarm;
		bool humidity_alarm;
		bool sensor_alarm;
		long int sensor_error_count;
		
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
		
		// Control horario, salida y puesta del sol
		void DayLightControl();
		int sunrise_time;
		int sunset_time;
		bool daylight_active;
		
		// Alarmas
		void Alarm();
		bool alarm_on;
		int alarm_repeat_count;
		bool alarm_blink;
		int alarm_blink_count;
		
		// Caracteres personalizados
		byte char_off[8] = {
			B00000000,
			B00000000,
			B00000100,
			B00001110,
			B00001110,
			B00000100,
			B00000000,
			B00000000
		};
		byte char_heater_on[8] = {
			B00000100,
			B00010101,
			B00010101,
			B00011011,
			B00010001,
			B00010001,
			B00010001,
			B00001110
		};
		byte char_humidifier_on[8] = {
			B00000100,
			B00001110,
			B00001110,
			B00011111,
			B00011111,
			B00011101,
			B00011111,
			B00001110
		};
		byte char_daylight_on[8] = {
			B00000000,
			B00010101,
			B00001110,
			B00011011,
			B00001110,
			B00010101,
			B00000000,
			B00011111
		};
		byte char_arrow_down[8] = {
			B00000100,
			B00000100,
			B00000100,
			B00000100,
			B00000100,
			B00011111,
			B00001110,
			B00000100
		};
		byte char_arrow_up[8] = {
			B00000100,
			B00001110,
			B00011111,
			B00000100,
			B00000100,
			B00000100,
			B00000100,
			B00000100
		};
		

};



#endif