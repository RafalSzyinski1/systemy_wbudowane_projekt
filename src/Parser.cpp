#include <string.h>
#include <stdlib.h>

#include "Parser.h"
#include "Global.h"
#include "Printer.h"
#include "GCommand.h"
#include "MCommand.h"

#define CASE_PARSE_FUNCTION(ParamType)                                \
    case #ParamType[0]:                                               \
        number = 0.0;                                                 \
        result = parseCommandWithFloat(command, #ParamType, &number); \
        if (result == -1)                                             \
            return -1;                                                \
        else if (result == 0)                                         \
            params[ParamType] = number;                               \
        else if (result == 2)                                         \
            params[ParamType] = 0;                                    \
        break;

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

    float params[PARAM_COUNT];
    for (size_t i = 0; i < PARAM_COUNT; ++i)
        params[i] = NAN;
    float number = 0.0;
    short result = 0;
    char *commandCopy = strdup(command);
    char *parameter = strtok(commandCopy, " ");

    while (parameter != nullptr)
    {
        switch (parameter[0])
        {
            CASE_PARSE_FUNCTION(G);
            CASE_PARSE_FUNCTION(M);
            CASE_PARSE_FUNCTION(N);
            CASE_PARSE_FUNCTION(T);
            CASE_PARSE_FUNCTION(X);
            CASE_PARSE_FUNCTION(Y);
            CASE_PARSE_FUNCTION(Z);
            CASE_PARSE_FUNCTION(F);
            CASE_PARSE_FUNCTION(E);
            CASE_PARSE_FUNCTION(S);
            CASE_PARSE_FUNCTION(R);
        default:
            return -1;
            break;
        }

        parameter = strtok(NULL, " ");
    }

    if (NCommand(params) == -1)
        return -1;

    if (MCommand(params) == -1)
        return -1;

    if (GCommand(params) == -1)
        return -1;

    if (TCommand(params) == -1)
        return -1;

    return 0;
}

short parseCommandWithFloat(const char *command, const char *letter, float *result)
{
    if (letter == nullptr)
    {
        addError(ERROR_INPUT, "parseCommandWithFloat | Wrong input (%p, %p, %p)", command, letter, result);
        return -1;
    }

    char *letterInCommand = strstr(command, letter);
    if (letterInCommand == nullptr)
        return 1;

    if (!isdigit(*(letterInCommand + 1)) && !isdigit(*(letterInCommand + 2)))
        return 2;

    if (result != nullptr)
        *result = atof(letterInCommand + 1);
    return 0;
}

void deleteComments(const char *command)
{
    char *comment = strstr(command, ";");
    if (comment != nullptr)
        *comment = '\0';
}

short parseCheckSum(const char *command)
{
    float checkSum = 0;
    short result = parseCommandWithFloat(command, "*", &checkSum);
    if (result == -1 || result == 2)
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

short NCommand(float *params)
{
    if (parserState.mState & M110)
    {
        if (parserState.lastNumberLine != -1 && (int)params[N] != parserState.lastNumberLine + 1)
        {
            addError(ERROR_NLINE, "NCommand | Wrong line number: %d, last line number %d", (int)params[N], parserState.lastNumberLine);
            return -1;
        }
        parserState.lastNumberLine = (int)params[N];
    }

    return 0;
}

short TCommand(float *params)
{
    for (size_t i = G; i < PARAM_COUNT; ++i)
        if (i == T || i == N)
            continue;
        else if (params[i] != NAN)
            return 0;

    if ((int)params[T] != T0)
    {
        addError(ERROR_TOOL, "TCommand | Wrong tool: %d", (int)params[T]);
        return -1;
    }

    return 0;
}
