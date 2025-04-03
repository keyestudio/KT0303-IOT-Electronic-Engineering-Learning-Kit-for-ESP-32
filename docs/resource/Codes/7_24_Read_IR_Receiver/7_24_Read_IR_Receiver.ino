/*  
 * Filename   : 7_24_Read_IR_Receiver
 * Function   : IR receiver reads the IR remote control key value
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
#include <IRremote.hpp>  // import IRremote library

#define DECODE_NEC  // Only the NEC protocol is enabled

const int IR_Pin = 5;  //set the IR receiver pin to IO5

void setup() {
  Serial.begin(9600);  // set baud rate to 9600
  while (!Serial)
    ;  // wait for initialization

  Serial.println(F("Ready to receive NEC IR signals..."));

  IrReceiver.begin(IR_Pin, ENABLE_LED_FEEDBACK);  // Initiate reception using pin IO5
}

void loop() {
  if (IrReceiver.decode()) {  // Detect whether an infrared signal is received
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      // Print the received key values and convert to decimal
      long IR_Value = IrReceiver.decodedIRData.command;
      Serial.print("IR Value:");
      Serial.println(IR_Value);  // Print key values in decimal
    }
    IrReceiver.resume();  // Stand by to receive the next infrared signal
  }
  delay(100);
}
