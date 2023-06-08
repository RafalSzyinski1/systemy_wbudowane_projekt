#include <stdarg.h>

#include "Error.h"
#include "Global.h"

void addError(int code, const char *fmt, ...)
{
    if (fmt == nullptr)
    {
        error.errorCode = 3;
        int result = snprintf(error.errorMessage,
                              ERROR_MESSAGE_SIZE,
                              "addError | wrong input (%p)", fmt);

        if (result < 0)
            error.errorCode = 7;
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
        error.errorCode = 7;
        return;
    }

    error.errorCode = code;
    error.errorMessage[result] = '\0';
}
