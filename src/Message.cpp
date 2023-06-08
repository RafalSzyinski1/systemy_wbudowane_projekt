#include <stdarg.h>

#include "Message.h"
#include "Global.h"

int addMessage(const char *fmt, ...)
{
    if (fmt == nullptr)
    {
        addError(ERROR_INPUT, "addMessage | wrong input fmt == nullptr");
        return -1;
    }

    if (messages.numOfMessages >= MESSAGE_NUM)
    {
        addError(ERROR_MESSAGE_OVERFLOW, "addMessage | message overflow: %s", fmt);
        return -1;
    }

    va_list args;
    va_start(args, fmt);
    int result = vsnprintf(messages.messages[messages.numOfMessages],
                           MESSAGE_SIZE,
                           fmt,
                           args);
    va_end(args);

    if (result < 0)
    {
        addError(ERROR_PRINTF, "addMessage | vsnprintf error");
        return -1;
    }

    messages.messages[messages.numOfMessages][result] = '\0';
    messages.numOfMessages++;
    return 0;
}

void restartMessage()
{
    messages.numOfMessages = 0;
    for (int i = 0; i < MESSAGE_NUM; ++i)
        messages.messages[i][0] = '\0';
}