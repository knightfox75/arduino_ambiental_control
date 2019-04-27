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



/*** Includes ***/
// Includes del proyecto
#include "ambiental_control.h"



/*** Contructor de la clase ***/
AmbientalControl::AmbientalControl() {
}



/*** Destructor de la clase ***/
AmbientalControl::~AmbientalControl() {
}



/*** Incia la clase ***/
void AmbientalControl::Start(Eeprom_d _data) {
	
	// Guarda los parametros
	data = _data;
	
	// Configura el sensor DHT
	ngn.dht.Start(DHT_PIN);
	
	// Configura el RTC
	ngn.rtc.Start();
	_hour = 0xFF;
	_minute = 0xFF;
	_second = 0xFF;
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
	pinMode(IR_LIGHT_PIN, OUTPUT);
	heater_active = false;
	
	// Control de la humedad
	humi_too_high = false;
	humi_too_low = false;
	pinMode(HUMIDIFIER_PIN, OUTPUT);
	humidifier_active = false;
	
	// Control de la luz diurna
	sunrise_time = (data.sunrise_hour * 60) + data.sunrise_minute;
	sunset_time = (data.sunset_hour * 60) + data.sunset_minute;
	pinMode(DAY_LIGHT_PIN, OUTPUT);
	daylight_active = false;
	
	// Alarma
	alarm_on = false;
	alarm_repeat_count = 0;
	alarm_blink = true;
	alarm_blink_count  = 0;
	
}



/*** Ejecucion ***/
void AmbientalControl::Run() {
	
	// Control del sensor ambiental
	AmbientalSensorControl();
	// Control de temperatura
	TemperatureControl();
	// Control de la humedad relativa
	HumidityControl();
	
	// Control horario
	ngn.rtc.Read();
	DayLightControl();
	
	// Alarmas
	Alarm();
		
}



/*** Muestra la informacion en pantalla ***/
void AmbientalControl::DisplayData() {

	DisplayAmbientalData();		// Muestra los datos ambientales
	DisplayTime();				// Muestra la hora actual
	DisplayOutputState();		// Iconos de estado
	
}



/*** Fuerza mostrar la informacion en el proximo ciclo ***/
void AmbientalControl::ForceDisplay() {
	
	ambiental_text_data = false;
	ambiental_text_error = false;
	
	_hour = 0xFF;
	_minute = 0xFF;
	_second = 0xFF;
	dot2 = true;
	
	_temperature = 0xFF;
	_humidity = 0xFF;
	
}




/*** Muestra los datos ambientales en el LCD ***/
void AmbientalControl::DisplayAmbientalData() {

	String text = String("");

	if (ngn.dht.sensor_status) {
		
		// Texto inicial
		if (!ambiental_text_data) {
			
			ngn.lcd.Cls(0, 0, 16);
			text = String("T:") + String(ngn.dht.temperature) + String("C");
			ngn.lcd.Print(0, 0, text);
			
			text = String("H:") + String(ngn.dht.humidity) + String("%");
			ngn.lcd.Print(8, 0, text);
			
			ambiental_text_data = true;
			ambiental_text_error = false;
			
		} else {
			
			// Actualiza la temperatura
			if (_temperature != ngn.dht.temperature) {
				ngn.lcd.Cls(2, 0, 5);
				text = String(ngn.dht.temperature) + String("C");
				ngn.lcd.Print(2, 0, text);
				_temperature = ngn.dht.temperature;
			}
			
			// Alarma de temperatura
			if (alarm_blink && (temp_too_low || temp_too_high)) {
				if (temp_too_low) {
					ngn.lcd.PrintChar(6, 0, 4);
				} else if (temp_too_high) {
					ngn.lcd.PrintChar(6, 0, 5);
				}
			} else {
				ngn.lcd.Print(6, 0, " ");
			}
			
			// Actualiza la humedad
			if (_humidity != ngn.dht.humidity) {
				ngn.lcd.Cls(10, 0, 5);
				text = String(ngn.dht.humidity) + String("%");
				ngn.lcd.Print(10, 0, text);
				_humidity = ngn.dht.humidity;
			}
			
			// Alarma de humedad
			if (alarm_blink && (humi_too_low || humi_too_high)) {
				if (humi_too_low) {
					ngn.lcd.PrintChar(14, 0, 4);
				} else if (humi_too_high) {
					ngn.lcd.PrintChar(14, 0, 5);
				}
			} else {
				ngn.lcd.Print(14, 0, " ");
			}
			
		}
		
	} else {
		
		// Mensage de error del sensor
		if (!ambiental_text_error) {
			ngn.lcd.Cls(0, 0, 16);
			ngn.lcd.Print(0, 0, "DHT Sensor ERROR");
			ambiental_text_error = true;
			ambiental_text_data = false;
		}
		
	}

}



