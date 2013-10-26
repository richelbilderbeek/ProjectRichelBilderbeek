
const int pin_1 = 2;
const int pin_2 = 3;
const int pin_3 = 4;
const int pin_4 = 5;

void setup()
{
  pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
  pinMode(pin_3,OUTPUT);
  pinMode(pin_4,OUTPUT);
  
}

void loop()
{
  const int my_delay = 10000;
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_2,LOW);
  digitalWrite(pin_4,HIGH);
  digitalWrite(pin_3,HIGH); //Never make 3 high when 4 is ground

  delay(my_delay);
  digitalWrite(pin_2,HIGH);
  digitalWrite(pin_3,LOW);
  digitalWrite(pin_4,LOW);
  digitalWrite(pin_1,HIGH); //Never make 1 high, when 2 is low
  delay(my_delay);
}
