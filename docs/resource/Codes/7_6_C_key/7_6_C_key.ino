/*
 * Filename   : 7_6_C_key 
 * Function   : passive buzzer plays Do，Re，Mi，Fa，So，La，Si in tone C
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Buzzer_Pine = 13; //set buzzer pin to IO13
void setup() {
  pinMode(Buzzer_Pine, OUTPUT);//set IO13 to output
}

void loop() {
  tone(Buzzer_Pine, 262);//Flat DO played for 500ms
  delay(500);
  tone(Buzzer_Pine, 294);//Flat Re played for 500ms
  delay(500);
  tone(Buzzer_Pine, 330);//Flat Mi played for 500ms
  delay(500);
  tone(Buzzer_Pine, 349);//Flat Fa played for 500ms
  delay(500);
  tone(Buzzer_Pine, 392);//Flat So played for 500ms
  delay(500);
  tone(Buzzer_Pine, 440);//Flat La played for 500ms
  delay(500);
  tone(Buzzer_Pine, 494);//Flat Si played for 500ms
  delay(500);
  noTone(Buzzer_Pine);//stop for 1s
  delay(1000);
}