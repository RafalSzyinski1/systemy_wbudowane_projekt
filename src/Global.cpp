#include "Global.h"
#include "Configure.h"

// Stepper Motors
AccelStepper X = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper Y = AccelStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper Z = AccelStepper(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper E = AccelStepper(AccelStepper::DRIVER, E_STEP_PIN, E_DIR_PIN);
MultiStepper Steppers = MultiStepper();

// EndStop
ezButton XendStop = ezButton(X_MAX_PIN);
ezButton YendStop = ezButton(Y_MAX_PIN);
ezButton ZendStop = ezButton(Z_MAX_PIN);

// Parser
ParserState parserState = {-1, 0, 0, -1};

// Message
Message messages = {0, {"\0", "\0", "\0"}};

// Error
Error error = {"\0", 0};