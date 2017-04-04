// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <DHT_U.h>
#include <DHT.h>
#include <ArduinoJson.h>

#include "Definitions.h"


extern DHT dht;
extern long sensor_cycles;

class Sensor {
private:
	String toNAN(short i);
	short fromNAN(String str);

public:
	String source;
	char unit;
	bool active;
	uint8_t pin;

	//Sensor Values
	short minute_values[NUMMINUTE];
	short hour_values[NUMHOUR]; //every minute
	short day_values[NUMDAY]; //every 15 minutes
	short month_values[NUMMONTH]; //every 6h
	short year_values[NUMYEAR]; //every month for three years

	//Pointer to Values
	int8_t minute_ptr = -1;
	int8_t hour_ptr = -1;
	int8_t day_ptr = -1;
	int8_t month_ptr = -1;
	int8_t year_ptr = -1;
	
	Sensor();

	//UI Controls
	short getLastValue();
	short getTenSecAvg();
	short getTwentySecAvg();
	short getThirtySecAvg();
	short getOneMinAvg();
	short getTwoMinAvg();
	short getFiveMinAvg();
	short getQuarterAvg();
	short getHalfAvg();
	short getHourAvg();
	short getTwoHourAvg();
	short getThreeHourAvg();
	short getFourHourAvg();
	short getSixHourAvg();
	short getTwelveHourAvg();
	short getDayAvg();
	short getTwoDayAvg();
	short getWeekAvg();
	short getTwoWeekAvg();

	//UI Output
	virtual String getValue();
	String getTitle();

	//Read new value and write to array
	virtual float readValue();
	void update();

	//Settings
	void reset();

	//Serialize
	void serializeJSON(uint8_t id, char* json, size_t maxSize);
	bool deserializeJSON(JsonObject& data);
};

class AnalogSensor : public Sensor {
public:
	AnalogSensor(String source, uint8_t pin, char unit, bool active);
	float readValue();
	String getValue();
};

class DigitalSensor : public Sensor {
public:
	DigitalSensor(String source, int pin, char unit, bool active);
	float readValue();
	String getValue();
};

class DHTTemperature : public Sensor {
public:
	DHTTemperature(String source, char unit, bool active);
	float readValue();
	String getValue();
};

class DHTHumidity : public Sensor {
public:
	DHTHumidity(String source, char unit, bool active);
	float readValue();
	String getValue();
};

#endif

