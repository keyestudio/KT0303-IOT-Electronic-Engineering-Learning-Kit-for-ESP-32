/*  
 * Filename: 8_7_WiFi_Control
 * Function: Use LAN wifi wireless control LED lights on and off
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
#include <WiFi.h>       // import WiFi library to control WiFi connectivity on the ESP32
#include <WebServer.h>  // import WebServer library to create an HTTP Server

/* Put your SSID & Password */
const char* ssid = "your SSID";    //  Wi-Fi SSID, network name
const char* password = "Password"; //  Wi-Fi password

WebServer server(80);  // Create a Web server object that listens on port 80

uint8_t Green_LED_Pin = 17;    // green LED to GPIO17
bool Green_LED_State = false;  // green LED initial state to off

uint8_t Red_LED_Pin = 13;    // red LED to GPIO13
bool Red_LED_State = false;  // red LED initial state to off

void setup() {
  Serial.begin(9600);              // set baud rate to 9600
  delay(100);                      // delay 100ms
  pinMode(Green_LED_Pin, OUTPUT);  // set GPIO17 to output
  pinMode(Red_LED_Pin, OUTPUT);    // set GPIO13 to output

  Serial.println("Connecting to ");
  Serial.println(ssid);  // Print the name of the Wi-Fi you are connecting to

  // connect to Wi-Fi
  WiFi.begin(ssid, password);

  // Check whether the Wi-Fi connection is successful
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");  // print a dot per 1 second to indicate that a connection is being made
  }
  Serial.println("");
  delay(500);
  Serial.println("WiFi connected..!");  // successful Wi-Fi connection
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  // Print the assigned IP address

  // set handlers for different URL paths
  server.on("/", handle_OnConnect);                   // Root path, initialize the page
  server.on("/Red_LED_ON", handle_Red_LED_ON);        // red LED on
  server.on("/Red_LED_OFF", handle_Red_LED_OFF);      // red LED off
  server.on("/Green_LED_ON", handle_Green_LED_ON);    // green LED on
  server.on("/Green_LED_OFF", handle_Green_LED_OFF);  // green LED off
  server.onNotFound(handle_NotFound);                 // Handle paths that are not found

  server.begin();                         // Start the Web server
  Serial.println("HTTP server started");  // Print the server startup information
}

void loop() {
  server.handleClient();  // Process client requests
  if (Green_LED_State) {
    digitalWrite(Green_LED_Pin, HIGH);  // if green LED state is on, output high to turn on LED
  } else {
    digitalWrite(Green_LED_Pin, LOW);  // or output low to turn off LED
  }

  if (Red_LED_State) {
    digitalWrite(Red_LED_Pin, HIGH);  // if red LED state is on, output high to turn on LED
  } else {
    digitalWrite(Red_LED_Pin, LOW);  // or output low to turn off LED
  }
}

// The root path request is processed and the initial page is displayed
void handle_OnConnect() {
  Green_LED_State = false;                                                  // green LED initially off
  Red_LED_State = false;                                                    // red LED initially off
  Serial.println("GPIO17 Status: OFF | GPIO13 Status: OFF");                // Print LED status
  server.send(200, "text/html", SendHTML(Red_LED_State, Green_LED_State));  // Return to the original HTML page
}

// process red LED on request
void handle_Red_LED_ON() {
  Red_LED_State = true;                                                     // set green LED state to on
  Serial.println("GPIO13 Status: ON");                                      // print LED state 
  server.send(200, "text/html", SendHTML(Red_LED_State, Green_LED_State));  // return the updated HTML page
}

// process red LED off request
void handle_Red_LED_OFF() {
  Red_LED_State = LOW;                                                      // set green LED state to off
  Serial.println("GPIO13 Status: OFF");                                     // print LED state 
  server.send(200, "text/html", SendHTML(Red_LED_State, Green_LED_State));  // return the updated HTML page
}

// process green LED on request
void handle_Green_LED_ON() {
  Green_LED_State = true;                                                   // set red LED state to on
  Serial.println("GPIO17 Status: ON");                                      // print LED state 
  server.send(200, "text/html", SendHTML(Red_LED_State, Green_LED_State));  // return the updated HTML page
}

// process green LED off request
void handle_Green_LED_OFF() {
  Green_LED_State = false;                                                  // set red LED state to off
  Serial.println("GPIO17 Status: OFF");                                     // print LED state 
  server.send(200, "text/html", SendHTML(Red_LED_State, Green_LED_State));  // return the updated HTML page
}

// process none path
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");  // 404 error returned
}

// Generate an HTML page to display the LED state and control buttons
String SendHTML(uint8_t RedState, uint8_t GreenState) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Web Server</h1>\n";
  ptr += "<h3>Using Station(STA) Mode</h3>\n";

  // according to red LED state, generate HTML button
  if (RedState) {
    ptr += "<p>Red LED State: ON</p><a class=\"button button-off\" href=\"/Red_LED_OFF\">OFF</a>\n";
  } else {
    ptr += "<p>Red LED State: OFF</p><a class=\"button button-on\" href=\"/Red_LED_ON\">ON</a>\n";
  }

  // according to green LED state, generate HTML button
  if (GreenState) {
    ptr += "<p>Green LED State: ON</p><a class=\"button button-off\" href=\"/Green_LED_OFF\">OFF</a>\n";
  } else {
    ptr += "<p>Green LED State: OFF</p><a class=\"button button-on\" href=\"/Green_LED_ON\">ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;  // Return the generated HTML page
}
