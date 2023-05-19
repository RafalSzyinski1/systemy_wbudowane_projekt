#include <SoftwareSerial.h>
#include <Arduino.h>

#include "Init.h"
#include "InitPins.h"

#include "Reader.h"

Reader reader;

void setup()
{
    Init();
    InitPins();
    reader.detectType();
    Serial.println("Connected");
}

void loop()
{
    String data = reader.readData();
    if (data != "")
        Serial.print("T:50.0/60.0 B:70.0/100.0");
    delay(500);
}