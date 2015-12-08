/*
 * JULIAN JUIXXXE LOIACONO
 * julian3@umbc.edu
 * 12/8/2015
 * 
 * With influence from Majenko Technologies WiFi Access Point
 * Example (downloaded using Arduino IDE) and jorisplusplus'
 * AR.Drone-ESP8266 available at:
 * https://github.com/jorisplusplus/AR.Drone-ESP8266
 * 
 * Example program which demonstrates one-way communication
 * between two ESP8266s, from which two-way communication is 
 * easily derived. Communication in the form of UDP packets
 * of a single uint32_t. The access point is the "server", and
 * the sender of information is the "client".
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <IPAddress.h>
#include <WiFiUdp.h>

#define LOUTPORT 5554
const IPAddress SERVER(192, 168, 4, 1);
uint32_t i;
const char* ssid = "JUIXXXE";
const char* password = "wordpass";
#define DEBUG true

WiFiUDP LINKOUT;

void setup() {
  // put your setup code here, to run once:
  // Connect to WiFi network  
  if(DEBUG){
    Serial.begin(115200);
    Serial.println("Verifying SSID...");
  }
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(DEBUG)
    Serial.println("Waiting for connection...");
    
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }
  if(DEBUG){
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());
  }

  //Open a port
  LINKOUT.begin(LOUTPORT);
  LINKOUT.flush();
  i = 0;
}

void loop() {
    if(DEBUG){
      Serial.print("Sending UDP packet ");
      Serial.println(i, DEC);
    }
    //Send a packet
    LINKOUT.beginPacket(SERVER, LOUTPORT);
    //break i down into bytes
    for(int j = 0; j<4; j++){
      Serial.println((i>>(j*8)) & 0x00000000FF);
      LINKOUT.write((i>>(j*8)) & 0x00000000FF);
    }

    //end packet
    LINKOUT.endPacket();

    //increment i
    i++;
    delay(500);
}
