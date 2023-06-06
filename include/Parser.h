#ifndef PARSER_H_
#define PARSER_H_

enum GState
{
    None = -1,
    G0,
    G1,
    G2,
    G3
};

enum MState
{
    None = 0,
    M110 = 1 << 0,
};

struct ParserState
{
    GState gState;

    uint16_t mState;
    int lastNumberLine;
};

void parseGCodeCommand(const char *command);
void parseGCommand(int number);
void parseMCommand(int number);
void parseNCommand(int number);
void parseTCommand(int number);
void parseMoveCommand(int *param);
int calculateChecksum(const char *command);

#endif // PARSER_H_