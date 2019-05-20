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



/*** Includes ***/
// Includes del proyecto
#include "menu.h"



/*** Constructor ***/
Menu::Menu() {
}



/*** Destructor ***/
Menu::~Menu() {
}



/*** Al iniciar el programa ***/
void Menu::Start(Eeprom_d _data) {
	
	// Guarda los datos actuales
	old_data = data = _data;
	
	// Maquina de estados
	st = next_st = MENU_ST_MAIN;
	
	// Valores temporales
	kb_up = kb_down = kb_fwd = kb_back = false;
	auto_key_delay = 0;
	auto_key_repeat = 0;
	temp_value = 0;
	param_value = 0;
	held_time = 0;
	
	// Captura del tiempo actual
	ReadDateTime();
	
	// Opciones del menu principal (MAIN)
	main_menu_op = 0; main_menu_op_last = -1;
	// Opciones del menu de temperatura
	temperature_menu_op = 0, temperature_menu_op_last = -1;
	// Opciones del menu de humedad relativa
	humidity_menu_op = 0, humidity_menu_op_last = -1;
	// Opciones del menu de luz diurna
	sunlight_menu_op = 0, sunlight_menu_op_last = -1;
	// Opciones del menu de fecha y hora
	datetime_menu_op = 0, datetime_menu_op_last = -1;
			
}



