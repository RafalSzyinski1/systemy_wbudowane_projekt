#ifndef ERROR_H_
#define ERROR_H_

#define ERROR_MESSAGE_SIZE 256

struct Error
{
    char errorMessage[256];
    int errorCode;
};

///////////////////////////////////////
/// ERROR CODES:
/// 1 - error while parse command with number
/// 2 - error: wrong checksum
/// 3 - error: wrong input
/// 4 - error: wrong N-line
/// 5 - error: wrong tool
//////////////////////////////////////
#endif // ERROR_H_