#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <AccelStepper.h>
#include <MultiStepper.h>
#include <ezButton.h>

#include "ConfigurePin.h"
#include "Parser.h"
#include "Error.h"
#include "Message.h"
#include "Printer.h"

// Stepper Motors
extern AccelStepper XMotor;
extern AccelStepper YMotor;
extern AccelStepper ZMotor;
extern AccelStepper EMotor;
extern MultiStepper Steppers;

// End Stop
extern ezButton XendStop;
extern ezButton YendStop;
extern ezButton ZendStop;

// Tools
extern ToolState tools[];

// Printer
extern PrinterState printer;

// Parser
extern ParserState parserState;

// Messages
extern Message messages;

// Error
extern Error error;

#endif // GLOBAL_H_