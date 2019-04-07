/*******************************************************************************

	Control ambiental
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com
	
	Control del display LCD

*******************************************************************************/



/*** Includes ***/
// Includes del proyecto
#include "lcd.h"



/*** Constructor ***/
Lcd::Lcd() {	
}



/*** Destructor ***/
Lcd::~Lcd() {
}



/*** Configura el display ***/
void Lcd::Start() {
	
	// Configura el display con los parametros
	lcd.begin(LCD_ROWS, LCD_COLUMNS);
	// Borra el contenido del display
	Cls();
	
}



/*** Imprime un texto ***/
void Lcd::Print(String txt) {
	
	lcd.print(txt);
	
}



/*** Imprime un texto ***/
void Lcd::Print(unsigned int x, unsigned int y, String txt) {
	
	lcd.setCursor(x, y);
	lcd.print(txt);
	
}


/*** Imprime un caracter especial ***/
void Lcd::PrintChar(unsigned int x, unsigned int y, byte b) {
	
	lcd.setCursor(x, y);
	lcd.write(byte(b));
	
}



/*** Borra la pantalla ***/
void Lcd::Cls() {
	
	lcd.clear();
	
}



/*** Borra una parte de la pantalla ***/
void Lcd::Cls(unsigned int x, unsigned int y, unsigned int length) {
	
	String txt = String("");
	
	for (unsigned int i = x; i < (x + length); i ++) txt += String(" ");
	Print(x, y, txt);
	
}



/*** Añade un caracter personalizado ***/
void Lcd::AddChar(int id, byte character[]) {
	lcd.createChar(id, character);
}