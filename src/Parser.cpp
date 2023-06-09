#include <string.h>
#include <stdlib.h>

#include "Parser.h"
#include "Global.h"
#include "Printer.h"

short parseGCodeCommand(const char *command)
{
    if (command == nullptr)
    {
        addError(ERROR_INPUT, "parseGCodeCommand | Wrong input (%p)", command);
        return -1;
    }

    deleteComments(command);

    if (parseCheckSum(command) == -1)
        return -1;

    if (parseMCommand(command) == -1)
        return -1;

    if (parseNCommand(command) == -1)
        return -1;

    if (parseGCommand(command) == -1)
        return -1;

    if (parseTCommand(command) == -1)
        return -1;

    return 0;
}

void deleteComments(const char *command)
{
    char *comment = strstr(command, ";");
    if (comment != nullptr)
        *comment = '\0';
}

short parseCommandWithInt(const char *command, const char *letter, int *result)
{
    if (letter == nullptr || result == nullptr)
    {
        addError(ERROR_INPUT, "parseCommandWithInt | Wrong input (%p, %p, %p)", command, letter, result);
        return -1;
    }

    char *letterInCommand = strstr(command, letter);
    if (letterInCommand == nullptr)
        return 1;

    if (!isdigit(*(letterInCommand + 1)) && !isdigit(*(letterInCommand + 2)))
    {
        addError(ERROR_PARSE_NUMBER, "parseCommandWithInt | Cannot parse number from %s", letter);
        return -1;
    }

    *result = atoi(letterInCommand + 1);
    return 0;
}

short parseCommandWithLong(const char *command, const char *letter, long *result)
{
    if (letter == nullptr || result == nullptr)
    {
        addError(ERROR_INPUT, "parseCommandWithLong | Wrong input (%p, %p, %p)", command, letter, result);
        return -1;
    }

    char *letterInCommand = strstr(command, letter);
    if (letterInCommand == nullptr)
        return 1;

    if (!isdigit(*(letterInCommand + 1)) && !isdigit(*(letterInCommand + 2)))
    {
        addError(ERROR_PARSE_NUMBER, "parseCommandWithLong | Cannot parse number from %s", letter);
        return -1;
    }

    *result = atol(letterInCommand + 1);
    return 0;
}

short parseCommandWithFloat(const char *command, const char *letter, float *result)
{
    if (letter == nullptr || result == nullptr)
    {
        addError(ERROR_INPUT, "parseCommandWithFloat | Wrong input (%p, %p, %p)", command, letter, result);
        return -1;
    }

    char *letterInCommand = strstr(command, letter);
    if (letterInCommand == nullptr)
        return 1;

    if (!isdigit(*(letterInCommand + 1)) && !isdigit(*(letterInCommand + 2)))
    {
        addError(ERROR_PARSE_NUMBER, "parseCommandWithFloat | Cannot parse number from %s", letter);
        return -1;
    }

    *result = atof(letterInCommand + 1);
    return 0;
}

short parseCheckSum(const char *command)
{
    int checkSum = 0;
    short result = parseCommandWithInt(command, "*", &checkSum);
    if (result == -1)
        return -1;
    else if (result == 0)
    {
        if (checkSum != calculateChecksum(command))
        {
            addError(ERROR_CHECKSUM, "Wrong check sum | expect: %d, get: %d", checkSum, calculateChecksum(command));
            return -1;
        }
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

short parseGCommand(const char *command)
{
    int gNumber = 0;
    short result = parseCommandWithInt(command, "G", &gNumber);
    if (result == -1)
        return -1;
    else if (result == 0)
    {
        return GCommand(gNumber);
    }
    return 0;
}

short GCommand(int number)
{
    switch (number)
    {
    case 0:
        // Move fast
        break;
    case 1:
        // Move with framefate
        break;
    case 28:
        homing();
        break;
    case 92:
        setStartPosition();
        break;
    default:
        return -1;
        break;
    }
    return 0;
}

short parseMCommand(const char *command)
{
    int mNumber = 0;
    short result = parseCommandWithInt(command, "M", &mNumber);
    if (result == -1)
        return -1;
    else if (result == 0)
        return MCommand(mNumber);
    return 0;
}

short MCommand(int number)
{
    switch (number)
    {
    case 17:
        X.enableOutputs();
        Y.enableOutputs();
        Z.enableOutputs();
        E.enableOutputs();
        break;
    case 82:
    case 83:
        // Relative, Absolute codes (ignore)
        break;
    case 84:
        X.disableOutputs();
        Y.disableOutputs();
        Z.disableOutputs();
        E.disableOutputs();
        break;
    case 104:
        // TODO: hotend fun
        break;
    case 105:
        if (addMessage("T0:200.0/200.0 T1:100.0/100.0") == -1) // TODO: Temp message
            return -1;
        break;
    case 107:
        // TODO: fan off
        break;
    case 109:
        // TODO: hotend fun
        break;
    case 110:
        parserState.mState |= M110;
        parserState.lastNumberLine = -1;
        break;
    case 140:
        // TODO: hot bed fun
        break;
    default:
        return -1;
        break;
    }

    return 0;
}

short parseNCommand(const char *command)
{
    long nLine = 0;
    short result = parseCommandWithLong(command, "N", &nLine);
    if (result == -1)
        return -1;
    else if (result == 0)
        return NCommand(nLine);

    return 0;
}

short NCommand(long number)
{
    if (parserState.mState & M110)
    {
        if (parserState.lastNumberLine != -1 && number != parserState.lastNumberLine + 1)
        {
            addError(ERROR_NLINE, "NCommand | Wrong line number: %d, last line number %d", number, parserState.lastNumberLine);
            return -1;
        }
        parserState.lastNumberLine = number;
    }

    return 0;
}

short parseTCommand(const char *command)
{
    int tTool = 0;
    short result = parseCommandWithInt(command, "T", &tTool);
    if (result == -1)
        return -1;
    else if (result == 0)
        return TCommand(tTool);

    return 0;
}

short TCommand(int number)
{
    if (number != 0)
    {
        addError(ERROR_TOOL, "TCommand | Wrong tool: %d", number);
        return -1;
    }

    return 0;
}
