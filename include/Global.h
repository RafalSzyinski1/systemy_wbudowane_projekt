#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <ezButton.h>

#include "ConfigurePin.h"
#include "Parser.h"

// Stepper Motors
extern AccelStepper X;
extern AccelStepper Y;
extern AccelStepper Z;
extern AccelStepper E;
extern MultiStepper Steppers;

// End Stop
extern ezButton XendStop;
extern ezButton YendStop;
extern ezButton ZendStop;

// Parser
extern ParserState parserState;

#endif // GLOBAL_H_