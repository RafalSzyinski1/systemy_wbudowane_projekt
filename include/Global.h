#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <AccelStepper.h>
#include <MultiStepper.h>

#include "ConfigurePin.h"

extern AccelStepper X;
extern AccelStepper Y;
extern AccelStepper Z;
extern AccelStepper E;
extern MultiStepper Steppers;

#endif // GLOBAL_H_