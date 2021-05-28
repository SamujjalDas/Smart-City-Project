
#include <ESP8266WiFi.h>;
 
#include <WiFiClient.h>;
 
#include <ThingSpeak.h>;
#define trigPin 5 //d1
#define echoPin 4//d2

 
const char* ssid = "Redmi#"; //Your Network SSID
 
const char* password = "smartcity1234"; //Your Network Password
 
int val;
 

 
 
 
WiFiClient client;
 
unsigned long myChannelNumber = 729077; //Your Channel Number (Without Brackets)
 
const char * myWriteAPIKey = "CRZWKRE4UX7Q8ILQ"; //Your Write API Key
 
void setup()
 
{
 

 Serial.begin(9600);
delay(10);
pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
// Connect to WiFi network
 
WiFi.begin(ssid, password);
 
 
 
ThingSpeak.begin(client);
 
}
 
 
 
void loop()
 
{long duration;
long distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
//Serial.println(distance);
//delay(200);
  
 val=distance;
Serial.println(val); //Print on Serial Monitor
 
delay(100);
 
ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
 
 
 
delay(50);
 
}
