#include <Arduino.h>
#include "Global.h"
#include "Init.h"

#include <ezButton.h>

ezButton button(X_MIN_PIN);

int ledState = HIGH;

void setup()
{
    pinMode(X_STEP_PIN, OUTPUT);
    digitalWrite(X_STEP_PIN, ledState);
    button.setDebounceTime(50);
}

void loop()
{
    button.loop();

    if (button.isReleased())
        ledState = !ledState;

    digitalWrite(X_STEP_PIN, ledState);
}