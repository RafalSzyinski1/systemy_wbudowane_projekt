#include <Arduino.h>

#include "Global.h"
#include "Configure.h"
#include "Init.h"

void setupSerialPort()
{
    Serial.begin(BAUDRATE);
    while (!Serial)
        ; // Wait to Serial connect
}

void setupStepperMotors()
{
    XMotor.setMaxSpeed(X_MAX_SPEED);
    XMotor.setAcceleration(X_ACCELERATION);
    XMotor.setEnablePin(ENABLE_PIN);
    XMotor.setPinsInverted(0, 0, 1);

    YMotor.setMaxSpeed(Y_MAX_SPEED);
    YMotor.setAcceleration(Y_ACCELERATION);
    YMotor.setEnablePin(ENABLE_PIN);
    YMotor.setPinsInverted(0, 0, 1);

    ZMotor.setMaxSpeed(Z_MAX_SPEED);
    ZMotor.setAcceleration(Z_ACCELERATION);
    ZMotor.setEnablePin(ENABLE_PIN);
    ZMotor.setPinsInverted(0, 0, 1);

    EMotor.setMaxSpeed(E_MAX_SPEED);
    EMotor.setAcceleration(E_ACCELERATION);
    EMotor.setEnablePin(ENABLE_PIN);
    EMotor.setPinsInverted(0, 0, 1);

    Steppers.addStepper(XMotor);
    Steppers.addStepper(YMotor);
    Steppers.addStepper(ZMotor);
    Steppers.addStepper(EMotor);
}

void setupEndStop()
{
    XendStop.setDebounceTime(50);
    YendStop.setDebounceTime(50);
    ZendStop.setDebounceTime(50);
}

void setupTools()
{
    for (size_t i = 0; i < NUM_OF_TOOLS; ++i)
    {
        tools[i].toolCode = (ToolCode)i;
        tools[i].targetHotendTemp = 0;
        tools[i].hotendTemp = 0;
    }
}

void initAll()
{
    setupSerialPort();
    setupStepperMotors();
    setupEndStop();
    setupTools();
}