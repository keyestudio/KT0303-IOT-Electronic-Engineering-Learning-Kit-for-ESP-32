/*  
 * Filename: 8_5_Password_Door
 * Function: Use OLED, 4x4 key pad, servo to make a simple password door
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
#include <Keypad.h>     // include Keypad library
#include <GyverOLED.h>  // include GyverOLED library for controlling OLED display
#include <ESP32Servo.h>

Servo myservo;            // create servo object to control a servo
const int Servo_Pin = 4;  // GPIO pin used to connect the servo control (digital out)

GyverOLED<SSH1106_128x64> oled;  // Create an OLED object specifying the display model SSH1106 with a resolution of 128x64

//Define keys
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 26, 25, 17, 16 };  // connect the row pins to the key pad
byte colPins[COLS] = { 27, 14, 12, 13 };  // connect the column pins to the key pad

// Initialize an instance of the myKeypad class
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234";   //save passwords
String inputPassword = "";  //save entered passwords

void setup() {
  oled.init();                      // iniitalize OLED
  oled.clear();                     // Clear the screen, making sure it is initially blank
  oled.setCursorXY(0, 0);           // Set display position
  oled.println("Enter Password:");  // Prompt character
  oled.update();                    //Refresh display

  myservo.attach(Servo_Pin);  //attaches the servo on pin to the servo object
  myservo.write(0);           // Set the servo to 0 degrees
  delay(1000);                // delay 1s
}

void loop() {
  // Get character input
  char keyPressed = myKeypad.getKey();
  // If any characters are entered, send them to the serial port
  if (keyPressed) {
    Serial.println(keyPressed);

    //validate password
    if (keyPressed == '#') {
      if (inputPassword == password) {        //Check whether the entered password is correct
        oled.clear();                         //Clear OLED display
        oled.setCursorXY(0, 0);               // Set display position
        oled.println("Correct! Opening...");  //Password correct door opening prompt
        oled.update();                        //Refresh display
        myservo.write(180);                   //set servo to 180degree, open the door
        delay(2000);                          //delay 2s
        myservo.write(0);                     // set servo to 0degree, close the door
        inputPassword = "";                   // Clear input password
      } else {                                //If the password entered is incorrect, execute the following code
        oled.clear();
        oled.setCursorXY(0, 0);
        oled.println("Wrong! Try again.");  //Incorrect password prompt
        oled.update();
        inputPassword = "";
      }
      delay(1000);  //After judging the correctness of the password, OLED recovers the password prompt
      oled.clear();
      oled.setCursorXY(0, 0);
      oled.println("Enter Password:");
      oled.update();
    } else if (keyPressed == '*') {  //If you enter the wrong password, press the * key to clear and re-enter
      inputPassword = "";
      oled.clear();
      oled.setCursorXY(0, 0);
      oled.println("Enter Password:");
      oled.update();
    } else {  //If the input key is not '#' and '*', it means to enter the password again

      if (inputPassword.length() < 4) {  //Check whether the number of entered passwords is smaller than four
        inputPassword += keyPressed;     //Put all entered passwords in the variable inputPassword
        oled.clear();
        oled.setCursorXY(0, 0);
        oled.println("Enter Password:");
        oled.setCursorXY(0, 20);
        oled.println(inputPassword);  //Display the entered password
        oled.update();
      }
    }
  }
}