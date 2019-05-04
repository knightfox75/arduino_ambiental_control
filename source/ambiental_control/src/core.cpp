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
	
	Nucleo de Ejecucion

*******************************************************************************/



/*** Includes ***/
// Includes del proyecto
#include "core.h"



/*** Constructor ***/
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
	
	// Configura el led de actividad
	pinMode(CORE_LED_PIN, OUTPUT);
		
	// Configura el display LCD
	ngn.lcd.Start();
	
	// Añade los characteres personalizados
	ngn.lcd.AddChar(CH_OFF, CHAR_OFF);
	ngn.lcd.AddChar(CH_HEATER_ON, CHAR_HEATER_ON);
	ngn.lcd.AddChar(CH_HUMIDIFIER_ON, CHAR_HUMIDIFIER_ON);
	ngn.lcd.AddChar(CH_DAYLIGHT_ON, CHAR_DAYLIGHT_ON);
	ngn.lcd.AddChar(CH_ARROW_DOWN, CHAR_ARROW_DOWN);
	ngn.lcd.AddChar(CH_ARROW_UP, CHAR_ARROW_UP);
	ngn.lcd.AddChar(CH_GRADES, CHAR_GRADES);
	
	// Mensaje de inicio
	ngn.lcd.Print(0, 0, "Starting...");
	
	// Carga los datos desde la SRAM
	data = eeprom.Load();
	
	// Configura los metodos de entrada
	ngn.input.Start(NUMBER_OF_KEYS);
	ngn.input.KeyAssign(KEY_UP_ID, KEY_UP_PIN);
	ngn.input.KeyAssign(KEY_DOWN_ID, KEY_DOWN_PIN);
	ngn.input.KeyAssign(KEY_LEFT_ID, KEY_LEFT_PIN);
	ngn.input.KeyAssign(KEY_RIGHT_ID, KEY_RIGHT_PIN);
	ngn.input.KeyAssign(KEY_A_ID, KEY_A_PIN);
	ngn.input.KeyAssign(KEY_B_ID, KEY_B_PIN);
	
	// Inicia el control ambiental
	ambiental.Start(data);
	
	// Configura la maquina de estados
	st = next_st = ST_START_AMBIENTAL;
			
}



/*** Ejecuta el programa ***/
void Core::Run() {
	
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
	
	// Maquina de estados
	switch (st) {
		
		case ST_START_AMBIENTAL:
			ambiental.UpdateData(data);		// Actualiza la informacion
			next_st = ST_RUN_AMBIENTAL;		// Siguiente estado
			break;
		
		case ST_RUN_AMBIENTAL:
			ambiental.DisplayData();		// Muestra la informacion en pantalla
			// Si se pulsa la tecla RIGHT, ve al menu
			if (ngn.input.KeyDown(KEY_RIGHT_ID)) {
				next_st = ST_START_MENU;
			}
			break;
			
		case ST_START_MENU:
			menu.Start(data);
			next_st = ST_RUN_MENU;
			break;
			
		case ST_RUN_MENU:
			if (menu.Run() >= 0) {
				data = menu.GetData();
				next_st = ST_START_AMBIENTAL;
			}
			break;
		
	}
	st = next_st;
		
}



/*** Procesos comunes a todos los estados ***/
void Core::Common() {
	
	// Lectura de los metodos de entrada
	ngn.input.Read();
	
	// Ejecuta el control ambiental
	ambiental.Run();
	
	// Led de actividad
	if (CORE_LED_ACTIVITY) {
		digitalWrite(CORE_LED_PIN, _led_blink);
		_led_blink = !_led_blink;
	}
				
}



