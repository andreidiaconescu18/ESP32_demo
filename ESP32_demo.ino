#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "ssid"; // Your Wi-Fi SSID
const char* password = "parola"; // Your Wi-Fi Password

AsyncWebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  lcd.init();
  lcd.backlight();
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32's IP address
  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  // Define a route to serve the HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("ESP32 Web Server: New request received:");  // for debugging
    Serial.println("GET /");        // for debugging
    request->send(200, "text/html", "<html><body><h1>Hello, ESP32!</h1></body></html>");
  });

  server.on("/ledOn",HTTP_GET,[](AsyncWebServerRequest* request){
    Serial.println("ESP32 Web Server: New request received:");  // for debugging
    Serial.println("GET /ledOn");        // for debugging
    functieON();
    request->send(200, "text/html", "<html><body><h1>Hello, ESP32! Led is ON!</h1></body></html>");
  });

  server.on("/ledOff",HTTP_GET,[](AsyncWebServerRequest* request){
    Serial.println("ESP32 Web Server: New request received:");  // for debugging
    Serial.println("GET /ledOff");        // for debugging
    functieOFF();
    request->send(200, "text/html", "<html><body><h1>Hello, ESP32! Led is OFF!</h1></body></html>");
  });

  // Start the server
  server.begin();
}

void functieON(){
    digitalWrite(2, 1);
    lcd.setCursor(0, 0);
    lcd.print("           ");
    lcd.setCursor(0, 0);
    lcd.print("Led ON");
}

void functieOFF(){
    digitalWrite(2, 0);
    lcd.setCursor(0, 0);
    lcd.print("           ");
    lcd.setCursor(0, 0);
    lcd.print("Led OFF");
}

void loop() {}
