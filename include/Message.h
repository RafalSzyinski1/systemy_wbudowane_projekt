#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <Arduino.h>

#define MESSAGE_SIZE 90
#define MESSAGE_NUM 2

struct Message
{
    size_t numOfMessages;
    char messages[MESSAGE_NUM][MESSAGE_SIZE];
};

int addMessage(const char *fmt, ...);
void restartMessage();

#endif // MESSAGE_H_