/*****************************************************************************
 **  COPYRIGHT (C) 2011, ADVANCER TECHNOLOGIES, ALL RIGHTS RESERVED.
 *****************************************************************************/
 
#include "Arduino.h"
#include "MuscleSensor.h"

 /***********************************************
 Biofeedback Game Controller
 Sends game control keys to the host PC

 Developed by Advancer Technologies
 www.AdvancerTechnologies.com
*************************************************/

uint8_t buf[8] = { 0 };	/* Keyboard report buffer */
void setup();
void loop();
boolean upTriggered = false;
boolean downTriggered = false;

/***********************************************
Keyboard HID values
************************************************/ 
const int X = 27;       
const int Z = 29;     
const int ENTER = 40;   
const int RIGHT = 79;  
const int LEFT = 80;    
const int DOWN = 81;  
const int UP = 82;    
const int CTRL = 224;  

/***********************************************
Define Muscle Sensors 
args:
- pin = analog pin number
- threshold value = min. ADC value to indicate
  the sensor has been triggered
************************************************/ 
MuscleSensor rForearm(0, 300);	//Right Forearm 
MuscleSensor lForearm(1, 300);	//Left Forearm 
MuscleSensor rBicep(2, 300);	//Right Bicep 
MuscleSensor lBicep(3, 300);	//Left Bicep 

void setup()
{
    Serial.begin(9600);
    delay(200);
}

void loop()
{
   /**********************************************
   Read Sensor Values	
   ***********************************************/ 
  rForearm.update();
  lForearm.update();
  rBicep.update();
  lBicep.update();
  
   /**********************************************
   Check for Combo Buttons	
   ***********************************************/ 
   //note - delete this if you aren't mapping multiple muscles to a single button
   
  if(	rForearm.isTriggered() && lForearm.isTriggered() && 
		rBicep.isTriggered() && lBicep.isTriggered())
		upTriggered = true;
  else
		upTriggered = false;
		
  if(	rBicep.isTriggered() && lBicep.isTriggered())
		downTriggered = true;
  else
		downTriggered = false;
	
  /***********************************************
  Function Buttons	
  ************************************************/    
  if(!upTriggered && !downTriggered)
  {
	  //A Button (x key)
	  if(lForearm.isTriggered())	{buf[2] = Z;}
	  else 				{buf[2] = 0;}
		
	  //B Button (z key)
	  if(rForearm.isTriggered())	{buf[3] = X;}
	  else 				{buf[3] = 0;}

	  if(lBicep.isTriggered() &&!rBicep.isTriggered())	
                {buf[4] = LEFT;}
          else if(!lBicep.isTriggered() && rBicep.isTriggered())
        	{buf[4] = RIGHT;}
	  else 				
                {buf[4] = 0;}
  }
  else
  {	   
          if(downTriggered && !upTriggered)	
                {buf[5] = DOWN;}
          else if(!downTriggered && upTriggered)
        	{buf[5] = UP;}
	  else 				
                {buf[5] = 0;}
  }
  
  /***********************************************
   Send to CPU	
   ***********************************************/  
  Serial.write(buf, 8);	// Send keypress
  delay(100);
}
