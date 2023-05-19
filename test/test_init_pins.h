#include <SoftwareSerial.h>
#include <Arduino.h>

#include "Init.h"
#include "InitPins.h"

void setup()
{
    Init();
    InitPins();
}

void loop()
{
    if (millis() % 1000 < 500)
    {
        digitalWrite(ENABLE_PIN, HIGH);
        digitalWrite(E_ENABLE_PIN, HIGH);
    }
    else
    {
        digitalWrite(ENABLE_PIN, LOW);
        digitalWrite(E_ENABLE_PIN, LOW);
    }
    if (millis() % 10000 < 5000)
    {
        digitalWrite(X_DIR_PIN, HIGH);
        digitalWrite(Y_DIR_PIN, HIGH);
        digitalWrite(Z_DIR_PIN, HIGH);
        digitalWrite(E_DIR_PIN, HIGH);

        digitalWrite(X_STEP_PIN, LOW);
        digitalWrite(Y_STEP_PIN, LOW);
        digitalWrite(Z_STEP_PIN, LOW);
        digitalWrite(E_STEP_PIN, LOW);
    }
    else
    {
        digitalWrite(X_DIR_PIN, LOW);
        digitalWrite(Y_DIR_PIN, LOW);
        digitalWrite(Z_DIR_PIN, LOW);
        digitalWrite(E_DIR_PIN, LOW);

        digitalWrite(X_STEP_PIN, HIGH);
        digitalWrite(Y_STEP_PIN, HIGH);
        digitalWrite(Z_STEP_PIN, HIGH);
        digitalWrite(E_STEP_PIN, HIGH);
    }
}