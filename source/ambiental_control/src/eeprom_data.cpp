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
	
	Gestion de datos en la EEPROM

*******************************************************************************/



/*** Includes ***/
// Includes del proyecto
#include "eeprom_data.h"



/*** Contructor ***/
EepromData::EepromData() {
}



/*** Destructor ***/
EepromData::~EepromData() {
}



/*** Carga los datos desde la SRAM ***/
Eeprom_d EepromData::Load() {
	
	// Carga los datos desde la EEPROM
	Eeprom_d data = Read();
	
	// Calcula el checksum
	unsigned int checksum = CheckSum(data);
	
	// Si el checksum difiere
	if (checksum != data.checksum) {
		
		// Vacia la EEPROM
		EraseEeprom();
		// Carga los valores por defecto
		data = DefaultValues();
		// Guarda los datos
		Write(data);
		
	}
	
	// Devuelve los datos
	return data;
	
}



/*** Guarda los datos a la SRAM ***/
void EepromData::Save(Eeprom_d data) {
	
	Write(data);
	
}



/*** Valores por defecto ***/
Eeprom_d EepromData::DefaultValues() {
	
	// Estructura de datos
	Eeprom_d data;
	
	// Datos predefinidos
	data.min_temp = TEMP_MIN_TRIGGER;
	data.max_temp = TEMP_MAX_TRIGGER;
	data.min_temp_alarm = TEMP_MIN_ALARM;
	data.max_temp_alarm = TEMP_MAX_ALARM;
	data.min_humi = HUMIDITY_MIN_TRIGGER;
	data.max_humi = HUMIDITY_MAX_TRIGGER;
	data.min_humi_alarm = HUMIDITY_MIN_ALARM;
	data.max_humi_alarm = HUMIDITY_MAX_ALARM;
	data.sunrise_hour = SUNRISE_HOUR;
	data.sunrise_minute = SUNRISE_MINUTE;
	data.sunset_hour = SUNSET_HOUR;
	data.sunset_minute = SUNSET_MINUTE;
	data.alarm_buzzer = BUZZER_ALARM;
	
	// Devuelve la estructura
	return data;
	
}



/*** Genera el CheckSum ***/
unsigned int EepromData::CheckSum(Eeprom_d data) {
	
	return (
		data.min_temp
		+
		data.max_temp
		+
		data.min_temp_alarm
		+
		data.max_temp_alarm
		+
		data.min_humi
		+
		data.max_humi
		+
		data.min_humi_alarm
		+
		data.max_humi_alarm
		+
		data.sunrise_hour
		+
		data.sunrise_minute
		+
		data.sunset_hour
		+
		data.sunset_minute
		+
		data.alarm_buzzer
	);
	
}



/*** Vacia la EEPROM ***/
void EepromData::EraseEeprom() {
	
	for (unsigned int i = 0; i < EEPROM.length(); i ++) EEPROM.write(i, 0);
	
}



/*** Lee la EEPROM ***/
Eeprom_d EepromData::Read() {
	
	Eeprom_d data;
	unsigned int addr = 0;
	
	EEPROM.get(addr, data);
	
	return data;
	
}


/*** Escribe la EEPROM ***/
void EepromData::Write(Eeprom_d data) {
	
	unsigned int addr = 0;
	
	// Calcula el checksun
	data.checksum = CheckSum(data);
	
	// Escribe la los datos
	EEPROM.put(addr, data);
	
}



