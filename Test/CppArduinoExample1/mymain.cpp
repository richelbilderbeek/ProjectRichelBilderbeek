#include <wiring_digital.h>

//int main is defined in ../../Libraries/Arduino/hardware/arduino/cores/main.cpp
//so only need to implement loop and setup
void setup()
{
  pinMode(3,OUTPUT);
}

void loop()
{
  digitalWrite(3,HIGH);
  delay(1000);
  digitalWrite(3,LOW);
  delay(1000);
}
