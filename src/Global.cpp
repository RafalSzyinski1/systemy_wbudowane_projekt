#include "Global.h"
#include "Configure.h"

// Stepper Motors
AccelStepper X = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper Y = AccelStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper Z = AccelStepper(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper E = AccelStepper(AccelStepper::DRIVER, E_STEP_PIN, E_DIR_PIN);
MultiStepper Steppers = MultiStepper();

// Parser
ParserState parserState = {None};