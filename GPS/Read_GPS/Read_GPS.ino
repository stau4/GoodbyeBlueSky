//#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>

#include "TinyGPS.h"

TinyGPS gps;

int unoRxPin = 6; // connected to Tx pin of the GPS
int unoTxPin = 7; // connected to Rx pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);

//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
//int backLight = 13;    // pin 13 will control the backlight

long startMillis;
long secondsToFirstLocation = 0;

void setup()
{
  ss.begin(9600);
  
//  pinMode(backLight, OUTPUT);
//  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
//  lcd.begin(20,4); // columns, rows.  use 16,2 for a 16x2 LCD, etc.
//  lcd.clear();  // start with a blank screen
  
  startMillis = millis();
}

void loop()
{
  bool newData = false;
  unsigned long chars = 0;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      int c = ss.read();
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    // we have a location fix so output the lat / long and time to acquire
    if(secondsToFirstLocation == 0){
      secondsToFirstLocation = (millis() - startMillis) / 1000;
    }
    
//    lcd.clear();  // start with a blank screen
    
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
//    lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
//    lcd.print("Lat=");
//    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

//    lcd.setCursor(0,1);
//    lcd.print("Long=");
//    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);

//    lcd.setCursor(0,2);
//    lcd.print("Acquire Time=");
//    lcd.print(secondsToFirstLocation);
//    lcd.print("s");
  }
  
  if (chars == 0){
    // if you haven't got any chars then likely a wiring issue
//    lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
//    lcd.print("No GPS: check wiring");
  }
  else if(secondsToFirstLocation == 0){
    // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
//    lcd.clear();  // start with a blank screen

    long seconds = (millis() - startMillis) / 1000;
    
//    lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
//    lcd.print("Searching ");
    for(int i = 0; i < seconds % 4; ++i){
//      lcd.print(".");
    }
    
//    lcd.setCursor(0,1);
//    lcd.print("Elapsed time:");
//    lcd.print(seconds);
//    lcd.print("s");
  }
}
