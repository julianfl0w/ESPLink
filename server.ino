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

#define DEBUG true

#define LINPORT 5554
#define bytesExpected 4
WiFiUDP LINKIN;

/* Set these to your desired credentials. */
const char *ssid = "JUIXXXE";
const char *password = "wordpass";
byte incomingbytes[4];

void setup() {
	if(DEBUG){
    Serial.begin(115200);
	  Serial.println(); 
	  Serial.print("Configuring access point...");
	}
 
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
 
  if(DEBUG){
	  Serial.print("AP IP address: ");
	  Serial.println(myIP);
  }
  
  LINKIN.begin(LINPORT); //Open port for navdata
  LINKIN.flush();
}

void loop() {
  if (LINKIN.parsePacket()) {
    int len = LINKIN.read(incomingbytes, bytesExpected);
    uint32_t incomingInt = 0;
    for(int i = 0; i < bytesExpected; i++)
      incomingInt += incomingbytes[i]<<(i*8);
    if(DEBUG)
      Serial.println(incomingInt);
  }
}
