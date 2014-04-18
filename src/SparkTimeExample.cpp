// This #include statement was automatically added by the Spark IDE.
#include "SparkTime.h"


UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
unsigned long lastTime = 0UL;
String timeStr;
// Create a variable that will store the temperature value
int temperature = 0;
double voltage=0.0;

void setup() {
  rtc.begin(&UDPClient, "uk.pool.ntp.org");
  rtc.setTimeZone(0); // gmt offset
  rtc.setUseEuroDSTRule(true);

  Serial.begin(9600);
  // Connect the temperature sensor to A7 and configure it
    // to be an input
    pinMode(A7, INPUT);
}

void loop() {
//	// Keep reading the temperature so when we make an API
//	  // call to read its value, we have the latest one
//	  temperature = analogRead(A7);
//	  Serial.print ("Raw data:");
//	  Serial.println (temperature);
//
//	  voltage = ((temperature * 3.3) / 4095);
//	  voltage = (voltage - 0.5) * 100;
//	  Serial.print ("Temperature (in Celsius):");
//	  Serial.println (voltage);

    currentTime = rtc.now();
    if (currentTime != lastTime) {
      byte sec = rtc.second(currentTime);
      if (sec == 00) {
	// Build Date String
	timeStr = "";
	timeStr += rtc.dayOfWeekString(currentTime);
	timeStr += ", ";
	timeStr += rtc.monthNameString(currentTime);
	timeStr += " "; 
	timeStr += rtc.dayString(currentTime);
	timeStr += ", ";
	timeStr += rtc.yearString(currentTime);
	Serial.println(timeStr);

	timeStr = "";
	timeStr += rtc.hour12String(currentTime);
	timeStr += ":";
	timeStr += rtc.minuteString(currentTime);
	timeStr += ":";
	timeStr += rtc.secondString(currentTime);	
	timeStr += " ";	
	timeStr += rtc.AMPMString(currentTime);
	Serial.println(timeStr);


	temperature = analogRead(A7);
	  Serial.print ("Raw Temperature data:");
	  Serial.println (temperature);

	  voltage = ((temperature * 3.3) / 4095);
	  voltage = (voltage - 0.5) * 100;
	  Serial.print ("Temperature (in Celsius):");
	  Serial.println (voltage);
      } else if (sec == 30) {
	// Including current timezone
	//Serial.println(rtc.ISODateString(currentTime));
	//Serial.println(rtc.ISODateUTCString(currentTime));

      } else if (sec == 50) {
	// UTC or Zulu time
	//Serial.println(rtc.ISODateUTCString(currentTime));
      } else {
	// Just the time in 12 hour format
//	timeStr = "";
//	timeStr += rtc.hour12String(currentTime);
//	timeStr += ":";
//	timeStr += rtc.minuteString(currentTime);
//	timeStr += ":";
//	timeStr += rtc.secondString(currentTime);
//	timeStr += " ";
//	timeStr += rtc.AMPMString(currentTime);
//	Serial.println(timeStr);
      }
      lastTime = currentTime;
    }

}
