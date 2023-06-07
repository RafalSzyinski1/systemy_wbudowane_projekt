#ifndef ERROR_H_
#define ERROR_H_

#define ERROR_MESSAGE_SIZE 128

struct Error
{
    char errorMessage[ERROR_MESSAGE_SIZE];
    int errorCode;
};

///////////////////////////////////////
/// ERROR CODES:
/// 1 - error while parse command with number
/// 2 - error: wrong checksum
/// 3 - error: wrong input
/// 4 - error: wrong N-line
/// 5 - error: wrong tool
/// 6 - error: messages overflow
//////////////////////////////////////
#endif // ERROR_H_