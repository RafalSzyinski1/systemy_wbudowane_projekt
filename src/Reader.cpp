#include "Arduino.h"
#include "Reader.h"

Reader::Reader() : mType(NONE)
{
}

void Reader::detectType()
{
    while (true)
    {
        if (Serial.available())
        {
            mType = Reader::SERIAL_PORT;
            break;
        }
    }
}

String Reader::readData()
{

    String result = "";
    if (mType == Reader::SERIAL_PORT && Serial.available())
    {
        result = Serial.readString();
        result.trim();
    }
    return result;
}