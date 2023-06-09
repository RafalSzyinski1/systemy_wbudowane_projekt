#ifndef PRINTER_H_
#define PRINTER_H_

enum ToolCode
{
    TNone = -1,
    T0,
};

struct ToolState
{
    ToolCode toolCode;
    // hotend
    unsigned int targetHotendTemp;
    unsigned int hotendTemp; // TODO; temp var (replace getTemp);
};

typedef short (*WaitFuntion)();

struct PrinterState
{
    ToolCode toolSelected;
    unsigned int feedrate;
    unsigned int fanspeed;

    short isWaitFunction;
    WaitFuntion waitFuntion;
};

short homing();
short setStartPosition();

#endif // PRINTER_H_