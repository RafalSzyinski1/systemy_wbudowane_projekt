
#include <Arduino.h>

#include "Init.h"
#include "Global.h"
#include "Parser.h"
#include "Configure.h"

String data = "";

void setup()
{
	initAll();
	Serial.println("Connected");
}

void loop()
{
	Printerloop();
	if (Serial.available())
	{
		data = Serial.readStringUntil('\n');
	}
	if (data != "")
	{
		short result = parseGCodeCommand(data.c_str());
		if (result == 0)
		{
			Serial.print("ok");
			for (size_t i = 0; i < messages.numOfMessages; ++i)
			{
				Serial.print(' ');
				Serial.print(messages.messages[i]);
			}
			Serial.println();
			restartMessage();
		}
		else if (result == -1 || error.errorCode != NONE)
		{
			Serial.println("M108");
			Serial.print("ERROR with command: ");
			Serial.println(data);
			Serial.print("ERROR CODE: ");
			Serial.println(error.errorCode);
			Serial.println(error.errorMessage);

			restartError();
		}

		data = "";
	}
}