/*** Muestra la hora ***/
void AmbientalControl::DisplayTime() {
	
	// Si ha pasado un segundo
	if (ngn.rtc.second == _second) return;
	_second = ngn.rtc.second;
	
	String text = String("");
	
	// Marcador de segundos
	text = dot2 ? String(":"):String(" ");
	ngn.lcd.Print(2, 1, text);
	dot2 = !dot2;
	
	// Minutos
	if (ngn.rtc.minute == _minute) return;
	text = String("");
	if (ngn.rtc.minute < 10) text += String("0");
	text += String(ngn.rtc.minute);
	ngn.lcd.Print(3, 1, text);
	_minute = ngn.rtc.minute;
	
	// Horas
	if (ngn.rtc.hour == _hour) return;
	text = String("");
	if (ngn.rtc.hour < 10) text += String("0");
	text += String(ngn.rtc.hour);
	ngn.lcd.Print(0, 1, text);
	_hour = ngn.rtc.hour;

}


/*** Muestra el estado de las salidas ***/
void AmbientalControl::DisplayOutputState() {
	
	if (heater_active) {
		ngn.lcd.PrintChar(11, 1, 1);
	} else {
		ngn.lcd.PrintChar(11, 1, 0);
	}
	
	if (humidifier_active) {
		ngn.lcd.PrintChar(13, 1, 2);
	} else {
		ngn.lcd.PrintChar(13, 1, 0);
	}
	
	if (daylight_active) {
		ngn.lcd.PrintChar(15, 1, 3);
	} else {
		ngn.lcd.PrintChar(15, 1, 0);
	}
	
}



/*** Control del sensor ambiental ***/
void AmbientalControl::AmbientalSensorControl() {
	
	// Lee los datos del sensor ambbiental
	ngn.dht.Read();
	
	// Error de lectura del sensor
	if (!ngn.dht.sensor_status) {
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
void AmbientalControl::TemperatureControl() {
	
	// Si el sensor esta operativo
	if (ngn.dht.sensor_status) {
	
		if (ngn.dht.temperature <= data.min_temp) {
			
			// Enciende la lampara
			digitalWrite(IR_LIGHT_PIN, 1);
			heater_active = true;
			
		} else if (ngn.dht.temperature >= data.max_temp) {
			
			// Apaga la lampara
			digitalWrite(IR_LIGHT_PIN, 0);
			heater_active = false;
			
		}
		
		// Control de rango de temperaturas peligrosas
		temp_too_low = (ngn.dht.temperature <= data.min_temp_alarm) ? true:false;
		temp_too_high = (ngn.dht.temperature >= data.max_temp_alarm) ? true:false;
		temperature_alarm = (temp_too_low | temp_too_high);
	
	} else {
		
		// Si el sensor no esta operativo, desconectalo todo
		digitalWrite(IR_LIGHT_PIN, 0);
		heater_active = false;
		temp_too_low = false;
		temp_too_high = false;
		temperature_alarm = false;
		
	}
			
}



/*** Control de la humedad ***/
void AmbientalControl::HumidityControl() {
	
	// Si el sensor esta operativo
	if (ngn.dht.sensor_status) {
	
		if (ngn.dht.humidity <= data.min_humi) {
			
			// Enciende el humidificador
			digitalWrite(HUMIDIFIER_PIN, 1);
			humidifier_active = true;
			
		} else if (ngn.dht.humidity >= data.max_humi) {
			
			// Apaga el humidificador
			digitalWrite(HUMIDIFIER_PIN, 0);
			humidifier_active = false;
			
		}
		
		// Control de rango de humedades relativas peligrosas
		humi_too_low = (ngn.dht.humidity <= data.min_humi_alarm) ? true:false;
		humi_too_high = (ngn.dht.humidity >= data.max_humi_alarm) ? true:false;
		humidity_alarm = (humi_too_low | humi_too_high);
	
	} else {
		
		// Si el sensor no esta operativo, desconectalo todo
		digitalWrite(HUMIDIFIER_PIN, 0);
		humidifier_active = false;
		humi_too_low = false;
		humi_too_high = false;
		humidity_alarm = false;
		
	}
			
}



/*** Control de la lampara de dia ***/
void AmbientalControl::DayLightControl() {
	
	// Calcula el global de tiempo
	int current_time = (ngn.rtc.hour * 60) + ngn.rtc.minute;
	
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
		digitalWrite(DAY_LIGHT_PIN, on);
		daylight_active = on;
	} else {	
		digitalWrite(DAY_LIGHT_PIN, off);
		daylight_active = false;
	}
	
}



/*** Alarma ***/
void AmbientalControl::Alarm() {

	if (temperature_alarm || humidity_alarm || sensor_alarm) {
		if (!alarm_on) {
			if (data.alarm_buzzer) tone(BUZZER_PIN, ALARM_TONE, ALARM_TONE_ON);
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