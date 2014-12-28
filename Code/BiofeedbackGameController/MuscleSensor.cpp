#include "Arduino.h"
#include "MuscleSensor.h"

MuscleSensor::MuscleSensor(int pin, int threshold)
{
  sensorPin = pin;
  sensorThreshold = threshold;
  pinMode(sensorPin,INPUT);				//setup emgPin as input pin
  state = false;
}

void MuscleSensor::update()
{
  int sensorValue = analogRead(sensorPin);

  if(sensorValue >= sensorThreshold)
	  state = true;
  else
	  state= false;
}

boolean MuscleSensor::isTriggered()
{
  return state;
}

