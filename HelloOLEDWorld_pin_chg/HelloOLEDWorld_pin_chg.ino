/*
 Based on the LiquidCrystal Library - Hello World
 
 Demonstrates the use a Winstar 16x2 OLED display.  These are similar, but
 not quite 100% compatible with the Hitachi HD44780 based LCD displays. 
 
 This sketch prints "Hello OLED World" to the LCD
 and shows the time in seconds since startup.

 5 Mar 2018  IMR changed DIO to accomodate encoder and switch
 
  The circuit:
 * LCD RS pin to digital pin 8
 * LCD R/W pin to digital pin 9
 * LCD Enable pin to digital pin 10
 * LCD D4 pin to digital pin 2
 * LCD D5 pin to digital pin 3
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 5

 There is no need for the contrast pot as used in the LCD tutorial
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 Library & Example Converted for OLED
 by Bill Earl 30 Jun 2012
 
 This example code is in the public domain.
 */

// include the library code:
#include <Adafruit_CharacterOLED.h>

// initialize the library with the OLED hardware 
// version OLED_Vx and numbers of the interface pins. 
// OLED_V1 = older, OLED_V2 = newer. If 2 doesn't work try 1 ;)
Adafruit_CharacterOLED lcd(OLED_V2, 8, 9, 10, 2, 3, 4, 5);

void setup() 
{
  // Print a message to the LCD.
  lcd.begin(16, 2);
  lcd.print("  IMR EnCodeR  ");
}

void loop() 
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(3, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}
