/*  
 * Filename: 8_8_WiFi_Read_Sensor
 * Function: Use LAN wifi wireless to read the photoresistor and temperature value, and display them on the web page
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/

#include <WiFi.h>       // import WiFi library to control the WiFi connection function of the ESP32
#include <WebServer.h>  // import WebServer library to create HTTP server

/* Put your SSID & Password */
const char* ssid = "your SSID";    // Wi-Fi SSID, network name
const char* password = "Password"; // Wi-Fi password

WebServer server(80);  // Create a Web server object that listens on port 80

// sensor pins
const int LM35_Pin = 36;        //set lm35 pin to GPIO36
float temperature = 0;          //set variable temperature initial value to 0
long value = 0;                 //set variable value initial value to 0
float constant = 5.0 / 4095.0;  //Set the analog value constant for the calculated temperature

const int Light_Pin = 35;  // photoresistor pin 

void setup() {
  Serial.begin(9600);  // set baud rate to 9600
  delay(100);          // delay 100ms

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
  server.on("/", handle_OnConnect);    // Root path, initialize the page
  server.onNotFound(handle_NotFound);  // Handle paths that are not found

  server.begin();                         // Start the Web server
  Serial.println("HTTP server started");  // Print the server startup information
}

void loop() {
  server.handleClient();  // Process client requests
}

// The root path request is processed and the initial page is displayed
void handle_OnConnect() {
  int lightValue = analogRead(Light_Pin);  // read photoresistor value
  value = analogRead(LM35_Pin);            //read analog input
  temperature = (value * constant * 100);  //Calculate temperature values

  String htmlPage = "<!DOCTYPE html><html>\n";
  htmlPage += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlPage += "<title>ESP32 Sensor Data</title>\n";
  htmlPage += "<meta http-equiv=\"refresh\" content=\"1\"> <!-- Automatically refresh the page every 5 seconds -->\n";
  htmlPage += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlPage += "body{margin-top: 50px; background-color: #f4f4f9;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  htmlPage += "p {font-size: 20px;color: #444;margin-bottom: 10px;}\n";
  htmlPage += ".sensor-box { background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); width: 300px; margin: 20px auto;}\n";
  htmlPage += ".sensor-title { font-size: 24px; font-weight: bold; color: #333; margin-bottom: 10px; }\n";
  htmlPage += ".sensor-value { font-size: 28px; color: #e74c3c; }\n";
  htmlPage += "</style>\n";
  htmlPage += "</head>\n";
  htmlPage += "<body>\n";
  htmlPage += "<h1>ESP32 Sensor Data</h1>\n";

  // photoresistor value
  htmlPage += "<div class=\"sensor-box\">\n";
  htmlPage += "<div class=\"sensor-title\">Light Sensor Value:</div>\n";
  htmlPage += "<div class=\"sensor-value\">" + String(lightValue) + "</div>\n";
  htmlPage += "</div>\n";

  // LM35 temperature sensor value
  htmlPage += "<div class=\"sensor-box\">\n";
  htmlPage += "<div class=\"sensor-title\">Temperature:</div>\n";
  htmlPage += "<div class=\"sensor-value\">" + String(temperature) + " °C</div>\n";
  htmlPage += "</div>\n";

  htmlPage += "</body>\n";
  htmlPage += "</html>\n";

  server.send(200, "text/html", htmlPage);  // Return to HTML page
}

// Handle paths that are not found
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");  // 404 error returned
}
