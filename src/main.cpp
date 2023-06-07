
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
		data = Serial.readStringUntil('\n');
		data.trim();
	}
	if (data != "")
	{
		int result = parseGCodeCommand(data.c_str());
		if (result == 0)
		{
			Serial.print("ok");
			for (size_t i = 0; i < messages.numOfMessages; ++i)
			{
				Serial.print(' ');
				Serial.print(messages.messages[i]);
			}
			messages.numOfMessages = 0;
		}
		else
		{
			Serial.println("M108");
			Serial.print("ERROR with command: ");
			Serial.println(data);
			Serial.print("ERROR CODE: ");
			Serial.println(error.errorCode);
			Serial.println(error.errorMessage);

			error.errorCode = 0;
			error.errorMessage[0] = '\0';
		}
	}
	data = "";
}