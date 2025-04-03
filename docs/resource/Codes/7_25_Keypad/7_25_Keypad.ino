/*  
 * Filename   : 7_25_Keypad
 * Function   : read thin film 4*4 key pad values
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
#include <Keypad.h> // include Keypad library

//Defines symbols of keys
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {26, 25, 17, 16}; // set pins of rows
byte colPins[COLS] = {27, 14, 12, 13};   // set pins of columns

//Initialize an instance of the myKeypad class
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600); // set baud rate to 9600
  Serial.println("ESP32 is ready!");  // print “ESP32 is ready!”
}

void loop() {
  // Get character input
  char keyPressed = myKeypad.getKey();
  // If there is any character input, it is sent to the serial port
  if (keyPressed) {
    Serial.println(keyPressed);
  }
}