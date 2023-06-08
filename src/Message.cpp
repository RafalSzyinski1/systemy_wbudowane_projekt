#include <stdarg.h>

#include "Message.h"
#include "Global.h"

int addMessage(const char *fmt, ...)
{
    if (messages.numOfMessages >= MESSAGE_NUM)
    {
        error.errorCode = 6;
        snprintf(error.errorMessage,
                 ERROR_MESSAGE_SIZE,
                 "addMessage | message overflow: %s", fmt);
        return -1;
    }

    va_list args;
    va_start(args, fmt);
    vsnprintf(messages.messages[messages.numOfMessages], MESSAGE_SIZE, fmt, args);
    va_end(args);

    messages.messages[messages.numOfMessages][sizeof(messages.messages[messages.numOfMessages]) - 1] = '\0';
    messages.numOfMessages++;
    return 0;
}
