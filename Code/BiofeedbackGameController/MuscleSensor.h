#ifndef MuscleSensor_h
#define MuscleSensor_h

#include "Arduino.h"

class MuscleSensor
{
	public:
	  MuscleSensor(int pin, int threshold);
	  void update(void);
	  boolean isTriggered(void);

	private:
	  boolean state;
	  int sensorPin;
	  int sensorThreshold;
};

#endif
