#ifndef PRINTER_H_
#define PRINTER_H_

struct PrinterState
{
    unsigned int feedrate;
    unsigned int fanspeed;

    // hotend
    unsigned int target_hotend_temp;
    unsigned int hotend_temp; // TODO; temp var (replace getTemp);
};

short setHotendTemperature();
short homing();

#endif // PRINTER_H_