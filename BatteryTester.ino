/*
A battery life cycle tester using an Lcd as output  
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int buttonPin = 9; 
int sensorPin = A0;    // select the input pin for the Battery
int sensorValue = 0;  // variable to store the value coming from the sensor
const int relay= 10;
int buttonState = 0;
float mah = 0.0;
long timestart  ;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Batt life tester");
  pinMode(relay, OUTPUT);
pinMode(buttonPin, INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  digitalWrite(relay, 0 ); //set the LED-relay off
 
  while (buttonState == LOW ) {
  sensorValue = analogRead(sensorPin); // read the battery
  
  buttonState = digitalRead(buttonPin);

  lcd.setCursor(0, 1);
  lcd.print((sensorValue*4.98)/1023);
  lcd.print(" Volts");
  delay(500);
  } //end get ready loop 
  digitalWrite(relay, 1 ); //set the LED-relay on
  lcd.setCursor(0, 0);
  lcd.print("Testing              ");
  lcd.setCursor(0, 1);
  lcd.print("                         ");
  mah = 0.0;
  timestart = millis( );
  while ( ((sensorValue*4.98)/1023) > 3.00 ) {
     lcd.setCursor(0, 1);    
     lcd.print((sensorValue*4.98)/1023);
     lcd.print(" V ");
     sensorValue = analogRead(sensorPin); // read the battery
     mah = mah + (((sensorValue*4.98)/1023)/4 )/7.2;
     lcd.print(mah);
     lcd.print(" mAh ");
     delay ( 500 ) ;
     lcd.setCursor(8,0);
     lcd.print((millis( )- timestart)/1000); // time since test staarted
  } // end battery drain
    digitalWrite(relay, 0 ); //set the LED-relay off

  // final results
 
   lcd.setCursor(0, 0);
   lcd.print(mah);
   lcd.print(" mAH ");
   lcd.print((millis( )- timestart)/1000);
   lcd.print(" S ");
   buttonState = digitalRead(buttonPin);
  
}
