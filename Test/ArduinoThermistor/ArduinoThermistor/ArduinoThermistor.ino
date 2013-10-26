#include <LiquidCrystal.h>

// 5V
// |
// thermistor
// |
// +---- pin
// |
// GND
const int pin_thermistor = A0;


//OpenPCR defaults. Note: pin 16 and 17 don't exist!
//iLcd(6, 7, 8, A5, 16, 17),
const int pin_lcd_rs =  3; //Arduino pin that connects to R/S pin of LCD display
const int pin_lcd_e  =  4; //Arduino pin that connects to E   pin of LCD display
const int pin_lcd_d4 =  5; //Arduino pin that connects to D4  pin of LCD display
const int pin_lcd_d5 =  6; //Arduino pin that connects to D5  pin of LCD display
const int pin_lcd_d6 =  7; //Arduino pin that connects to D6  pin of LCD display
const int pin_lcd_d7 =  8; //Arduino pin that connects to D7  pin of LCD display



LiquidCrystal lcd(
  pin_lcd_rs,
  pin_lcd_e,
  pin_lcd_d4,
  pin_lcd_d5,
  pin_lcd_d6,
  pin_lcd_d7);


void setup ()
{
  pinMode(pin_thermistor,INPUT);
  lcd.begin(16,2);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  const int value = analogRead(pin_thermistor);
  const double f = static_cast<double>(value) / 1024.0;
  lcd.print(f * 5.0);
  delay(100);
}
