#include <Arduino.h>

#include "Printer.h"
#include "Global.h"
#include "Configure.h"

void Printerloop()
{
    XendStop.loop();
    YendStop.loop();
    ZendStop.loop();
}
