/*

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int led_pin = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
}

void loop()
{
  String content = "";
  while(Serial.available())
  {
    const char character = Serial.read();
    content.concat(character);
  }

  if (content != "")
  {
    const int brightness = content.toInt();
    lcd.clear();
    lcd.setCursor(0,0);
    analogWrite(led_pin, brightness);
    lcd.print(brightness);
  }

  delay(100);
}

*/
#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Dialog w;
  w.show();  
  return a.exec();
}
