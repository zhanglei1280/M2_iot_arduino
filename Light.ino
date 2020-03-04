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
  // put your setup code here, to run once:
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
    char c = Serial.read();
    if (c == 'a')
    {
      Serial.println("arroser");
      digitalWrite(motorPin, HIGH);
      
    }
    if (c == 's')
    {
      Serial.println("stop arroser");
      digitalWrite(motorPin, LOW);

      
    }
    if (c == 'e')
    {
      digitalWrite(lumpPin, HIGH);
      Serial.println("eclairer");
      
    }
    if (c == 't')
    {
      digitalWrite(lumpPin, LOW);
      Serial.println("stop eclairer");
      
    }
  }
  
  
  // put your main code here, to run repeatedly:
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
  
  Serial.print("LightOne: ");
  Serial.println(avgValue);

  Serial.print("PH: ");
  Serial.println(ph);

  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);
  Serial.print("Temperature: ");
  Serial.println(DHT.temperature); 

  Serial.print("Water: ");
  Serial.println(-water + 1024); 

  Serial.print("WaterTwo: ");
  Serial.println(water2);
    
  
  digitalWrite(13,HIGH);
  delay(3000);
  digitalWrite(13,LOW);
  
}
