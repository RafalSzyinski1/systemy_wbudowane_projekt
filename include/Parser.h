#ifndef PARSER_H_
#define PARSER_H_

enum GState
{
    None,
    G1,
    G2,
    G3
};

struct ParserState
{
    GState gstate;
};

void parseGCodeCommand(const char *command);
void parseGCommand(int number);
void parseMCommand(int number);
void parseMoveCommand(int *param);

#endif // PARSER_H_