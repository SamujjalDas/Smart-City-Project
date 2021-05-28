
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>



 bool clogging=false;
   bool gas=false;
   



byte sensorInterrupt = 0;


volatile long flow_frequency=0; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input






const int AOUTpin=A0;//the AOUT pin of the methane sensor goes into analog pin A0 of the arduino
const int DOUTpin=D8;//the DOUT pin of the methane sensor goes into digital pin D8 of the arduino


int limit;
int value;


void ICACHE_RAM_ATTR flow () // Interrupt function
{
   flow_frequency++;
}




void setup() {
Serial.begin(115200);//sets the baud rate

WiFi.begin("Redmi#", "smartcity1234"); //WiFi connection
while (WiFi.status() != WL_CONNECTED) { //Wait for the WiFI connection completion
 delay(500);
 Serial.println("Waiting for connection");
 }









   pinMode(D2, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   //Serial.begin(9600);
   attachInterrupt(D2, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts

pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
//pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
}

void loop()
{

  
  
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 //detachInterrupt(flowsensor);


     
l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
     // Serial.print("Water Flow: ");
    //  Serial.print(l_hour);
     // Serial.println(" L/hour");
      if(l_hour==0)
      {
        clogging=true;
        Serial.println("CLOGGING (Flow:0L/hour)");
      
      
      }
      else if(l_hour!=0){
        clogging=false;
           Serial.print(l_hour);
        
      }


  
      
    value= analogRead(AOUTpin);//reads the analaog value from the methane sensor's AOUT pin
limit= digitalRead(DOUTpin);//reads the digital value from the methane sensor's DOUT pin
Serial.print("Methane value: ");
Serial.println(value);//prints the methane value
Serial.print("Limit: ");
Serial.print(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
delay(100);
if (limit == HIGH){
  gas=true;
  
//digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on as status indicator
}
else if(limit==LOW){
  gas=false;
//digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
}


StaticJsonBuffer<300> JSONbuffer; //Declaring static JSON buffer
JsonObject& JSONencoder = JSONbuffer.createObject();
JSONencoder["id"] = 1;
JSONencoder["clogging"] = clogging;
JSONencoder["gas"] = gas;

char JSONmessageBuffer[300];
JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
Serial.println(JSONmessageBuffer);
HTTPClient http; //Declare object of class HTTPClient
http.begin("http://smartcityguwahati.herokuapp.com/webapi/drains/update"); //Specify request destination
http.addHeader("Content-Type", "application/json"); //Specify content-type header
int httpCode = http.PUT(JSONmessageBuffer); //Send the request
String payload = http.getString(); //Get the response payload
Serial.println(httpCode); //Print HTTP return code
Serial.println(payload); //Print request response payload
http.end(); //Close connection
   } else {
       Serial.println("Error in WiFi connection");
  



}
  delay(2000); //Send a request every 30 seconds

   
}
