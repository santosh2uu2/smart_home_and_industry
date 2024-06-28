#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Santosh";
const char* password = "santosh2";

// Pin definitions for devices
const int light1Pin = 2; // Example pin numbers, change these according to your setup
const int light2Pin = 4;
const int light3Pin = 5;
const int fanPin = 18;
const int device1Pin = 19;
const int device2Pin = 21;

WebServer server(80);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize the outputs for the devices
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(light3Pin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(device1Pin, OUTPUT);
  pinMode(device2Pin, OUTPUT);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Route to control devices
  server.on("/", HTTP_GET, handleRoot);
  server.on("/light1/on", HTTP_GET, [](){digitalWrite(light1Pin, HIGH); server.send(200, "text/plain", "Light 1 turned on");});
  server.on("/light1/off", HTTP_GET, [](){digitalWrite(light1Pin, LOW); server.send(200, "text/plain", "Light 1 turned off");});
  server.on("/light2/on", HTTP_GET, [](){digitalWrite(light2Pin, HIGH); server.send(200, "text/plain", "Light 2 turned on");});
  server.on("/light2/off", HTTP_GET, [](){digitalWrite(light2Pin, LOW); server.send(200, "text/plain", "Light 2 turned off");});
  server.on("/light3/on", HTTP_GET, [](){digitalWrite(light3Pin, HIGH); server.send(200, "text/plain", "Light 3 turned on");});
  server.on("/light3/off", HTTP_GET, [](){digitalWrite(light3Pin, LOW); server.send(200, "text/plain", "Light 3 turned off");});
  server.on("/fan/on", HTTP_GET, [](){digitalWrite(fanPin, HIGH); server.send(200, "text/plain", "Fan turned on");});
  server.on("/fan/off", HTTP_GET, [](){digitalWrite(fanPin, LOW); server.send(200, "text/plain", "Fan turned off");});
  server.on("/device1/on", HTTP_GET, [](){digitalWrite(device1Pin, HIGH); server.send(200, "text/plain", "Device 1 turned on");});
  server.on("/device1/off", HTTP_GET, [](){digitalWrite(device1Pin, LOW); server.send(200, "text/plain", "Device 1 turned off");});
  server.on("/device2/on", HTTP_GET, [](){digitalWrite(device2Pin, HIGH); server.send(200, "text/plain", "Device 2 turned on");});
  server.on("/device2/off", HTTP_GET, [](){digitalWrite(device2Pin, LOW); server.send(200, "text/plain", "Device 2 turned off");});

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><title>Home Automation</title></head><body>";
  html += "<h1>Home Automation</h1>";
  html += "<h2>Lights</h2>";
  html += "<p><a href='/light1/on'>Turn Light 1 On</a> | <a href='/light1/off'>Turn Light 1 Off</a></p>";
  html += "<p><a href='/light2/on'>Turn Light 2 On</a> | <a href='/light2/off'>Turn Light 2 Off</a></p>";
  html += "<p><a href='/light3/on'>Turn Light 3 On</a> | <a href='/light3/off'>Turn Light 3 Off</a></p>";
  html += "<h2>Fan</h2>";
  html += "<p><a href='/fan/on'>Turn Fan On</a> | <a href='/fan/off'>Turn Fan Off</a></p>";
  html += "<h2>Other Devices</h2>";
  html += "<p><a href='/device1/on'>Turn Device 1 On</a> | <a href='/device1/off'>Turn Device 1 Off</a></p>";
  html += "<p><a href='/device2/on'>Turn Device 2 On</a> | <a href='/device2/off'>Turn Device 2 Off</a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}
