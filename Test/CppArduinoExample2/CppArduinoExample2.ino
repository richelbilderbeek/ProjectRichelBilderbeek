#include "Arduino.h"
#include "LiquidCrystal.h"

const int ms_pin_rs =  6 ; //Arduino pin that connects to R/S pin of LCD display
const int ms_pin_e  =  7; //Arduino pin that connects to E   pin of LCD display
const int ms_pin_d4 =  8; //Arduino pin that connects to D4  pin of LCD display
const int ms_pin_d5 =  A5; //Arduino pin that connects to D5  pin of LCD display
const int ms_pin_d6 =  A2; //Arduino pin that connects to D6  pin of LCD display
const int ms_pin_d7 =  A3; //Arduino pin that connects to D7  pin of LCD display

const int ms_pin_v0 =  5; //Arduino pin that connects to V0  pin of LCD display

const int ms_pin_thermistor = A0;
LiquidCrystal lcd(
      ms_pin_rs,
      ms_pin_e,
      ms_pin_d4,
      ms_pin_d5,
      ms_pin_d6,
      ms_pin_d7
    );

void setup()
{
  pinMode(ms_pin_thermistor,INPUT);
  lcd.begin(20,2);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  const int thermistor = analogRead(ms_pin_thermistor);
  lcd.print(thermistor);
  lcd.setCursor(0,1);
  const int time = millis();
  lcd.print(time);
  delay(100);
}
