/* Upload this code to the Arduino:

const int pin_read = A0;
const int read_every_msec = 100;

void setup() {
  Serial.begin(9600);
}

void loop() {
  const int sensorValue = analogRead(pin_read);
  Serial.println(sensorValue);
  delay(read_every_msec);
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
