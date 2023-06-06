#include <Arduino.h>
#include "Global.h"
#include "Init.h"

void setup()
{
    initAll();
}

void loop()
{
    long moves[] = {1000, 2000, 3000, 4000};
    Steppers.moveTo(moves);
    Steppers.run();
}
