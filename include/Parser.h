#ifndef PARSER_H_
#define PARSER_H_

enum GState
{
    GNone,
    G0,
    G1,
};

enum MState
{
    MNone = 0,
    M110 = 1 << 0,
};

struct ParserState
{
    unsigned int gState;
    unsigned int mState;
    long lastNumberLine;
};

short parseGCodeCommand(const char *command);
short parseCommandWithInt(const char *command, const char *letter, int *result);
short parseCommandWithLong(const char *command, const char *letter, long *result);
short parseCommandWithFloat(const char *command, const char *letter, float *result);

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