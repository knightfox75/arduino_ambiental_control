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
	
	// Configura el led interno
	pinMode(LED_BUILTIN, OUTPUT);
		
	// Configura el display LCD
	ngn.lcd.Start();
	
	// Añade los characteres personalizados
	ngn.lcd.AddChar(0, char_off);
	ngn.lcd.AddChar(1, char_heater_on);
	ngn.lcd.AddChar(2, char_humidifier_on);
	ngn.lcd.AddChar(3, char_daylight_on);
	ngn.lcd.AddChar(4, char_arrow_down);
	ngn.lcd.AddChar(5, char_arrow_up);
	
	// Mensaje de inicio
	ngn.lcd.Print(0, 0, "Boot up...");
	
	// Carga los datos desde la SRAM
	data = eeprom.Load();
	
	// Configura los metodos de entrada
	ngn.input.Start(NUMBER_OF_KEYS);
	ngn.input.KeyAssign(SENSOR_WATER_LOW_ID, SENSOR_WATER_LOW_PIN);
	ngn.input.KeyAssign(SENSOR_WATER_EMPTY_ID, SENSOR_WATER_EMPTY_PIN);
	ngn.input.KeyAssign(KEY_UP_ID, KEY_UP_PIN);
	ngn.input.KeyAssign(KEY_DOWN_ID, KEY_DOWN_PIN);
	ngn.input.KeyAssign(KEY_LEFT_ID, KEY_LEFT_PIN);
	ngn.input.KeyAssign(KEY_RIGHT_ID, KEY_RIGHT_PIN);
	
	// Inicia el control ambiental
	ambiental.Start(data);
			
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
	ambiental.Run();			// Ejecuta el control ambiental
	ambiental.DisplayData();	// Muestra la informacion en pantalla
	
}



/*** Procesos comunes a todos los estados ***/
void Core::Common() {
	
	// Lectura de los metodos de entrada
	ngn.input.Read();
	
	// Led de actividad
	if (CORE_LED_ACTIVITY) {
		digitalWrite(LED_BUILTIN, _led_blink);
		_led_blink = !_led_blink;
	}
		
	// Test
	digitalWrite(LED_BUILTIN, ngn.input.KeyHeld(KEY_RIGHT_ID));
		
}



