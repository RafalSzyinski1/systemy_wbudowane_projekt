
#include <Arduino.h>

#include "Init.h"
#include "Global.h"
#include "Parser.h"
#include "Configure.h"

char data[MAX_DATA_SIZE] = "\0";
size_t data_index = 0;
char receivedChar = '\0';

void setup()
{
	initAll();
	Serial.println("Connected");
}

void loop()
{
	Printerloop();
	if (!printer.wait && Serial.available())
	{
		receivedChar = Serial.read();

		if (data_index > MAX_DATA_SIZE)
			addError(ERROR_OVERLOAD_DATA_SIZE, "main | data to big");
		else
			data[data_index++] = receivedChar;
	}
	if (receivedChar == '\n')
	{
		data[data_index] = '\0';
		short result = parseGCodeCommand(data);
		if (!printer.wait && result == 0)
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
		if (!printer.wait)
		{
			data[0] = '\0';
			receivedChar = '\0';
			data_index = 0;
		}
	}
}