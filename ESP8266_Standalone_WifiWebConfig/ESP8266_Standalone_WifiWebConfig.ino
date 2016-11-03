/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * NOTE: SmartConfig might not work in your environment.
 *       Please try basic ESP8266 SmartConfig examples
 *       before using this sketch!
 *
 * Change Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

//for LED status
#include <Ticker.h>
Ticker ticker;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f7f7aab7e2894b29b4ffbd71979f696d";

#define TRIGGER_PIN 0
#define LED_PIN 13

void tick()
{
  //toggle state
  int state = digitalRead(LED_PIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_PIN, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

void setup()
{
  WiFiManager wifiManager;
  
  Serial.begin(115200);
  Serial.println("\n Starting");
  pinMode(TRIGGER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  ticker.attach(0.6, tick);

  wifiManager.setAPCallback(configModeCallback);

  if (!wifiManager.autoConnect("VerwarmingsknopAP", "12345678")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }
  
  Serial.println("connected...");
  ticker.detach();
  digitalWrite(LED_PIN, HIGH);
  
  Blynk.config(auth);
}

void loop()
{
  Blynk.run();
}

