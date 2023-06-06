
#include <Arduino.h>

#include "Init.h"

String data = "";

void setup()
{
	initAll();
	Serial.println("Connected");
}

void loop()
{
	if (Serial.available())
	{
		data = Serial.readString();
		data.trim();
	}
	if (data != "")
	{
		if (data == "M105")
			Serial.print("ok T:50.0/60.0 B:70.0/100.0");
		else
			Serial.print("ok");
	}
	data = "";
}