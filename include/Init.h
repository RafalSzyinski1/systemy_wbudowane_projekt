#include <Arduino.h>

#include "Configure.h"

void Init()
{
    Serial.begin(BAUDRATE);
    while (!Serial)
        ; // Wait to Serial connect
}