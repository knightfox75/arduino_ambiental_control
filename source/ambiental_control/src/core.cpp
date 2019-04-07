/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Nucleo de Ejecucion

*******************************************************************************/



/*** Includes ***/
// Includes del proyecto
#include "core.h"



/*** Contructor ***/
Core::Core() {
}



/*** Destructor ***/
Core::~Core() {
}



/*** Al iniciar el programa ***/
void Core::Start() {
	
	// Variables de control
	_update = false;
	_led_blink = false;
	
	// Configura el led interno
	pinMode(LED_BUILTIN, OUTPUT);
	
	// Configura el display LCD
	lcd.Start();
	// Añade los characteres personalizados
	lcd.AddChar(0, char_off);
	lcd.AddChar(1, char_heater_on);
	lcd.AddChar(2, char_humidifier_on);
	lcd.AddChar(3, char_daylight_on);
	lcd.AddChar(4, char_arrow_down);
	lcd.AddChar(5, char_arrow_up);
	// Mensaje de inicio
	lcd.Print(0, 0, "Boot up...");
	
	// Configura el sensor DHT
	dht.Start();
	
	// Configura el RTC
	rtc.Start();
	_hour = 0xFF;
	_minute = 0xFF;
	_second = rtc.second;
	dot2 = true;
	
	// Display sensor ambiental
	ambiental_text_data = false;
	ambiental_text_error = false;
	_temperature = 0xFF;
	_humidity = 0xFF;
	
	// Control del sensor ambiental
	temperature_alarm = false;
	humidity_alarm = false;
	sensor_alarm = false;
	sensor_error_count = 0;
	
	// Control de la temperatura
	temp_too_high = false;
	temp_too_low = false;
	pinMode(CORE_IR_LIGHT_PIN, OUTPUT);
	heater_active = false;
	
	// Control de la humedad
	humi_too_high = false;
	humi_too_low = false;
	pinMode(CORE_HUMIDIFIER_PIN, OUTPUT);
	humidifier_active = false;
	
	// Control de la luz diurna
	sunrise_time = (SUNRISE_HOUR * 60) + SUNRISE_MINUTE;
	sunset_time = (SUNSET_HOUR * 60) + SUNSET_MINUTE;
	pinMode(CORE_DAY_LIGHT_PIN, OUTPUT);
	daylight_active = false;
	
	// Alarma
	alarm_on = false;
	alarm_repeat_count = 0;
	alarm_blink = true;
	alarm_blink_count  = 0;
		
}



/*** Actualiza el programa ***/
void Core::Update() {
	
	// Si no se ha alcanzado el tiempo de refresco, sal
	if ((((long int)(millis() / CORE_FREQ_DIVIDER)) % CORE_MAIN_UPDATE_FREQ) != 0) {
		_update = false;
		return;
	}
	// Si ya se ha actualizado en este ciclo, sal
	if (_update) return;

	// Logica del programa
	Logic();

	// Indica que ya se ha actualizado
	_update = true;
	
}



/*** Logica del programa ***/
void Core::Logic() {
	
	Common();					// Metodos comunes
	DisplayAmbientalData();		// Muestra los datos ambientales
	DisplayTime();				// Muestra la hora actual
	DisplayOutputState();
	
}



/*** Procesos comunes a todos los estados ***/
void Core::Common() {
	
	// Led de actividad
	if (CORE_LED_ACTIVITY) {
		digitalWrite(LED_BUILTIN, _led_blink);
		_led_blink = !_led_blink;
	}
	
	// Control del sensor ambiental
	AmbientalSensorControl();
	// Control de temperatura
	TemperatureControl();
	// Control de la humedad relativa
	HumidityControl();
	
	// Control horario
	rtc.Read();
	DayLightControl();
	
	// Alarmas
	Alarm();
	
}



