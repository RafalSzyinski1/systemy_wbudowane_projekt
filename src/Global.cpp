#include "Global.h"
#include "Configure.h"

// Stepper Motors
AccelStepper XMotor = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper YMotor = AccelStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper ZMotor = AccelStepper(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper EMotor = AccelStepper(AccelStepper::DRIVER, E_STEP_PIN, E_DIR_PIN);
MultiStepper Steppers = MultiStepper();

// EndStop
ezButton XendStop = ezButton(X_MAX_PIN);
ezButton YendStop = ezButton(Y_MAX_PIN);
ezButton ZendStop = ezButton(Z_MAX_PIN);

// Tools
ToolState tools[NUM_OF_TOOLS];

// Printer
PrinterState printer = {TNone, 0, 0, 0, nullptr};

// Parser
ParserState parserState = {MNone, -1};

// Message
Message messages = {0, {"\0", "\0"}};

// Error
Error error = {"\0", NONE, 0};