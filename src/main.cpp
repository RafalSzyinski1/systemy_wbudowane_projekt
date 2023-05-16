#include <SoftwareSerial.h>
#include <Arduino.h>

#include "Init.h"
#include "InitPins.h"

void setup()
{
	Init();
	InitPins();
	digitalWrite(ENABLE_PIN, LOW);
}

void loop()
{
	if (millis() % 1000 < 500)
		digitalWrite(LED_PIN, HIGH);
	else
		digitalWrite(LED_PIN, LOW);

	if (millis() % 1000 < 300)
	{
		digitalWrite(HEATER_0_PIN, HIGH);
		digitalWrite(FAN_PIN, LOW);
	}
	else if (millis() % 1000 < 600)
	{
		digitalWrite(HEATER_0_PIN, LOW);
		digitalWrite(FAN_PIN, LOW);
	}
	else
	{
		digitalWrite(HEATER_0_PIN, LOW);
		digitalWrite(FAN_PIN, HIGH);
	}

	if (millis() % 10000 < 5000)
	{
		digitalWrite(X_DIR_PIN, HIGH);
		digitalWrite(Y_DIR_PIN, HIGH);
		digitalWrite(Z_DIR_PIN, HIGH);
		digitalWrite(E_DIR_PIN, HIGH);
	}
	else
	{
		digitalWrite(X_DIR_PIN, LOW);
		digitalWrite(Y_DIR_PIN, LOW);
		digitalWrite(Z_DIR_PIN, LOW);
		digitalWrite(E_DIR_PIN, LOW);
	}

	digitalWrite(X_STEP_PIN, HIGH);
	digitalWrite(Y_STEP_PIN, HIGH);
	digitalWrite(Z_STEP_PIN, HIGH);
	digitalWrite(E_STEP_PIN, HIGH);
	delay(1);

	digitalWrite(X_STEP_PIN, LOW);
	digitalWrite(Y_STEP_PIN, LOW);
	digitalWrite(Z_STEP_PIN, LOW);
	digitalWrite(E_STEP_PIN, LOW);
}