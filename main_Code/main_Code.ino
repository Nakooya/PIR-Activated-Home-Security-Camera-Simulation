#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8 //DS18B20 PIN 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Temperature Computation
float Celsius = 0;

//ULTRASONIC PIN ASSIGNMENT
const int trigPin = 9; //ULTRASONIC TRIGGER PIN 9
const int echoPin = 10; //ULTRASONIC ECHO PIN 10

//Distance computation inputs
long duration;
int distance;

//Output Pins
const int outEcho = 2;
const int outTemp = 3;


void setup() {
  //Temperature Sensor
  //sensors.begin();
  //Pin Assignments
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outEcho, OUTPUT);
  pinMode (outTemp, OUTPUT);
  //Serial Monitor Baud Rate
  Serial.begin(9600);
}

void loop() {


  digitalWrite(outTemp, LOW);
  digitalWrite(outEcho, LOW);

  /* ULTRASONIC */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance != 0)
  {
    Serial.print("Distance: ");
    Serial.println(distance);
  }

  if (distance > 0 && distance <= 15)
  {

    digitalWrite(outEcho, HIGH);
    delay(1000);

    while (1)
    {
      sensors.requestTemperatures();
      delay(100);
      Celsius = sensors.getTempCByIndex(0);
      if (Celsius == -127 ) {
        digitalWrite(outTemp, LOW);
      }
      else
      {
        Serial.print(Celsius);
        Serial.println(" C  ");
        if (Celsius >= 36 && Celsius <= 37)
        {
          digitalWrite(outTemp, HIGH);
          Serial.println("Output Triggered. Twenty seconds delay started...");
          delay(5000);
          break;

        }


      }

    }

  }
  else
  {
    digitalWrite(outEcho, LOW);
  }
}
