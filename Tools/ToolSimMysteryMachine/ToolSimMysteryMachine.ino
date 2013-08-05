const int rot_pin_1_1 = 2;
const int rot_pin_1_2 = 3;
const int rot_pin_1_3 = 4;
const int rot_pin_2_1 = 5;
const int rot_pin_2_2 = 6;
const int rot_pin_2_3 = 7;
const int led_pin_1_1 = 8;
const int led_pin_1_2 = 9;
const int led_pin_1_3 = 10;
const int led_pin_2_1 = 11;
const int led_pin_2_2 = 12;
const int led_pin_2_3 = 13;
const int led_pin_3_1 = 14;
const int led_pin_3_2 = 15;
const int led_pin_3_3 = 16;

void setup()
{
  pinMode(rot_pin_1_1,INPUT);
  pinMode(rot_pin_1_2,INPUT);
  pinMode(rot_pin_1_3,INPUT);
  pinMode(rot_pin_2_1,INPUT);
  pinMode(rot_pin_2_2,INPUT);
  pinMode(rot_pin_2_3,INPUT);
  pinMode(led_pin_1_1,OUTPUT);
  pinMode(led_pin_1_2,OUTPUT);
  pinMode(led_pin_1_3,OUTPUT);
  pinMode(led_pin_2_1,OUTPUT);
  pinMode(led_pin_2_2,OUTPUT);
  pinMode(led_pin_2_3,OUTPUT);
  pinMode(led_pin_3_1,OUTPUT);
  pinMode(led_pin_3_2,OUTPUT);
  pinMode(led_pin_3_3,OUTPUT);
}

void loop()
{
  digitalWrite(led_pin_1_1, HIGH);
  digitalWrite(led_pin_1_2, HIGH);
  digitalWrite(led_pin_1_3, HIGH);

  //digitalWrite(led_pin_1_1, digitalRead(rot_pin_1_1));
  //digitalWrite(led_pin_1_2, digitalRead(rot_pin_1_2));
  //digitalWrite(led_pin_1_3, digitalRead(rot_pin_1_3));

  /*
  const int player_1 
    = ((digitalRead(rot_pin_1_1) == HIGH ? 0 : 0)
    + (digitalRead(rot_pin_1_2) == HIGH ? 1 : 0)
    + (digitalRead(rot_pin_1_3) == HIGH ? 2 : 0))
    % 3;
  */
  /*
  static int player_1 = 0;
  player_1 = (++player_1) % 3;
  digitalWrite(led_pin_1_1, player_1 == 0 ? HIGH : LOW);
  digitalWrite(led_pin_1_2, player_1 == 1 ? HIGH : LOW);
  digitalWrite(led_pin_1_3, player_1 == 2 ? HIGH : LOW);
  delay(100);
  */
}
  
