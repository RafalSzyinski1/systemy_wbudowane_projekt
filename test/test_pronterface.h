
// Pronterface test
#include <SoftwareSerial.h>
#include <Arduino.h>

#include "InitPins.h"

#define BAUD_RATE 115200 // Baud rate for communication

void setup()
{
    Serial.begin(BAUD_RATE);
    InitPins();
    delay(1000); // Delay for stable connection establishment

    Serial.println("Connected to Pronterface!");
}

int printed = 6;
bool print = true;

void loop()
{
    if (millis() % 1000 < 500)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);

    if (Serial.available())
    {
        if (printed <= -1 && print)
        {
            Serial.println("ok EX0: 99.0 / 100.0");
            print = false;
        }
        else
        {
            printed--;
        }
    }
}