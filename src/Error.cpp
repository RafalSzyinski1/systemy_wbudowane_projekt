#include <stdarg.h>

#include "Error.h"
#include "Global.h"

void addError(ErrorCode code, const char *fmt, ...)
{
    if (fmt == nullptr)
    {
        error.errorCode = ERROR_INPUT;
        int result = snprintf(error.errorMessage,
                              ERROR_MESSAGE_SIZE,
                              "addError | wrong input (%p)", fmt);

        if (result < 0)
            error.printfError = 1;
        return;
    }

    va_list args;
    va_start(args, fmt);
    int result = vsnprintf(error.errorMessage,
                           ERROR_MESSAGE_SIZE,
                           fmt,
                           args);
    va_end(args);

    if (result < 0)
    {
        error.printfError = 1;
        return;
    }

    error.errorCode = code;
    error.errorMessage[result] = '\0';
}

void restartError()
{
    error.errorCode = NONE;
    error.printfError = 0;
    error.errorMessage[0] = '\0';
}