/*** Ejecuta el programa ***/
S16 Menu::Run() {
	
	// Valores temporales
	S16 max = 0;
	
	// Resultado
	S16 r = -1;
	
	// Lee el teclado
	Keyboard();
	
	// Maquina de estados
	switch (st) {
		
		/***************************************
			MENU PRINCIPAL
		***************************************/
		case MENU_ST_MAIN:
			switch (MenuMain()) {
				case MENU_OP_EXIT:								// Sal del menu
					// Restaura las opciones iniciales
					main_menu_op = 0; main_menu_op_last = -1;
					// Verifica si han cambiado los datos
					if (!eeprom.Compare(data, old_data)) {
						// Si han cambiado, guardalos en la EEPROM
						eeprom.Save(data);
					}
					r = 0;
					break;
				case MAIN_MENU_OP_TEMPERATURE:					// Selecciona el sub-menu "Temperatura"
					next_st = MENU_ST_TEMPERATURE;
					break;
				case MAIN_MENU_OP_HUMIDITY:						// Selecciona el sub-menu "Humedad"
					next_st = MENU_ST_HUMIDITY;
					break;
				case MAIN_MENU_OP_SUNLIGHT:						// Selecciona el sub-menu "Luz diurna"
					next_st = MENU_ST_SUNLIGHT;
					break;
				case MAIN_MENU_OP_DATETIME:						// Selecciona el sub-menu "Fecha y hora"
					next_st = MENU_ST_DATETIME;
					break;
				case MAIN_MENU_OP_SYSTEM:						// Selecciona el sub-menu "Sistema"
					next_st = MENU_ST_SYSTEM;
					break;
			}
			break;
		
		
		/***************************************
			TEMPERATURA
		***************************************/
		// Menu de parametros
		case MENU_ST_TEMPERATURE:
			switch (MenuTemperature()) {
				case MENU_OP_EXIT:								// Vuelve al menu principal
					// Restaura las opciones iniciales
					temperature_menu_op = 0, temperature_menu_op_last = -1;
					// Cambio de estado
					next_st = MENU_ST_MAIN;
					break;
				case TEMPERATURE_MENU_OP_MIN:					// Temperatura minima
					temp_value = data.min_temp;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = TEMPERATURE_ST_MIN;
					break;
				case TEMPERATURE_MENU_OP_MAX:					// Temperatura maxima
					temp_value = data.max_temp;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = TEMPERATURE_ST_MAX;
					break;
				case TEMPERATURE_MENU_OP_LOWALARM:				// Alarma de temperatura minima
					temp_value = data.min_temp_alarm;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = TEMPERATURE_ST_LOWALARM;
					break;
				case TEMPERATURE_MENU_OP_HIALARM:				// Alarma de temperatura minima
					temp_value = data.max_temp_alarm;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = TEMPERATURE_ST_HIALARM;
					break;					
			}
			break;
			
		// Ajusta la temperatura minima
		case TEMPERATURE_ST_MIN:
			param_value = data.min_temp;
			if (
				SetValue(param_value, data.min_temp_alarm, (data.max_temp - 1), UNIT_GRADES, 3) >= 0
			) {
				data.min_temp = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		// Ajusta la temperatura maxima
		case TEMPERATURE_ST_MAX:
			param_value = data.max_temp;
			if (
				SetValue(param_value, (data.min_temp + 1), data.max_temp_alarm, UNIT_GRADES, 3) >= 0
			) {
				data.max_temp = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		// Ajusta la alarma de temperatura minima
		case TEMPERATURE_ST_LOWALARM:
			param_value = data.min_temp_alarm;
			if (
				SetValue(param_value, ABS_TEMP_MIN, data.min_temp, UNIT_GRADES, 3) >= 0
			) {
				data.min_temp_alarm = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		// Ajusta la alarma de temperatura maxima
		case TEMPERATURE_ST_HIALARM:
			param_value = data.max_temp_alarm;
			if (
				SetValue(param_value, data.max_temp, ABS_TEMP_MAX, UNIT_GRADES, 3) >= 0
			) {
				data.max_temp_alarm = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		
		/***************************************
			HUMEDAD
		***************************************/		
		// Menu de parametros
		case MENU_ST_HUMIDITY:
			switch (MenuHumidity()) {
				case MENU_OP_EXIT:								// Vuelve al menu principal
					// Restaura las opciones iniciales
					humidity_menu_op = 0, humidity_menu_op_last = -1;
					// Cambio de estado
					next_st = MENU_ST_MAIN;
					break;
				case HUMIDITY_MENU_OP_MIN:					// Temperatura minima
					temp_value = data.min_humi;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = HUMIDITY_ST_MIN;
					break;
				case HUMIDITY_MENU_OP_MAX:					// Temperatura maxima
					temp_value = data.max_humi;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = HUMIDITY_ST_MAX;
					break;
				case HUMIDITY_MENU_OP_LOWALARM:				// Alarma de temperatura minima
					temp_value = data.min_humi_alarm;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = HUMIDITY_ST_LOWALARM;
					break;
				case HUMIDITY_MENU_OP_HIALARM:				// Alarma de temperatura minima
					temp_value = data.max_humi_alarm;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = HUMIDITY_ST_HIALARM;
					break;
				case HUMIDITY_MENU_OP_ONTIME:				// Tiempo de actividad del aspersor
					temp_value = Ticks2Seconds(data.humi_duty_cycle_on);
					ngn.lcd.Print(10, 1, CURSOR_CHAR);
					next_st = HUMIDITY_ST_ONTIME;
					break;
				case HUMIDITY_MENU_OP_OFFTIME:				// Tiempo de reposo del aspersor
					temp_value = Ticks2Seconds(data.humi_duty_cycle_off);
					ngn.lcd.Print(10, 1, CURSOR_CHAR);
					next_st = HUMIDITY_ST_OFFTIME;
					break;					
			}
			break;
			
		// Ajusta la humedad minima
		case HUMIDITY_ST_MIN:
			param_value = data.min_humi;
			if (
				SetValue(param_value, data.min_humi_alarm, (data.max_humi - 1), UNIT_PERCENT, 3) >= 0
			) {
				data.min_humi = param_value;
				next_st = MENU_ST_HUMIDITY;
			}
			break;
			
		// Ajusta la humedad maxima
		case HUMIDITY_ST_MAX:
			param_value = data.max_humi;
			if (
				SetValue(param_value, (data.min_humi + 1), data.max_humi_alarm, UNIT_PERCENT, 3) >= 0
			) {
				data.max_humi = param_value;
				next_st = MENU_ST_HUMIDITY;
			}
			break;
			
		// Ajusta la alarma de humedad minima
		case HUMIDITY_ST_LOWALARM:
			param_value = data.min_humi_alarm;
			if (
				SetValue(param_value, ABS_HUMI_MIN, data.min_humi, UNIT_PERCENT, 3) >= 0
			) {
				data.min_humi_alarm = param_value;
				next_st = MENU_ST_HUMIDITY;
			}
			break;
			
		// Ajusta la alarma de humedad maxima
		case HUMIDITY_ST_HIALARM:
			param_value = data.max_humi_alarm;
			if (
				SetValue(param_value, data.max_humi, ABS_HUMI_MAX, UNIT_PERCENT, 3) >= 0
			) {
				data.max_humi_alarm = param_value;
				next_st = MENU_ST_HUMIDITY;
			}
			break;
			
		// Ajusta el ciclo de trabajo del aspersor (Encendido)
		case HUMIDITY_ST_ONTIME:
			param_value = Ticks2Seconds(data.humi_duty_cycle_on);
			if (
				SetValue(param_value, ABS_DUTY_MIN, ABS_DUTY_MAX, UNIT_SECONDS, 4) >= 0
			) {
				data.humi_duty_cycle_on = Seconds2Ticks(param_value);
				next_st = MENU_ST_HUMIDITY;
			}
			break;
			
		// Ajusta el ciclo de trabajo del aspersor (Apagado)
		case HUMIDITY_ST_OFFTIME:
			param_value = Ticks2Seconds(data.humi_duty_cycle_off);
			if (
				SetValue(param_value, ABS_DUTY_MIN, ABS_DUTY_MAX, UNIT_SECONDS, 4) >= 0
			) {
				data.humi_duty_cycle_off = Seconds2Ticks(param_value);
				next_st = MENU_ST_HUMIDITY;
			}
			break;
			
			
		/***************************************
			LUZ DIURNA
		***************************************/
		// Menu de parametros
		case MENU_ST_SUNLIGHT:
			switch (MenuSunLight()) {
				case MENU_OP_EXIT:							// Vuelve al menu principal
					// Restaura las opciones iniciales
					sunlight_menu_op = 0, sunlight_menu_op_last = -1;
					// Cambio de estado
					next_st = MENU_ST_MAIN;
					break;
				case SUNLIGHT_MENU_OP_RISE_H:				// Hora de salida del sol
					temp_value = data.sunrise_hour;
					ngn.lcd.Print(12, 1, CURSOR_CHAR);
					next_st = SUNLIGHT_ST_RISE_H;
					break;
				case SUNLIGHT_MENU_OP_RISE_M:				// Minuto de salida del sol
					temp_value = data.sunrise_minute;
					ngn.lcd.Print(12, 1, CURSOR_CHAR);
					next_st = SUNLIGHT_ST_RISE_M;
					break;
				case SUNLIGHT_MENU_OP_SET_H:				// Hora de puesta del sol
					temp_value = data.sunset_hour;
					ngn.lcd.Print(12, 1, CURSOR_CHAR);
					next_st = SUNLIGHT_ST_SET_H;
					break;
				case SUNLIGHT_MENU_OP_SET_M:				// Minuto de puesta del sol
					temp_value = data.sunset_minute;
					ngn.lcd.Print(12, 1, CURSOR_CHAR);
					next_st = SUNLIGHT_ST_SET_M;
					break;
			}
			break;
			
		// Ajusta la hora de salida del sol
		case SUNLIGHT_ST_RISE_H:
			param_value = data.sunrise_hour;
			if (
				SetValue(param_value, 0, 23, UNIT_HOURS, 2) >= 0
			) {
				data.sunrise_hour = param_value;
				next_st = MENU_ST_SUNLIGHT;
			}
			break;
			
		// Ajusta el minuto de salida del sol
		case SUNLIGHT_ST_RISE_M:
			param_value = data.sunrise_minute;
			if (
				SetValue(param_value, 0, 59, UNIT_MINUTES, 2) >= 0
			) {
				data.sunrise_minute = param_value;
				next_st = MENU_ST_SUNLIGHT;
			}
			break;
			
		// Ajusta la hora de puesta del sol
		case SUNLIGHT_ST_SET_H:
			param_value = data.sunset_hour;
			if (
				SetValue(param_value, 0, 23, UNIT_HOURS, 2) >= 0
			) {
				data.sunset_hour = param_value;
				next_st = MENU_ST_SUNLIGHT;
			}
			break;
			
		// Ajusta el minuto de puesta del sol
		case SUNLIGHT_ST_SET_M:
			param_value = data.sunset_minute;
			if (
				SetValue(param_value, 0, 59, UNIT_MINUTES, 2) >= 0
			) {
				data.sunset_minute = param_value;
				next_st = MENU_ST_SUNLIGHT;
			}
			break;
			
		
			
		/***************************************
			FECHA Y HORA
		***************************************/
		// Menu de parametros	
		case MENU_ST_DATETIME:
			switch (MenuDateTime()) {
				case MENU_OP_EXIT:							// Vuelve al menu principal
					// Restaura las opciones iniciales
					datetime_menu_op = 0, datetime_menu_op_last = -1;
					// Cambio de estado
					next_st = MENU_ST_MAIN;
					break;
				case DATETIME_MENU_OP_SECOND:				// Segundos
					temp_value = time_snap.second;
					ngn.lcd.Print(13, 1, CURSOR_CHAR);
					next_st = DATETIME_ST_SECOND;
					break;
				case DATETIME_MENU_OP_MINUTE:				// Minutos
					temp_value = time_snap.minute;
					ngn.lcd.Print(13, 1, CURSOR_CHAR);
					next_st = DATETIME_ST_MINUTE;
					break;
				case DATETIME_MENU_OP_HOUR:					// Horas
					temp_value = time_snap.hour;
					ngn.lcd.Print(13, 1, CURSOR_CHAR);
					next_st = DATETIME_ST_HOUR;
					break;
				case DATETIME_MENU_OP_DAY:					// Dia
					temp_value = time_snap.day;
					ngn.lcd.Print(13, 1, CURSOR_CHAR);
					next_st = DATETIME_ST_DAY;
					break;
				case DATETIME_MENU_OP_MONTH:				// Mes
					temp_value = time_snap.month;
					ngn.lcd.Print(13, 1, CURSOR_CHAR);
					next_st = DATETIME_ST_MONTH;
					break;
				case DATETIME_MENU_OP_YEAR:					// Año
					temp_value = time_snap.year;
					ngn.lcd.Print(11, 1, CURSOR_CHAR);
					next_st = DATETIME_ST_YEAR;
					break;
			}
			break;
			
		// Ajusta los segundos
		case DATETIME_ST_SECOND:
			param_value = time_snap.second;
			if (
				SetValue(param_value, 0, 59, UNIT_NONE, 2) >= 0
			) {
				if (time_snap.second != param_value) {
					ReadDateTime();
					time_snap.second = param_value;
					SaveDateTime();
				}
				next_st = MENU_ST_DATETIME;
			}
			break;
			
		// Ajusta los minutos
		case DATETIME_ST_MINUTE:
			param_value = time_snap.minute;
			if (
				SetValue(param_value, 0, 59, UNIT_NONE, 2) >= 0
			) {
				if (time_snap.minute != param_value) {
					ReadDateTime();
					time_snap.minute = param_value;
					SaveDateTime();
				}
				next_st = MENU_ST_DATETIME;
			}
			break;
			
		// Ajusta las horas
		case DATETIME_ST_HOUR:
			param_value = time_snap.hour;
			if (
				SetValue(param_value, 0, 23, UNIT_NONE, 2) >= 0
			) {
				if (time_snap.hour != param_value) {
					ReadDateTime();
					time_snap.hour = param_value;
					SaveDateTime();
				}
				next_st = MENU_ST_DATETIME;
			}
			break;
			
		// Ajusta el dia
		case DATETIME_ST_DAY:
			// Segun el mes y año...
			switch (time_snap.month) {
				// Meses de 31 dias
				case 1:	case 3:	case 5:	case 7:	case 8: case 10: case 12:
					max = 31;
					break;
				// Meses de 30 dias
				case 4:	case 6:	case 9:	case 11:
					max = 30;
					break;
				// Febrero
				case 2:
					// Si es año bisiesto o no...
					if (
					((time_snap.year % 4) == 0)
					&&
					(((time_snap.year % 100) != 0) || ((time_snap.year % 400) == 0))
					) {
						max = 29;
					} else {
						max = 28;
					}
					break;	
			}
			// Ajuste del parametro
			param_value = time_snap.day;
			if (
				SetValue(param_value, 1, max, UNIT_NONE, 2) >= 0
			) {
				if (time_snap.day != param_value) {
					ReadDateTime();
					time_snap.day = param_value;
					SaveDateTime();
				}
				next_st = MENU_ST_DATETIME;
			}
			break;
			
		// Ajusta el mes
		case DATETIME_ST_MONTH:
			param_value = time_snap.month;
			if (
				SetValue(param_value, 1, 12, UNIT_NONE, 2) >= 0
			) {
				if (time_snap.month != param_value) {
					ReadDateTime();
					time_snap.month = param_value;
					SaveDateTime();
				}
				next_st = MENU_ST_DATETIME;
			}
			break;
			
		// Ajusta el año
		case DATETIME_ST_YEAR:
			param_value = time_snap.year;
			if (
				SetValue(param_value, 2000, 2099, UNIT_NONE, 4) >= 0
			) {
				if (time_snap.year != param_value) {
					ReadDateTime();
					time_snap.year = param_value;
					SaveDateTime();
				}
				next_st = MENU_ST_DATETIME;
			}
			break;
			
			
		/***************************************
			CONFIGURACION DEL SISTEMA
		***************************************/
			
		case MENU_ST_SYSTEM:
			r = 0;
			break;
			
			
	}
	
	// Actualiza el estado
	st = next_st;
	
	return r;
	
}



/*** Devuelve los datos ***/
Eeprom_d Menu::GetData() {
	
	return data;
	
}



/*** Gestion del teclado ***/
void Menu::Keyboard() {
	
	// Reset de teclas
	kb_up = kb_down = kb_fwd = kb_back = false;
	
	// Control del teclado
	if (ngn.input.KeyDown(KEY_UP_ID)) {
		// UP
		kb_up = true;
		auto_key_delay = 0;
		held_time = 0;
	} else if (ngn.input.KeyDown(KEY_DOWN_ID)) {
		// DOWN
		kb_down = true;
		auto_key_delay = 0;
		held_time = 0;
	} else if (ngn.input.KeyDown(KEY_RIGHT_ID)) {
		// FORWARD
		kb_fwd = true;
		auto_key_delay = 0;
		held_time = 0;
	} else if (ngn.input.KeyDown(KEY_LEFT_ID)) {
		// BACK
		kb_back = true;
		auto_key_delay = 0;
		held_time = 0;
	} else if (ngn.input.KeyHeld(KEY_UP_ID)) {
		// UP al mantener pulsado
		if (auto_key_delay < AUTO_KEY_DELAY) {
			auto_key_delay ++;
			auto_key_repeat = 0;
		} else {
			auto_key_repeat ++;
			if (auto_key_repeat >= AUTO_KEY_REPEAT) {
				auto_key_repeat = 0;
				kb_up = true;
			}
		}
		held_time ++;
	} else if (ngn.input.KeyHeld(KEY_DOWN_ID)) {
		// DOWN al mantener pulsado
		if (auto_key_delay < AUTO_KEY_DELAY) {
			auto_key_delay ++;
			auto_key_repeat = 0;
		} else {
			auto_key_repeat ++;
			if (auto_key_repeat >= AUTO_KEY_REPEAT) {
				auto_key_repeat = 0;
				kb_down = true;
			}
		}
		held_time ++;
	} else {
		auto_key_delay = 0;
		held_time = 0;
	}
	
}



/*** Menu principal ***/
S16 Menu::MenuMain() {
	
	// Resultado
	S16 r = -1;
	
	// Dibujado inicial?
	if (main_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, (CURSOR_CHAR + "Setup"));
	}
	
	// Control del teclado
	if (kb_up) {
		// Opcion anterior
		main_menu_op --;
		if (main_menu_op < 0) main_menu_op = 0;
	} else if (kb_down) {
		// Opcion siguiente
		main_menu_op ++;
		if (main_menu_op >= MAIN_MENU_OPTIONS) main_menu_op = (MAIN_MENU_OPTIONS - 1);
	} else if (kb_fwd) {
		// Acepta
		r = main_menu_op;
	} else if (kb_back) {
		// Cancela
		r = MENU_OP_EXIT;
	}
	
	// Si ha canviado la opcion, cambia el texto
	if (main_menu_op_last != main_menu_op) {
		ngn.lcd.Cls(0, 1, 16);
		ngn.lcd.Print(0, 1, main_menu_text[main_menu_op]);
	}
	
	// Guarda la opcion
	main_menu_op_last = (r < 0) ? main_menu_op:-1;
	
	// Devuelve el resultado
	return r;
	
}



/*** Menu de configuracion de la temperatura ***/
S16 Menu::MenuTemperature() {
	
	// Resultado
	S16 r = -1;
	
	// Array con los datos actuales
	S8 dt[TEMPERATURE_MENU_OPTIONS] = {
		data.min_temp,
		data.max_temp,
		data.min_temp_alarm,
		data.max_temp_alarm
	};
	
	// Dibujado inicial?
	if (temperature_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, (CURSOR_CHAR + main_menu_text[MAIN_MENU_OP_TEMPERATURE]));
	}
	
	// Control del teclado
	if (kb_up) {
		// Opcion anterior
		temperature_menu_op --;
		if (temperature_menu_op < 0) temperature_menu_op = 0;
	} else if (kb_down) {
		// Opcion siguiente
		temperature_menu_op ++;
		if (temperature_menu_op >= TEMPERATURE_MENU_OPTIONS) temperature_menu_op = (TEMPERATURE_MENU_OPTIONS - 1);
	} else if (kb_fwd) {
		// Acepta
		r = temperature_menu_op;
	} else if (kb_back) {
		// Cancela
		r = MENU_OP_EXIT;
	}
	
	// Si ha canviado la opcion, cambia el texto
	if (temperature_menu_op_last != temperature_menu_op) {
		ngn.lcd.Cls(0, 1, 16);
		ngn.lcd.Print(0, 1, temperature_menu_text[temperature_menu_op]);
		ngn.lcd.Print(12, 1, ngn.string.Int2String(dt[temperature_menu_op], 3));
		ngn.lcd.PrintChar(15, 1, CH_GRADES);
	}
	
	// Guarda la opcion
	temperature_menu_op_last = (r < 0) ? temperature_menu_op:-1;
	
	// Devuelve el resultado
	return r;
	
}



/*** Menu de configuracion de la humedad ***/
S16 Menu::MenuHumidity() {
	
	// Resultado
	S16 r = -1;
	
	// Array con los datos actuales
	S32 dt[HUMIDITY_MENU_OPTIONS][2] = {
		{(S32)data.min_humi, 0},
		{(S32)data.max_humi, 0},
		{(S32)data.min_humi_alarm, 0},
		{(S32)data.max_humi_alarm, 0},
		{data.humi_duty_cycle_on, 1},
		{data.humi_duty_cycle_off, 1}
	};
	
	// Dibujado inicial?
	if (humidity_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, (CURSOR_CHAR + main_menu_text[MAIN_MENU_OP_HUMIDITY]));
	}
	
	// Control del teclado
	if (kb_up) {
		// Opcion anterior
		humidity_menu_op --;
		if (humidity_menu_op < 0) humidity_menu_op = 0;
	} else if (kb_down) {
		// Opcion siguiente
		humidity_menu_op ++;
		if (humidity_menu_op >= HUMIDITY_MENU_OPTIONS) humidity_menu_op = (HUMIDITY_MENU_OPTIONS - 1);
	} else if (kb_fwd) {
		// Acepta
		r = humidity_menu_op;
	} else if (kb_back) {
		// Cancela
		r = MENU_OP_EXIT;
	}
	
	// Si ha canviado la opcion, cambia el texto
	if (humidity_menu_op_last != humidity_menu_op) {
		String symbol = "";
		S16 value = 0;
		U8 width = 0;
		if (dt[humidity_menu_op][1] == 0) {
			value = dt[humidity_menu_op][0];
			symbol = "%";
			width = 3;
		} else {
			value = Ticks2Seconds(dt[humidity_menu_op][0]);
			symbol = "s";
			width = 4;
		}
		ngn.lcd.Cls(0, 1, 16);
		ngn.lcd.Print(0, 1, humidity_menu_text[humidity_menu_op]);
		ngn.lcd.Print((15 - width), 1, ngn.string.Int2String(value, width));
		ngn.lcd.Print(15, 1, symbol);
	}
	
	// Guarda la opcion
	humidity_menu_op_last = (r < 0) ? humidity_menu_op:-1;
	
	// Devuelve el resultado
	return r;
	
}



/*** Menu de la lampara de luz diurna ***/
S16 Menu::MenuSunLight() {
	
	// Resultado
	S16 r = -1;
	
	// Array con los datos actuales
	S8 dt[SUNLIGHT_MENU_OPTIONS] = {
		data.sunrise_hour,
		data.sunrise_minute,
		data.sunset_hour,
		data.sunset_minute
	};
	String symbol[SUNLIGHT_MENU_OPTIONS] = {
		"h", "m", "h", "m"
	};
	
	// Dibujado inicial?
	if (sunlight_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, (CURSOR_CHAR + main_menu_text[MAIN_MENU_OP_SUNLIGHT]));
	}
	
	// Control del teclado
	if (kb_up) {
		// Opcion anterior
		sunlight_menu_op --;
		if (sunlight_menu_op < 0) sunlight_menu_op = 0;
	} else if (kb_down) {
		// Opcion siguiente
		sunlight_menu_op ++;
		if (sunlight_menu_op >= SUNLIGHT_MENU_OPTIONS) sunlight_menu_op = (SUNLIGHT_MENU_OPTIONS - 1);
	} else if (kb_fwd) {
		// Acepta
		r = sunlight_menu_op;
	} else if (kb_back) {
		// Cancela
		r = MENU_OP_EXIT;
	}
	
	// Si ha canviado la opcion, cambia el texto
	if (sunlight_menu_op_last != sunlight_menu_op) {
		ngn.lcd.Cls(0, 1, 16);
		ngn.lcd.Print(0, 1, sunlight_menu_text[sunlight_menu_op]);
		ngn.lcd.Print(13, 1, ngn.string.Int2String(dt[sunlight_menu_op], 2));
		ngn.lcd.Print(15, 1, symbol[sunlight_menu_op]);
	}
	
	// Guarda la opcion
	sunlight_menu_op_last = (r < 0) ? sunlight_menu_op:-1;
	
	// Devuelve el resultado
	return r;
	
}



