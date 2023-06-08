#ifndef ERROR_H_
#define ERROR_H_

#define ERROR_MESSAGE_SIZE 128

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
};

void addError(ErrorCode code, const char *fmt, ...);

#endif // ERROR_H_