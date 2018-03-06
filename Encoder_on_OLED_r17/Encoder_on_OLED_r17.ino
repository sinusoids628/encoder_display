//=========================HEADER=============================================================
/*
   Try to remove code for second encoder
   
   Dual LS7366 Quadrature Counter Test Code
   AUTHOR: Jason Traud
   DATE: June 22, 2013
   
   This is a simple test program to read encoder counts
   collected by the LS7366 breakout board. The counts are
   then displayed in the Arduino's serial monitor at a 
   baud rate of 9600
   
   Hardware: Arduino Uno R3
   Powered 
   
   LS7366 Breakout    -------------   Arduino
   -----------------                    -------
            MOSI   -------------------   SDO (D11)
            MISO   -------------------   SDI (D12)
            SCK    -------------------   SCK (D13)
            SS1    -------------------   SS1 (D7)
            SS2    -------------------   SS2 (D8)
            GND    -------------------   GND
            VDD    -------------------   VCC (5.0V)

            5 Mar 2018  IMR changed DIO to accomodate encoder and switch
 
  The circuit:
 * LCD RS pin to digital pin 8
 * LCD R/W pin to digital pin 9
 * LCD Enable pin to digital pin 10
 * LCD D4 pin to digital pin 2
 * LCD D5 pin to digital pin 3
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 5

			
   License: CCAv3.0 Attribution-ShareAlike (http://creativecommons.org/licenses/by-sa/3.0/)
   You're free to use this code for any venture. Attribution is greatly appreciated. 

//============================================================================================
*/

// Inclde the standard Arduino SPI Library, please ensure the SPI pins are
// connected properly for your Arduino version
#include <SPI.h>

// include the library code:
#include <Adafruit_CharacterOLED.h>

// initialize the library with the OLED hardware 
// version OLED_Vx and numbers of the interface pins. 
// OLED_V1 = older, OLED_V2 = newer. If 2 doesn't work try 1 ;)

Adafruit_CharacterOLED lcd(OLED_V2, 8, 9, 10, 2, 3, 4, 5);

// Slave Select pins for encoder
// Feel free to reallocate these pins to best suit your circuit

const int slaveSelectEnc1 = 7;

// This holds the current encoder count.

signed long encoder1count = 0;
const int zeroPin = 1;     // the number of the pushbutton pin
int zeroState = 0;         // variable for reading the zero status


void initEncoders() {
  
  // Set slave selects as outputs
  pinMode(slaveSelectEnc1, OUTPUT);
  
  // Raise select pin
  // Communication begins when you drop the individual select pin
  digitalWrite(slaveSelectEnc1,HIGH);
  
  SPI.begin();

  // NOTE: For more information on commands, see datasheet
  digitalWrite(slaveSelectEnc1,LOW);        // Begin SPI conversation
  SPI.transfer(0x88);                       // Write to MDR0
  SPI.transfer(0x01);                       // Configure to X1 count / quadrature cycle 
  digitalWrite(slaveSelectEnc1,HIGH);       // Terminate SPI conversation 

}

long readEncoder(int encoder) {
  
  // Initialize temporary variables for SPI read
  unsigned int count_1, count_2, count_3, count_4;
  long count_value;  
  
  // Read encoder 

    digitalWrite(slaveSelectEnc1,LOW);      // Begin SPI conversation
    SPI.transfer(0x60);                     // Request count
    count_1 = SPI.transfer(0x00);           // Read highest order byte
    count_2 = SPI.transfer(0x00);           
    count_3 = SPI.transfer(0x00);           
    count_4 = SPI.transfer(0x00);           // Read lowest order byte
    digitalWrite(slaveSelectEnc1,HIGH);     // Terminate SPI conversation 
  
 
  
  // Calculate encoder count
  count_value = (count_1 << 8) + count_2;
  count_value = (count_value << 8) + count_3;
  count_value = (count_value << 8) + count_4;
  
  return count_value;
}

void clearEncoderCount() {
    
  // Set encoder1's data register to 0
  digitalWrite(slaveSelectEnc1,LOW);      // Begin SPI conversation  
  // Write to DTR
  SPI.transfer(0x98);    
  // Load data
  SPI.transfer(0x00);  // Highest order byte
  SPI.transfer(0x00);           
  SPI.transfer(0x00);           
  SPI.transfer(0x00);  // lowest order byte
  digitalWrite(slaveSelectEnc1,HIGH);     // Terminate SPI conversation 
  
  delayMicroseconds(100);  // provides some breathing room between SPI conversations
  
  // Set encoder1's current data register to center
  digitalWrite(slaveSelectEnc1,LOW);      // Begin SPI conversation  
  SPI.transfer(0xE0);    
  digitalWrite(slaveSelectEnc1,HIGH);     // Terminate SPI conversation   

}


void setup() {
  // Print a message to the LCD.
  lcd.begin(16, 2);
  
 initEncoders();       lcd.println("Encoder ZERO");  
 delay(1000);
 lcd.setCursor(1,1);  
 delay(1000);
 clearEncoderCount();  lcd.println("Encoder Cleared");
 delay(1000);

  // Print a message to the LCD.
  lcd.begin(16, 2);
  lcd.print("  IMR EncodeR    ");
  
  // initialize the zero input as an input:
    pinMode(zeroPin, INPUT);
}

void loop() {

// read the state of the pushbutton value:
  zeroState = digitalRead(zeroPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (zeroState == LOW) {
    // zero encoder:

 lcd.setCursor(0,1);  
 lcd.clear();
 lcd.setCursor(1,1);  
 lcd.clear();
 
  initEncoders();       lcd.println("Encoder ZERO");  
 delay(1000);
 lcd.setCursor(1,1);  
 delay(1000);
  clearEncoderCount();  lcd.println("Encoder Cleared");
 delay(1000);

 lcd.setCursor(0,1);  
 lcd.clear();
 lcd.setCursor(1,1);  
 lcd.clear();
   
  } else {
    // display most recent encoder position:
 
  
  
 delay(500);
 
 // Retrieve current encoder counter
 encoder1count = readEncoder(1); 
 

   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 
 lcd.setCursor(0, 0); 
 lcd.print("Encoder Position"); 
 lcd.setCursor(0, 1); 
 lcd.print("Counts: "); lcd.println(encoder1count);  
 }
}