/*** Menu de ajuste de fecha y hora ***/
S16 Menu::MenuDateTime() {
	
	// Resultado
	S16 r = -1;
	
	// Array con los datos actuales
	S16 dt[DATETIME_MENU_OPTIONS][2] = {
		{ngn.rtc.second, 2},
		{ngn.rtc.minute, 2},
		{ngn.rtc.hour, 2},
		{ngn.rtc.day, 2},
		{ngn.rtc.month, 2},
		{ngn.rtc.year, 4}
	};

	
	// Dibujado inicial?
	if (datetime_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, (CURSOR_CHAR + main_menu_text[MAIN_MENU_OP_DATETIME]));
	}
	
	// Control del teclado
	if (kb_up) {
		// Opcion anterior
		datetime_menu_op --;
		if (datetime_menu_op < 0) datetime_menu_op = 0;
	} else if (kb_down) {
		// Opcion siguiente
		datetime_menu_op ++;
		if (datetime_menu_op >= DATETIME_MENU_OPTIONS) datetime_menu_op = (DATETIME_MENU_OPTIONS - 1);
	} else if (kb_fwd) {
		// Lee la marca de tiempo actual
		ReadDateTime();
		// Acepta
		r = datetime_menu_op;
	} else if (kb_back) {
		// Cancela
		r = MENU_OP_EXIT;
	}
	
	// Si ha canviado la opcion, cambia el texto
	if (datetime_menu_op_last != datetime_menu_op) {
		ngn.lcd.Cls(0, 1, 16);
		ngn.lcd.Print(0, 1, datetime_menu_text[datetime_menu_op]);
		ngn.lcd.Print((16 - dt[datetime_menu_op][1]), 1, ngn.string.Int2String(dt[datetime_menu_op][0], dt[datetime_menu_op][1]));
	}
	
	// Guarda la opcion
	datetime_menu_op_last = (r < 0) ? datetime_menu_op:-1;
	
	// Devuelve el resultado
	return r;
	
}



