#include <string.h>
#include <stdlib.h>

#include "Parser.h"
#include "Global.h"

void parseGCodeCommand(const char *command)
{
    char *checkSum = strstr(command, "*");
    if (checkSum != nullptr)
    {
        int sum = atoi(checkSum + 1);
        if (sum != calculateChecksum(command))
        {
            // TODO: ERROR
        }
    }

    char *gCommand = strstr(command, "G");
    if (gCommand != nullptr)
    {
        int gCommandNumber = atoi(gCommand + 1);
        parseGCommand(gCommandNumber);
    }
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
    case 110:
        parserState.mState |= M110;
        break;
    }
}

void parseMoveCommand(int *param);

void parseNCommand(int number)
{
    if (parserState.mState & M110)
    {
        if (parserState.lastNumberLine == -1)
        {
            parserState.lastNumberLine = number;
        }
        else if (number != parserState.lastNumberLine - 1)
        {
            // TODO: ERROR
        }
        parserState.lastNumberLine = number;
    }
}
void parseTCommand(int number)
{
    if (number != 0)
    {
        // TODO: ERROR
    }
}

int calculateChecksum(const char *command)
{
    int checksum = 0;
    size_t length = strlen(command);

    for (size_t i = 0; i < length; ++i)
    {
        if (command[i] == '*')
            break;
        checksum ^= command[i];
    }

    return checksum;
}
