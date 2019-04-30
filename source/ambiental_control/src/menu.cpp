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
	
	// Opciones del menu principal (MAIN)
	main_menu_op = 0; main_menu_op_last = -1;
	// Opciones del menu de temperatura
	temperature_menu_op = 0, temperature_menu_op_last = -1;
			
}



/*** Ejecuta el programa ***/
int Menu::Run() {
	
	// Resultado
	int r = -1;
	
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
					// Verifica si han cambiado los datos
					if (eeprom.Compare(data, old_data)) {
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
					next_st = MENU_ST_MAIN;
					break;
				case TEMPERATURE_MENU_OP_MIN:					// Temperatura minima
					temp_value = data.min_temp;
					ngn.lcd.Print(11, 1, ">");
					next_st = TEMPERATURE_ST_MIN;
					break;
				case TEMPERATURE_MENU_OP_MAX:					// Temperatura maxima
					temp_value = data.max_temp;
					ngn.lcd.Print(11, 1, ">");
					next_st = TEMPERATURE_ST_MAX;
					break;
				case TEMPERATURE_MENU_OP_LOWALARM:				// Alarma de temperatura minima
					temp_value = data.min_temp_alarm;
					ngn.lcd.Print(11, 1, ">");
					next_st = TEMPERATURE_ST_LOWALARM;
					break;
				case TEMPERATURE_MENU_OP_HIALARM:				// Alarma de temperatura minima
					temp_value = data.max_temp_alarm;
					ngn.lcd.Print(11, 1, ">");
					next_st = TEMPERATURE_ST_HIALARM;
					break;					
			}
			break;
			
		// Ajusta la temperatura minima
		case TEMPERATURE_ST_MIN:
			param_value = data.min_temp;
			if (
				SetValue(param_value, data.min_temp_alarm, (data.max_temp - 1), UNIT_GRADES) >= 0
			) {
				data.min_temp = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		// Ajusta la temperatura maxima
		case TEMPERATURE_ST_MAX:
			param_value = data.max_temp;
			if (
				SetValue(param_value, (data.min_temp + 1), data.max_temp_alarm, UNIT_GRADES) >= 0
			) {
				data.max_temp = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		// Ajusta la alarma de temperatura minima
		case TEMPERATURE_ST_LOWALARM:
			param_value = data.min_temp_alarm;
			if (
				SetValue(param_value, ABS_TEMP_MIN, data.min_temp, UNIT_GRADES) >= 0
			) {
				data.min_temp_alarm = param_value;
				next_st = MENU_ST_TEMPERATURE;
			}
			break;
			
		// Ajusta la alarma de temperatura maxima
		case TEMPERATURE_ST_HIALARM:
			param_value = data.max_temp_alarm;
			if (
				SetValue(param_value, data.max_temp, ABS_TEMP_MAX, UNIT_GRADES) >= 0
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
			r = 0;
			break;
			
			
		/***************************************
			LUZ DIURNA
		***************************************/
			
		case MENU_ST_SUNLIGHT:
			r = 0;
			break;
			
			
		/***************************************
			FECHA Y HORA
		***************************************/
			
		case MENU_ST_DATETIME:
			r = 0;
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
	} else if (ngn.input.KeyDown(KEY_DOWN_ID)) {
		// DOWN
		kb_down = true;
		auto_key_delay = 0;
	} else if (ngn.input.KeyDown(KEY_RIGHT_ID)) {
		// FORWARD
		kb_fwd = true;
		auto_key_delay = 0;		
	} else if (ngn.input.KeyDown(KEY_LEFT_ID)) {
		// BACK
		kb_back = true;
		auto_key_delay = 0;	
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
	} else {
		auto_key_delay = 0;
	}
	
}



/*** Menu principal ***/
int Menu::MenuMain() {
	
	// Resultado
	int r = -1;
	
	// Dibujado inicial?
	if (main_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, ">Setup");
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
int Menu::MenuTemperature() {
	
	// Resultado
	int r = -1;
	
	// Array con los datos actuales
	int dt[TEMPERATURE_MENU_OPTIONS] = {
		data.min_temp,
		data.max_temp,
		data.min_temp_alarm,
		data.max_temp_alarm
	};
	
	// Dibujado inicial?
	if (temperature_menu_op_last < 0) {
		ngn.lcd.Cls(0, 0, 16);
		ngn.lcd.Print(0, 0, (">" + main_menu_text[MAIN_MENU_OP_TEMPERATURE]));
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



/*** Cambia el valor de un parametro ***/
int Menu::SetValue(int &value, int min_val, int max_val, byte unit) {
	
	// Resultado
	int r = -1;
	
	// Variables de control
	bool update = false;
	
	// Control por teclado
	if (kb_up) {
		// Suma
		temp_value ++;
		if (temp_value > max_val) temp_value = max_val;
		update = true;
	} else if (kb_down) {
		// Resta
		temp_value --;
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
		ngn.lcd.Cls(12, 1, 4);
		ngn.lcd.Print(12, 1, ngn.string.Int2String(temp_value, 3));
		switch (unit) {
			case UNIT_GRADES:
				ngn.lcd.PrintChar(15, 1, CH_GRADES);
				break;
			case UNIT_PERCENT:
				ngn.lcd.Print(15, 1, "%");
				break;
		}
	}
	
	// Devuelve el resultado
	return r;
	
}
