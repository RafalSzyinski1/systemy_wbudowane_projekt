#include <Arduino.h>

#include "Printer.h"
#include "Global.h"
#include "Configure.h"

void Printerloop()
{
    XendStop.loop();
    YendStop.loop();
    ZendStop.loop();

    if (XMotor.distanceToGo() != 0)
        XMotor.run();
    if (YMotor.distanceToGo() != 0)
        YMotor.run();
    if (ZMotor.distanceToGo() != 0)
        ZMotor.run();
    if (EMotor.distanceToGo() != 0)
        EMotor.run();
}