/*** Muestra los datos ambientales en el LCD ***/
void Core::DisplayAmbientalData() {

	String text = String("");

	if (dht.sensor_status) {
		
		// Texto inicial
		if (!ambiental_text_data) {
			
			lcd.Cls(0, 0, 16);
			text = String("T:") + String(dht.temperature) + String("C");
			lcd.Print(0, 0, text);
			
			text = String("H:") + String(dht.humidity) + String("%");
			lcd.Print(8, 0, text);
			
			ambiental_text_data = true;
			ambiental_text_error = false;
			
		} else {
			
			// Actualiza la temperatura
			if (_temperature == dht.temperature) {
				lcd.Cls(2, 0, 5);
				text = String(dht.temperature) + String("C");
				lcd.Print(2, 0, text);
				_temperature = dht.temperature;
			}
			
			// Alarma de temperatura
			if (alarm_blink && (temp_too_low || temp_too_high)) {
				if (temp_too_low) {
					lcd.PrintChar(6, 0, 4);
				} else if (temp_too_high) {
					lcd.PrintChar(6, 0, 5);
				}
			} else {
				lcd.Print(6, 0, " ");
			}
			
			// Actualiza la humedad
			if (_humidity == dht.humidity) {
				lcd.Cls(10, 0, 5);
				text = String(dht.humidity) + String("%");
				lcd.Print(10, 0, text);
				_humidity = dht.humidity;
			}
			
			// Alarma de humedad
			if (alarm_blink && (humi_too_low || humi_too_high)) {
				if (humi_too_low) {
					lcd.PrintChar(14, 0, 4);
				} else if (humi_too_high) {
					lcd.PrintChar(14, 0, 5);
				}
			} else {
				lcd.Print(14, 0, " ");
			}
			
		}
		
	} else {
		
		// Mensage de error del sensor
		if (!ambiental_text_error) {
			lcd.Cls(0, 0, 16);
			lcd.Print(0, 0, "DHT Sensor ERROR");
			ambiental_text_error = true;
			ambiental_text_data = false;
		}
		
	}

}



/*** Muestra la hora ***/
void Core::DisplayTime() {
	
	// Si ha pasado un segundo
	if (rtc.second == _second) return;
	_second = rtc.second;
	
	String text = String("");
	
	// Marcador de segundos
	text = dot2 ? String(":"):String(" ");
	lcd.Print(2, 1, text);
	dot2 = !dot2;
	
	// Minutos
	if (rtc.minute == _minute) return;
	text = String("");
	if (rtc.minute < 10) text += String("0");
	text += String(rtc.minute);
	lcd.Print(3, 1, text);
	_minute = rtc.minute;
	
	// Horas
	if (rtc.hour == _hour) return;
	text = String("");
	if (rtc.hour < 10) text += String("0");
	text += String(rtc.hour);
	lcd.Print(0, 1, text);
	_hour = rtc.hour;

}


/*** Muestra el estado de las salidas ***/
void Core::DisplayOutputState() {
	
	if (heater_active) {
		lcd.PrintChar(11, 1, 1);
	} else {
		lcd.PrintChar(11, 1, 0);
	}
	
	if (humidifier_active) {
		lcd.PrintChar(13, 1, 2);
	} else {
		lcd.PrintChar(13, 1, 0);
	}
	
	if (daylight_active) {
		lcd.PrintChar(15, 1, 3);
	} else {
		lcd.PrintChar(15, 1, 0);
	}
	
}



/*** Control del sensor ambiental ***/
void Core::AmbientalSensorControl() {
	
	// Lee los datos del sensor ambbiental
	dht.Read();
	
	// Error de lectura del sensor
	if (!dht.sensor_status) {
		sensor_error_count ++;
		if (sensor_error_count >= SENSOR_ERROR_TIMEOUT) {
			sensor_error_count = SENSOR_ERROR_TIMEOUT;
			sensor_alarm = true;
		}
		return;
	}
	
	// Deshabilita el sensor de alarma
	sensor_alarm = false;
	sensor_error_count = 0;
	
}



