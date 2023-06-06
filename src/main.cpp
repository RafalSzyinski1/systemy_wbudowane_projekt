
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
		int result = parseGCodeCommand(data.c_str());
		if (result == 1)
			Serial.println("ok");
	}
	data = "";
}