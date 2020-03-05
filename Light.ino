#include "dht.h"

#define SensorPin 0;
#define dht_apin A2

dht DHT;
unsigned long int avgValue;
unsigned long int avgValuePH;
float b;
int buf[10], temp, bufPH[10];
int motorPin = 6;
int lumpPin = 8;

void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(motorPin,OUTPUT);
  pinMode(lumpPin,OUTPUT);
  Serial.begin(9600);
  Serial.println("hello");
}

void loop() 
{
  if ( Serial.available() > 0 )
  {
    char command = Serial.read();
    if (command == 'a')
    {
      Serial.println("arrosage");
      digitalWrite(motorPin, HIGH);
    }
    if (command == 's')
    {
      Serial.println("arrosage arrêté");
      digitalWrite(motorPin, LOW);
    }
    if (command == 'e')
    {
      digitalWrite(lumpPin, HIGH);
      Serial.println("éclairage");
    }
    if (command == 't')
    {
      digitalWrite(lumpPin, LOW);
      Serial.println("éclairage arrêté");
    }
  }
  
  for(int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(A1);
    bufPH[i] = analogRead(0);
    delay(10);
  }

  for(int i = 0; i < 9; i++)
  {
    for(int j = i + 1; j < 10; j++)
    {
      if(buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }

      if(bufPH[i] > bufPH[j])
      {
        temp = bufPH[i];
        bufPH[i] = bufPH[j];
        bufPH[j] = temp;
      }
    }
  }

  avgValue = 0;
  avgValuePH = 0;
  for(int i = 2; i < 8; i++)
  {
    avgValue += buf[i];
    avgValuePH += bufPH[i];
  }

  avgValue = avgValue/10;
  float ph = (float) avgValuePH * 5.0/1024/6;
  ph = 3.5 * ph;

  DHT.read11(dht_apin);

  int water = analogRead(A3);

  int water2 = analogRead(A4);

  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);

  Serial.print("Temperature: ");
  Serial.println(DHT.temperature); 
  
  Serial.print("LightOne: ");
  Serial.println(avgValue);

  Serial.print("PHThree: ");
  Serial.println(ph);

  Serial.print("WaterOne: ");
  Serial.println(-water + 1024); 

  Serial.print("WaterTwo: ");
  Serial.println(water2);
    
  digitalWrite(13,HIGH);
  delay(3000);
  digitalWrite(13,LOW); 
}