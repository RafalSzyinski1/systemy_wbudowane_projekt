#include <Arduino.h>

#include "ConfigurePin.h"

void InitPins()
{
    pinMode(FAN_PIN, OUTPUT);
    pinMode(HEATER_0_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);

    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);

    pinMode(Z_STEP_PIN, OUTPUT);
    pinMode(Z_DIR_PIN, OUTPUT);

    pinMode(E_STEP_PIN, OUTPUT);
    pinMode(E_DIR_PIN, OUTPUT);

    pinMode(E_ENABLE_PIN, OUTPUT);
}