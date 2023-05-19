#include <Arduino.h>

class Reader
{
public:
    enum Type
    {
        NONE,
        SERIAL_PORT,
        SD,
    };

public:
    Reader();
    void detectType();
    String readData();

private:
    Type mType;
};