#include <DHT.h>
#include <DHT_U.h>

#include <Phant.h>

// Include the libraries we need
#include <ESP8266WiFi.h>

#include "wifi_config.h"
#include "sparkfun_config.h"


// GPIO Pin connected to AM2302 Data PIN
#define AM2302_WIRE_BUS 4 
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(AM2302_WIRE_BUS, DHTTYPE);

// Initialize the client library
WiFiClient client;


/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.print("");
  Serial.println("  DHT22 Library Demo  ");
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  delay(2000);
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  
  float h = dht.readHumidity();
  
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  char strTemperature[8];
  char strRH[8];
  
  dtostrf(t, 2, 2, strTemperature);
  dtostrf(h, 2, 2, strRH);
    
  //Post to sparkfun
  Phant phant("data.sparkfun.com", SPARKFUN_PUBLIC_KEY, SPARKFUN_PRIVATE_KEY);
  phant.add("temperature", strTemperature);
  phant.add("humidity", strRH);

  
  if (client.connect("data.sparkfun.com", 80))
  {
    Serial.println("connected");
    
    // Make a HTTP request:
    //Serial.println(phant.post());
    
    // Make a HTTP request:
    client.println(phant.post());
    client.println();
  }

  
/*  Serial.print("Humidity ");
  Serial.print(h);
  Serial.print(" Temperature ");
  Serial.println(t);
*/
    
  //delay(30000);
  ESP.deepSleep( 10 * 60 * 1000000,WAKE_RF_DEFAULT);
  
}
