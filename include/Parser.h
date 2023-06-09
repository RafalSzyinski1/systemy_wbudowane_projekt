#ifndef PARSER_H_
#define PARSER_H_

enum MState
{
    MNone = 0,
    M110 = 1 << 0,
};

struct ParserState
{
    unsigned int mState;
    long lastNumberLine;
};

short parseGCodeCommand(const char *command);
short parseCommandWithInt(const char *command, const char *letter, int *result);
short parseCommandWithLong(const char *command, const char *letter, long *result);
short parseCommandWithFloat(const char *command, const char *letter, float *result);

void deleteComments(const char *command);

short parseCheckSum(const char *command);
unsigned char calculateChecksum(const char *command);

short parseGCommand(const char *command);
short GCommand(int number);

short parseMCommand(const char *command);
short MCommand(int number);

short parseNCommand(const char *command);
short NCommand(long number);

short parseTCommand(const char *command);
short TCommand(int number);

#endif // PARSER_H_