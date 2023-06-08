#ifndef ERROR_H_
#define ERROR_H_

#include <Arduino.h>

#define ERROR_MESSAGE_SIZE 90

enum ErrorCode
{
    NONE,
    ERROR_PARSE_NUMBER,
    ERROR_CHECKSUM,
    ERROR_INPUT,
    ERROR_NLINE,
    ERROR_TOOL,
    ERROR_MESSAGE_OVERFLOW,
    ERROR_PRINTF,
};

struct Error
{
    char errorMessage[ERROR_MESSAGE_SIZE];
    ErrorCode errorCode;
    uint8_t printfError;
};

void addError(ErrorCode code, const char *fmt, ...);
void restartError();

#endif // ERROR_H_