/*  
 * Filename: 8_1_Table_Lamp
 * Function: Use IR remote control and button to realize dual control LED
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
#include <IRremote.hpp>  // Import IRremote library

#define DECODE_NEC  // Only enable the NEC protocol

const int IR_Pin = 5;       //set ir receiver pin to IO5
const int Button_Pin = 14;  //set button pin to IO14
const int LED_Pin = 23;     //set LED pin to IO23

long IR_Value = 0;          //save remote control key values
bool Button_State = false;  //save button state, true: button is pressed, false: button is released
bool LED_State = false;     //save led states, false: LED off, true: LED on

void setup() {
  Serial.begin(9600);  // set baud rate

  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);  // Initiate reception using pin IO5
  pinMode(Button_Pin, INPUT);                     //Set the button pin to input
  pinMode(LED_Pin, OUTPUT);                       //Set led pin to output
}

void loop() {
  if (IrReceiver.decode()) {  // Detects whether an infrared signal is received
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      // Print the received key value (command value) and convert it to decimal
      IR_Value = IrReceiver.decodedIRData.command;
      //Check whether the key value is equal to 64. If so, reverse LED_State
      if (IR_Value == 64) {
        LED_State = !LED_State;
        delay(200);
      }
    }
    IrReceiver.resume();  // Stand by to receive the next infrared signal
  }
  Button_State = digitalRead(Button_Pin);  //Read key status
  if (Button_State == false) {             //Determine whether the button is pressed
    LED_State = !LED_State;                //reverse LED_State
    while (!digitalRead(Button_Pin))       //Use the While loop to prevent the led light from flashing while the key is being pressed
      ;
  }
  digitalWrite(LED_Pin, LED_State);  //control LED on/off
  delay(50); //delay 50ms
}
