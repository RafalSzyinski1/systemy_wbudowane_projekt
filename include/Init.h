#ifndef INIT_H_
#define INIT_H_

#include <Arduino.h>

#include "Configure.h"

void setupSerialPort()
{
    Serial.begin(BAUDRATE);
    while (!Serial)
        ; // Wait to Serial connect
}

void setupStepperMotors()
{
    X.setMaxSpeed(X_MAX_SPEED);
    X.setAcceleration(X_ACCELERATION);
    Y.setMaxSpeed(Y_MAX_SPEED);
    Y.setAcceleration(Y_ACCELERATION);
    Z.setMaxSpeed(Z_MAX_SPEED);
    Z.setAcceleration(Z_ACCELERATION);
    E.setMaxSpeed(E_MAX_SPEED);
    E.setAcceleration(E_ACCELERATION);

    Steppers.addStepper(X);
    Steppers.addStepper(Y);
    Steppers.addStepper(Z);
    Steppers.addStepper(E);
}

void initAll()
{
    setupSerialPort();
    setupStepperMotors();
}

#endif // INIT_H_