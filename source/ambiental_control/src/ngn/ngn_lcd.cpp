/*******************************************************************************

	N'gine para Arduino
	Ver 0.0.1-a
	
	Proyecto iniciado el 05-04-2019
	
	(cc) 2019 por Cesar Rincon
	
	http://www.nightfoxandco.com
	contact@nightfoxandco.com

	N'gine para Arduino se distribuye bajo la licencia CREATIVE COMMONS
	"Attribution-NonCommercial 4.0 International"
	https://creativecommons.org/licenses/by-nc/4.0/
	
	Control del display LCD

*******************************************************************************/



/*** Includes ***/
// Includes de N'gine
#include "ngn_lcd.h"



/*** Constructor ***/
NGN_Lcd::NGN_Lcd() {	
}



/*** Destructor ***/
NGN_Lcd::~NGN_Lcd() {
}



/*** Configura el display ***/
void NGN_Lcd::Start() {
	
	// Configura el display con los parametros
	display.begin(LCD_ROWS, LCD_COLUMNS);
	
	// Borra el contenido del display
	Cls();
	
}



/*** Imprime un texto ***/
void NGN_Lcd::Print(String txt) {
	
	display.print(txt);
	
}



/*** Imprime un texto ***/
void NGN_Lcd::Print(U8 x, U8 y, String txt) {
	
	display.setCursor(x, y);
	display.print(txt);
	
}


/*** Imprime un caracter especial ***/
void NGN_Lcd::PrintChar(U8 x, U8 y, U8 b) {
	
	display.setCursor(x, y);
	display.write(byte(b));
	
}



/*** Borra la pantalla ***/
void NGN_Lcd::Cls() {
	
	display.clear();
	
}



/*** Borra una parte de la pantalla ***/
void NGN_Lcd::Cls(U8 x, U8 y, U8 length) {
	
	String txt = "";
	
	for (U8 i = x; i < (x + length); i ++) txt += " ";
	Print(x, y, txt);
	
}



/*** Añade un caracter personalizado ***/
void NGN_Lcd::AddChar(U8 id, const U8* character) {
	
	display.createChar(id, (U8*)character);
	
}