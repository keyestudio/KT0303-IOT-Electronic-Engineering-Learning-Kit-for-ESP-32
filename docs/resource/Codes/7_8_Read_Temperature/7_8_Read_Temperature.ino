/*  
 * Filename   : 7_8_Read_Temperature
 * Function   : Read the value of LM35D and calculate the temperature value through the formula
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/

const int LM35_Pin = 36;  //set lm35 pin to GPIO36
float temperature = 0;    //set variable temperature initial value to 0
long value = 0;           //set variable value initial value to 0

/*
  5.0 : the input voltage of LM35D 5V
  4095.0 ：4095 is the maximum ADC (analog-to-digital converter) of the ESP32 at 12-bit resolution
  Interger number adds a decimal part because we want to preserve the value of the decimal part
  If both values are integers, the system ignores the decimal part of the value and keeps only the integer part
*/
float constant = 5.0 / 4095.0;  //Set the analog value constant for the calculated temperature

void setup() {
  Serial.begin(9600);        //set baud rate to 9600
  pinMode(LM35_Pin, INPUT);  //set LM35_Pin to intput
}

void loop() {
  value = analogRead(LM35_Pin);  // read analog input
  temperature = (value * constant * 100);  // calculate analog temperature value
  //print temperature value
  Serial.print("Temper =  ");
  Serial.print(temperature);
  Serial.println("℃");
  delay(1000);
}