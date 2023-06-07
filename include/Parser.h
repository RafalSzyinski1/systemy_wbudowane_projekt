#ifndef PARSER_H_
#define PARSER_H_

enum GState
{
    G0,
    G1,
};

enum MState
{
    None = 0,
    M110 = 1 << 0,
};

struct ParserState
{
    int gState;
    unsigned int feedrate;
    unsigned int mState;
    int lastNumberLine;
};

int parseGCodeCommand(const char *command);
int parseCommandWithNumber(const char *command, const char *letter, int *result);

int parseCheckSum(const char *command);
unsigned char calculateChecksum(const char *command);

int parseGCommand(const char *command);
int GCommand(int number);

int parseMCommand(const char *command);
int MCommand(int number);

int parseNCommand(const char *command);
int NCommand(int number);

int parseTCommand(const char *command);
int TCommand(int number);

#endif // PARSER_H_