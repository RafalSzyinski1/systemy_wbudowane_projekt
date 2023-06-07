#include <string.h>
#include <stdlib.h>

#include "Parser.h"
#include "Global.h"

int parseGCodeCommand(const char *command)
{
    if (command == nullptr)
    {
        error.errorCode = 3;
        snprintf(error.errorMessage,
                 ERROR_MESSAGE_SIZE,
                 "parseGCodeCommand | Wrong input (%p)", command);
        return -1;
    }

    if (parseCheckSum(command) == -1)
        return -1;

    if (parseNCommand(command) == -1)
        return -1;

    if (parseGCommand(command) == -1)
        return -1;

    if (parseMCommand(command) == -1)
        return -1;

    if (parseTCommand(command) == -1)
        return -1;

    return 0;
}

int parseCommandWithNumber(const char *command, const char *letter, int *result)
{
    if (letter == nullptr || result == nullptr)
    {
        error.errorCode = 3;
        snprintf(error.errorMessage,
                 ERROR_MESSAGE_SIZE,
                 "parseCommandWithNumber | Wrong input (%p, %p, %p)", command, letter, result);
        return -1;
    }

    char *letterInCommand = strstr(command, letter);
    if (letterInCommand == nullptr)
        return 1;

    if (!isdigit(*(letterInCommand + 1)) && !isdigit(*(letterInCommand + 2)))
    {
        error.errorCode = 1;
        snprintf(error.errorMessage,
                 ERROR_MESSAGE_SIZE,
                 "parseCommandWithNumber | Cannot parse number from %s", letter);
        return -1;
    }

    *result = atoi(letterInCommand + 1);
    return 0;
}

int parseCheckSum(const char *command)
{
    int checkSum = 0;
    int result = parseCommandWithNumber(command, "*", &checkSum);
    if (result == -1)
        return -1;
    else if (result == 0)
    {
        if (checkSum != calculateChecksum(command))
        {
            error.errorCode = 2;
            snprintf(error.errorMessage,
                     ERROR_MESSAGE_SIZE,
                     "Wrong check sum | expect: %d, get: %d", checkSum, calculateChecksum(command));
            return -1;
        }
    }
    return 0;
}

int parseGCommand(const char *command)
{
    int gNumber = 0;
    int result = parseCommandWithNumber(command, "G", &gNumber);
    if (result == -1)
        return -1;
    else if (result == 0)
    {
        return GCommand(gNumber);
    }
    return 0;
}

int GCommand(int number)
{
    if (number >= G0 && number <= G1)
        parserState.gState = number;
    else
        return 0; // TODO: for now its 0 default should be -
    return 0;
}

int parseMCommand(const char *command)
{
    int mNumber = 0;
    int result = parseCommandWithNumber(command, "M", &mNumber);
    if (result == -1)
        return -1;
    else if (result == 0)
        return MCommand(mNumber);
    return 0;
}

int MCommand(int number)
{
    switch (number)
    {
    case 105:
        if (addMessage("T0:200.0/200.0 T1:100.0/100.0") == -1)
            return -1;
        break;
    case 110:
        parserState.mState |= M110;
        break;
    default:
        return 0; // TODO: for now its 0 default should be -1
        break;
    }

    return 0;
}

int parseNCommand(const char *command)
{
    int nLine = 0;
    int result = parseCommandWithNumber(command, "N", &nLine);
    if (result == -1)
        return -1;
    else if (result == 0)
        return NCommand(nLine);

    return 0;
}

int NCommand(int number)
{
    if (parserState.mState & M110)
    {
        if (parserState.lastNumberLine != -1 && number != parserState.lastNumberLine + 1)
        {
            error.errorCode = 4;
            snprintf(error.errorMessage,
                     ERROR_MESSAGE_SIZE,
                     "NCommand | Wrong line number: %d, last line number %d", number, parserState.lastNumberLine);
            return -1;
        }
        parserState.lastNumberLine = number;
    }

    return 0;
}

int parseTCommand(const char *command)
{
    int tTool = 0;
    int result = parseCommandWithNumber(command, "T", &tTool);
    if (result == -1)
        return -1;
    else if (result == 0)
        return TCommand(tTool);

    return 0;
}

int TCommand(int number)
{
    if (number != 0)
    {
        error.errorCode = 5;
        snprintf(error.errorMessage,
                 ERROR_MESSAGE_SIZE,
                 "TCommand | Wrong tool: %d", number);
        return -1;
    }

    return 0;
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
