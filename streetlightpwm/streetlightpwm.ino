
#define trigPin 9

#define echoPin 10

#define led 11

//const int ldr = A1;
const int ldr = A1;


int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by






void setup()

{
  Serial.begin (9600);

pinMode(trigPin, OUTPUT);

pinMode(echoPin, INPUT);

pinMode(led, OUTPUT);







}



void loop()

{
 int c = analogRead(ldr);

long duration, distance;




digitalWrite(trigPin, LOW);


delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);


distance= duration*0.034/2;

  //Serial.println(c);


if( c<=800)
{

if (distance >13)

{ analogWrite(led,40);

}

if (distance <13){

analogWrite(led, 255);

}




Serial.print("Ultrasonic Sensor: ");
Serial.print(distance);
Serial.println(" cm    ");


}
else{

  digitalWrite(led,LOW);

    Serial.println("DAY");
    Serial.println(c);
  }
delay(200);

















     
      
     // delay(2000);




}