/*** Control de la temperatura ***/
void Core::TemperatureControl() {
	
	// Si el sensor esta operativo
	if (dht.sensor_status) {
	
		if (dht.temperature <= TEMP_MIN_TRIGGER) {
			
			// Enciende la lampara
			digitalWrite(CORE_IR_LIGHT_PIN, 1);
			heater_active = true;
			
		} else if (dht.temperature >= TEMP_MAX_TRIGGER) {
			
			// Apaga la lampara
			digitalWrite(CORE_IR_LIGHT_PIN, 0);
			heater_active = false;
			
		}
		
		// Control de rango de temperaturas peligrosas
		temp_too_low = (dht.temperature <= TEMP_MIN_ALARM) ? true:false;
		temp_too_high = (dht.temperature >= TEMP_MAX_ALARM) ? true:false;
		temperature_alarm = (temp_too_low | temp_too_high);
	
	} else {
		
		// Si el sensor no esta operativo, desconectalo todo
		digitalWrite(CORE_IR_LIGHT_PIN, 0);
		heater_active = false;
		temp_too_low = false;
		temp_too_high = false;
		temperature_alarm = false;
		
	}
			
}



/*** Control de la humedad ***/
void Core::HumidityControl() {
	
	// Si el sensor esta operativo
	if (dht.sensor_status) {
	
		if (dht.humidity <= HUMIDITY_MIN_TRIGGER) {
			
			// Enciende el humidificador
			digitalWrite(CORE_HUMIDIFIER_PIN, 1);
			humidifier_active = true;
			
		} else if (dht.humidity >= HUMIDITY_MAX_TRIGGER) {
			
			// Apaga el humidificador
			digitalWrite(CORE_HUMIDIFIER_PIN, 0);
			humidifier_active = false;
			
		}
		
		// Control de rango de humedades relativas peligrosas
		humi_too_low = (dht.humidity <= HUMIDITY_MIN_ALARM) ? true:false;
		humi_too_high = (dht.humidity >= HUMIDITY_MAX_ALARM) ? true:false;
		humidity_alarm = (humi_too_low | humi_too_high);
	
	} else {
		
		// Si el sensor no esta operativo, desconectalo todo
		digitalWrite(CORE_HUMIDIFIER_PIN, 0);
		humidifier_active = false;
		humi_too_low = false;
		humi_too_high = false;
		humidity_alarm = false;
		
	}
			
}



/*** Control de la lampara de dia ***/
void Core::DayLightControl() {
	
	// Calcula el global de tiempo
	int current_time = (rtc.hour * 60) + rtc.minute;
	
	// Ajuste para arcos temporales con cambio de dia
	int start_time = 0, end_time = 0;
	bool on = false, off = false;
	if (sunset_time >= sunrise_time) {	
		start_time = sunrise_time;
		end_time = sunset_time;
		on = true;
		off = false;		
	} else {
		start_time = sunset_time;
		end_time = sunrise_time;
		on = false;
		off = true;
	}
	
	// Verifica si hay que encender la Luz
	if ((current_time >= start_time) && (current_time < end_time)) {
		digitalWrite(CORE_DAY_LIGHT_PIN, on);
		daylight_active = on;
	} else {	
		digitalWrite(CORE_DAY_LIGHT_PIN, off);
		daylight_active = false;
	}
	
}



/*** Alarma ***/
void Core::Alarm() {

	if (temperature_alarm || humidity_alarm || sensor_alarm) {
		if (!alarm_on) {
			if (CORE_BUFFER_ALARM) tone(CORE_BUZZER_PIN, ALARM_TONE, ALARM_TONE_ON);
			alarm_on = true;
			alarm_repeat_count = 0;
		} else {
			alarm_repeat_count ++;
			if (alarm_repeat_count >= ALARM_TONE_OFF) alarm_on = false;
		}
		alarm_blink_count ++;
		if (alarm_blink_count >= ALARM_BLINK_SPEED) {
			alarm_blink = !alarm_blink;
			alarm_blink_count = 0;
		}
	} else {
		alarm_on = false;
		alarm_repeat_count = 0;
	}

}



