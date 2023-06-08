#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <Arduino.h>

#define MESSAGE_SIZE 128
#define MESSAGE_NUM 3

struct Message
{
    size_t numOfMessages;
    char messages[MESSAGE_NUM][MESSAGE_SIZE];
};

int addMessage(const char *fmt, ...);

#endif // MESSAGE_H_