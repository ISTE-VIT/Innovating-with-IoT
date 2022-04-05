#include <DHT.h>
#include <DHT_U.h>

#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <DHT.h>

const char* ssid = "Tirthhh";   // Your Network SSID
const char* password = "0987654321";       // Your Network Password

int val;
#define DHTPIN 0          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);

WiFiClient client;

unsigned long myChannelNumber = 1684584; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "L2DKNOABLZB5HEJE"; //Your Write API Key

void setup()
{
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
  ThingSpeak.begin(client);
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(t);                 // Print on Serial Monitor
  Serial.println("*C");
  Serial.print("Humidity: ");
  Serial.print(h);                 // Print on Serial Monitor
  Serial.println("%");
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1,t, myWriteAPIKey); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 2,h, myWriteAPIKey); //Update in ThingSpeak
  delay(100);
}