/*** Cambia el valor de un parametro ***/
S16 Menu::SetValue(S16 &value, S16 min_val, S16 max_val, U8 unit, U8 width) {
	
	// Resultado
	S16 r = -1;
	
	// Variables de control
	bool update = false;
	
	// Control de autosuma
	U8 add = 0;
	if (held_time >= 200) {
		add = 75;
		held_time = 200;
	} else if (held_time >= 150) {
		add = 25;
	} else if (held_time >= 100) {
		add = 10;
	} else {
		add = 1;
	}
	
	// Control por teclado
	if (kb_up) {
		// Suma
		temp_value += add;
		if (temp_value > max_val) temp_value = max_val;
		update = true;
	} else if (kb_down) {
		// Resta
		temp_value -= add;
		if (temp_value < min_val) temp_value = min_val;
		update = true;
	} else if (kb_fwd) {
		// Acepta
		value = temp_value;
		r = 0;
	} else if (kb_back) {
		// Descarta
		r = 0;
	}
		
	// Actualiza el marcador
	if (update) {
		U8 x = (unit == UNIT_NONE) ? (16 - width):(15 - width);
		ngn.lcd.Cls(x, 1, width);
		ngn.lcd.Print(x, 1, ngn.string.Int2String(temp_value, width));
		switch (unit) {
			case UNIT_GRADES:
				ngn.lcd.PrintChar(15, 1, CH_GRADES);
				break;
			case UNIT_PERCENT:
				ngn.lcd.Print(15, 1, "%");
				break;
			case UNIT_HOURS:
				ngn.lcd.Print(15, 1, "h");
				break;
			case UNIT_MINUTES:
				ngn.lcd.Print(15, 1, "m");
				break;
			case UNIT_SECONDS:
				ngn.lcd.Print(15, 1, "s");
				break;
		}		
	}
	
	// Devuelve el resultado
	return r;
	
}




