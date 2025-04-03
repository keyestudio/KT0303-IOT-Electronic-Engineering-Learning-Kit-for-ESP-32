/*  
 * Filename   : 7_20_Read_Joystick
 * Function   : read joystick values
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
int VRX_Pin = 36;  //set X axis pin to IO36
int VRY_Pin = 39;  //set Y axis pin to IO39
int SW_Pin = 26;    //set B axis pin to IO26

int xPosition = 0;  //set variable xPosition initial value to 0
int yPosition = 0;  //set variable yPosition initial value to 0
int SW_state = 0;  //set variable SW_state initial value to 0

void setup() {
Serial.begin(9600); 
pinMode(VRX_Pin, INPUT);  //X axis pin to input
pinMode(VRY_Pin, INPUT);  //Y axis pin to input
pinMode(SW_Pin, INPUT_PULLUP);   //Z axis pin to input pull-up
}

// In loop(), use analogRead() to read the X-axis and Y-axis values, and use digitalRead() to read the Z-axis values, and then display them.
void loop() {
  xPosition = analogRead(VRX_Pin); 
  yPosition = analogRead(VRY_Pin);
  SW_state = digitalRead(SW_Pin);
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  delay(100);
}