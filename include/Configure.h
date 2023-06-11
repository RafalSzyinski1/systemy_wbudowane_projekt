#ifndef CONFIGURE_H_
#define CONFIGURE_H_

// Serial Port
#define BAUDRATE 115200

// Printer
#define WIDTH 100
#define DEPTH 100
#define HEIGHT 100

// Stepper
#define X_MAX_SPEED 500.0
#define X_ACCELERATION 3000.0
#define X_STEPS_PER_MM 64

#define Y_MAX_SPEED 500.0
#define Y_ACCELERATION 3000.0
#define Y_STEPS_PER_MM 64

#define Z_MAX_SPEED 500.0
#define Z_ACCELERATION 3000.0
#define Z_STEPS_PER_MM 64

#define E_MAX_SPEED 500.0
#define E_ACCELERATION 3000.0
#define E_STEPS_PER_MM 64

// Tools
#define NUM_OF_TOOLS 1

// Min/Max hotend temperature
#define MINTEMP 80
#define MAXTEMP 200
#define AUTOTEMP 0.98

#endif // CONFIGURE_H_