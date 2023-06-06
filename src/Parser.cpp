#include <string.h>
#include <stdlib.h>

#include "Parser.h"
#include "Global.h"

int parseGCodeCommand(const char *command)
{
    char *checkSum = strstr(command, "*");
    if (checkSum != nullptr)
    {
        unsigned char sum = atoi(checkSum + 1);
        unsigned char cSum = calculateChecksum(command);
        Serial.println((int)cSum);
        if (sum != cSum)
        {
            // TODO: ERROR
            Serial.println("ERROR: sum");
        }
    }

    char *nCommand = strstr(command, "N");
    if (nCommand != nullptr)
    {
        int nCommandNumber = atoi(nCommand + 1);
        parseNCommand(nCommandNumber);
    }

    char *gCommand = strstr(command, "G");
    if (gCommand != nullptr)
    {
        int gCommandNumber = atoi(gCommand + 1);
        parseGCommand(gCommandNumber);
    }

    char *mCommand = strstr(command, "M");
    if (mCommand != nullptr)
    {
        int mCommandNumber = atoi(mCommand + 1);
        parseMCommand(mCommandNumber);
    }

    return 1;
}

void parseGCommand(int number)
{
    if (number >= G0 && number <= G3)
        parserState.gState = (GState)number;
    else
        parserState.gState = GState::None;
}

void parseMCommand(int number)
{
    switch (number)
    {
    case 105:
        Serial.print("ok T0:200.0/200.0 T1:100.0/100.0"); // TODO: Temp
        break;
    case 110:
        parserState.mState |= M110;
        break;
    }
}

void parseMoveCommand(int *param)
{
}

void parseNCommand(int number)
{
    if (parserState.mState & M110)
    {
        if (parserState.lastNumberLine != -1 && number != parserState.lastNumberLine + 1)
        {
            // TODO: ERROR
            Serial.println("ERROR: N line");
        }
        parserState.lastNumberLine = number;
    }
}
void parseTCommand(int number)
{
    if (number != 0)
    {
        // TODO: ERROR
        Serial.println("ERROR: T wrong tool");
    }
}

unsigned char calculateChecksum(const char *command)
{
    unsigned char checksum = 0;
    size_t length = strlen(command);

    for (size_t i = 0; i < length; ++i)
    {
        if (command[i] == '*')
            break;
        checksum ^= command[i];
    }

    return checksum;
}
