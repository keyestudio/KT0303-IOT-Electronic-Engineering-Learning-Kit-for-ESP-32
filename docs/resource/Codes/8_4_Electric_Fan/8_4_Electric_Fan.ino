/*  
 * Filename: 8_4_Electric_Fan
 * Function: Make a simple electric fan using relay, buttons, motor, and fan
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Relay_Pin = 12;  // set relay pin to IO12

const int Red_Button_Pin = 18;    // set red button pin to IO12
const int Green_Button_Pin = 19;  // set green button pin to IO12

bool Red_Button_State = true;    //store red button state value
bool Green_Button_State = true;  //store green button state value

void setup() {
  pinMode(Red_Button_Pin, INPUT);    // set red button pin to input 
  pinMode(Green_Button_Pin, INPUT);  // set green button pin to input 
  pinMode(Relay_Pin, OUTPUT);        // set relay pin to output

  digitalWrite(Relay_Pin, LOW);  // set relay initial state to off
}
void loop() {

  Red_Button_State = digitalRead(Red_Button_Pin);      //read red button state
  Green_Button_State = digitalRead(Green_Button_Pin);  //read green button state

  if (Red_Button_State == false) {           //determine whether the red button is pressed
    digitalWrite(Relay_Pin, LOW);            //turn relay NO on, fan stops
  } else if (Green_Button_State == false) {  //determine whether the green button is pressed
    digitalWrite(Relay_Pin, HIGH);           //turn relay NO off, fan rotates
  }
  delay(100);  //delay 100ms
}
