#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


#ifndef STASSID
#define STASSID ""
#define STAPSK  ""
#endif


const char* ssid = STASSID;
const char* password = STAPSK;
const int internalLedPin = LED_BUILTIN;
const int relayPin = 16;
ESP8266WebServer server(80);


void handleRoot() {
    digitalWrite(internalLedPin, 1);
    runRelay();
    server.send(200, "text/plain", "ok");
    digitalWrite(internalLedPin, 0);
}


void runRelay() {
    Serial.println("Running Relay");
    digitalWrite(relayPin, LOW);
    delay(2000);
    digitalWrite(relayPin, HIGH);
}


void setupWifi(void) {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");
    digitalWrite(relayPin, HIGH);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}


void setupMicrocontroller() {
    pinMode(internalLedPin, OUTPUT);
    pinMode(relayPin, OUTPUT);
    digitalWrite(internalLedPin, 0);
}


void setup(void) {
    setupMicrocontroller();
    setupWifi();
}


void loop(void) {
    server.handleClient();
    MDNS.update();
}