/*** Convierte de tics a segundos ***/
U16 Menu::Ticks2Seconds(U32 ticks) {
		
	return ((ticks * TICK) / BASE);
	
}



/*** Convierte de segundos a tics ***/
U32 Menu::Seconds2Ticks(U16 seconds) {
	
	return ((seconds * BASE) / TICK);
	
}



/*** Lee la marca de tiempo desde el RTC ***/
void Menu::ReadDateTime() {
	
	ngn.rtc.Read();
	
	time_snap.second = ngn.rtc.second;
	time_snap.minute = ngn.rtc.minute;
	time_snap.hour = ngn.rtc.hour;
	time_snap.day = ngn.rtc.day;
	time_snap.month = ngn.rtc.month;
	time_snap.year = ngn.rtc.year;
	
}



/*** Guarda la marca de tiempo en el RTC ***/
void Menu::SaveDateTime() {
	
	ngn.rtc.second = (S8)time_snap.second;
	ngn.rtc.minute = (S8)time_snap.minute;
	ngn.rtc.hour = (S8)time_snap.hour;
	ngn.rtc.day = (S8)time_snap.day;
	ngn.rtc.month = (S8)time_snap.month;
	ngn.rtc.year = (S16)time_snap.year;
	
	ngn.rtc.Save();
	
}
