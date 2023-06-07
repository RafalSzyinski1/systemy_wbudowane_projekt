#include <stdarg.h>

#include "Message.h"
#include "Global.h"

int addMessage(const char *format, ...)
{
    if (messages.numOfMessages >= MESSAGE_NUM)
    {
        error.errorCode = 6;
        snprintf(error.errorMessage,
                 ERROR_MESSAGE_SIZE,
                 "addMessage | message overflow: %s", format);
        return -1;
    }

    va_list args;
    va_start(args, format);
    vsnprintf(messages.messages[messages.numOfMessages], MESSAGE_SIZE, format, args);
    va_end(args);

    messages.messages[messages.numOfMessages][sizeof(messages.messages[messages.numOfMessages]) - 1] = '\0';
    messages.numOfMessages++;
    return 0;
}
