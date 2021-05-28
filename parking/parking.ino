#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


const int ledPin = 13;      // LED connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 55;  // threshold value to decide when the detected sound is a knock or not
bool car=false;

// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

void setup() {

Serial.begin(115200); //Serial connection
WiFi.begin("Redmi#", "smartcity1234"); //WiFi connection
while (WiFi.status() != WL_CONNECTED) { //Wait for the WiFI connection completion
 delay(500);
 Serial.println("Waiting for connection");
 }


  
  pinMode(LED_BUILTIN, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
}

void loop() {


  if (WiFi.status() == WL_CONNECTED) {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);
  Serial.println("sensorReading:");
Serial.println(sensorReading);
  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) 
  {car=true;
  Serial.println(car);

   
    
  }
  else{
  car=false;
  Serial.println(car);
}
// Serial.println(car);
//delay(500);



StaticJsonBuffer<300> JSONbuffer; //Declaring static JSON buffer
JsonObject& JSONencoder = JSONbuffer.createObject();
JSONencoder["id"] = 1;
JSONencoder["available"] = car;


char JSONmessageBuffer[300];
JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
Serial.println(JSONmessageBuffer);
HTTPClient http; //Declare object of class HTTPClient
http.begin("http://smartcityguwahati.herokuapp.com/webapi/parkings/update"); //Specify request destination
http.addHeader("Content-Type", "application/json"); //Specify content-type header
int httpCode = http.PUT(JSONmessageBuffer); //Send the request
String payload = http.getString(); //Get the response payload
Serial.println(httpCode); //Print HTTP return code
Serial.println(payload); //Print request response payload
http.end(); //Close connection
   } else {
       Serial.println("Error in WiFi connection");
  }
  delay(3000); //Send a request every 30 seconds

}
