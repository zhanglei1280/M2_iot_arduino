#include <Wire.h>
#include <Digital_Light_TSL2561.h>
#include "dht.h"

#define SensorPin 0;
#define dht_apin A2
dht DHT;

int temp, bufPH[10];

int WaterOnePin = A0;
int WaterTwoPin = A3;

int WaterOneValue = 0;
int WaterTwoValue = 0;

int PHPin = A1;
unsigned long int avgValuePH;

int lumpPin1 = 8;
int lumpPin2 = 9;
int lumpPin3 = 10;

int motorPin1 = 5;
int motorPin2 = 6;
int motorPin3 = 7;

void setup() 
{
  Wire.begin();
  TSL2561.init();
  Serial.begin(9600);
  
  pinMode(lumpPin1,OUTPUT);
  pinMode(lumpPin2,OUTPUT);
  pinMode(lumpPin3,OUTPUT);
  
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  
  pinMode(13,OUTPUT);
  
  Serial.println("hello");
}

void loop() 
{
  
  
  if ( Serial.available() > 0 )
  {
    char commande = Serial.read();
    if (commande == 'a')
    {
      Serial.println("arroser1");
      digitalWrite(motorPin1, HIGH);
    }

    if (commande == 'b')
    {
      Serial.println("arroser2");
      digitalWrite(motorPin2, HIGH);
      
    }

    if (commande == 'c')
    {
      Serial.println("arroser3");
      digitalWrite(motorPin3, HIGH);
    }
    
    if (commande == 'd')
    {
      Serial.println("stop arroser");
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
    }
    
    if (commande == 'e')
    {
      digitalWrite(lumpPin1, HIGH);
      Serial.println("eclairer1");
    }

    if (commande == 'f')
    {
      digitalWrite(lumpPin2, HIGH);
      Serial.println("eclairer2");
    }

    if (commande == 'g')
    {
      digitalWrite(lumpPin3, HIGH);
      Serial.println("eclairer3");
    }

    if (commande == 'h')
    {
      digitalWrite(lumpPin1, HIGH);
      digitalWrite(lumpPin2, HIGH);
      digitalWrite(lumpPin3, HIGH);
      Serial.println("eclairer all");
    }
    
    if (commande == 'i')
    {
      digitalWrite(lumpPin1, LOW);
      digitalWrite(lumpPin2, LOW);
      digitalWrite(lumpPin3, LOW);
      Serial.println("stop eclairer");
    }

    if (commande == 'j')
    {
      Serial.println("arroser all");
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
    }
  }
  
  for(int i = 0; i < 10; i++)
  {
    bufPH[i] = analogRead(PHPin);
    delay(10);
  }

  for(int i = 0; i < 9; i++)
  {
    for(int j = i + 1; j < 10; j++)
    {
      if(bufPH[i] > bufPH[j])
      {
        temp = bufPH[i];
        bufPH[i] = bufPH[j];
        bufPH[j] = temp;
      }
    }
  }

  avgValuePH = 0;
  for(int i = 2; i < 8; i++)
  {
    avgValuePH += bufPH[i];
  }

  float ph = (float) avgValuePH * 5.0/1024/6;
  ph = 3.5 * ph;

  Serial.print("LightOneValue: ");
  Serial.println(TSL2561.readVisibleLux());
  
  WaterOneValue = analogRead(WaterOnePin);
  Serial.print("WaterOneValue: ");
  Serial.println(WaterOneValue); 

  WaterTwoValue = analogRead(WaterTwoPin);
  Serial.print("WaterTwoValue: ");
  Serial.println(1024 - WaterTwoValue); 

  Serial.print("PHThree: ");
  Serial.println(ph);

  DHT.read11(dht_apin);  
  Serial.print("Humidity: ");
  Serial.println(DHT.humidity);
  Serial.print("Temperature: ");
  Serial.println(DHT.temperature); 

  digitalWrite(13,HIGH);
  delay(2000);
  digitalWrite(13,LOW);
}
