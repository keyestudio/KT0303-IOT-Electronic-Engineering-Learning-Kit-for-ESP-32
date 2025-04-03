/*
 * Filename: 8_2_Parking_Sensor
 * Function: Use ultrasonic sensor and buzzer to alert the distance of obstacles
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
const int Buzzer_Pin = 13;  // the buzzer pin
const int Trig_Pin = 16;
const int Echo_Pin = 17;

// Function prototype for reading sensor data
float readSensorData();

void setup() {
  pinMode(Buzzer_Pin, OUTPUT);  // Set as output
  // Set Echo_Pin as input and Trig_Pin as output
  pinMode(Trig_Pin, OUTPUT);
  pinMode(Echo_Pin, INPUT);
}

void loop() {

  float distance = readSensorData();             //Read distance value
  if (distance <= 30 && distance > 20) {         //determine whether the value is within 20~30. If yes, run code below
    digitalWrite(Buzzer_Pin, HIGH);              //active buzzer alarms
    delay(500);                                  //delay 500ms
    digitalWrite(Buzzer_Pin, LOW);               //active buzzer off
    delay(500);                                  //delay 500ms
  } else if (distance <= 20 && distance > 10) {  //determine whether the value is within 10~20. If yes, run code below
    digitalWrite(Buzzer_Pin, HIGH);              //active buzzer alarms
    delay(100);                                  //delay 100ms
    digitalWrite(Buzzer_Pin, LOW);               //active buzzer off
    delay(100);                                  //delay 100ms
  } else if (distance <= 10) {                   //determine whether the value is euqal to or less than 10. If yes, run code below
    digitalWrite(Buzzer_Pin, HIGH);              //active buzzer alarms
  } else {                                       //else
    digitalWrite(Buzzer_Pin, LOW);               //active buzzer off
  }
  delay(100);  // delay for a period of time and measure
}

// Function to read data from the ultrasonic sensor
float readSensorData() {
  // Trigger a low signal before sending a high signal
  digitalWrite(Trig_Pin, LOW);
  delayMicroseconds(2);
  // Send a 10-microsecond high signal to the Trig_Pin
  digitalWrite(Trig_Pin, HIGH);
  delayMicroseconds(10);
  // Return to low signal
  digitalWrite(Trig_Pin, LOW);
  // Measure the duration of the high signal on the Echo_Pin
  unsigned long microsecond = pulseIn(Echo_Pin, HIGH);
  // Calculate the distance using the speed of sound (29.00µs per centimeter)
  float distance = microsecond / 29.00 / 2;
  // Return the calculated distance
  return distance;
}