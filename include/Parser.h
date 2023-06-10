#ifndef PARSER_H_
#define PARSER_H_

enum MState
{
    MNone = 0,
    M82 = 1 << 0,
    M83 = 1 << 1,
    M110 = 1 << 2,
};

struct ParserState
{
    unsigned int mState;
    int lastNumberLine;
};

enum Param
{
    G,
    M,
    N,
    T,
    X,
    Y,
    Z,
    E,
    F,
    S,
    R,
    PARAM_COUNT
};

short parseGCodeCommand(const char *command);
short parseCommandWithFloat(const char *command, const char *letter, float *result);

void deleteComments(const char *command);

short parseCheckSum(const char *command);
unsigned char calculateChecksum(const char *command);

short NCommand(float *params);
short TCommand(float *params);

#endif // PARSER_H_