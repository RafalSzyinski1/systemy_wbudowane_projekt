#include <Arduino.h>

#include "Printer.h"
#include "Global.h"

short homing()
{
    if (XendStop.getState() == LOW)
        XMotor.runSpeed();
    else
        XMotor.stop();

    if (YendStop.getState() == LOW)
        YMotor.runSpeed();
    else
        YMotor.stop();

    if (ZendStop.getState() == LOW)
        ZMotor.runSpeed();
    else
        ZMotor.stop();

    if (XendStop.getState() == HIGH &&
        YendStop.getState() == HIGH &&
        ZendStop.getState() == HIGH)
    {
        printer.isWaitFunction = 0;
        printer.waitFuntion = nullptr;
        // TODO set position on the middle
        XMotor.setCurrentPosition(0);
        YMotor.setCurrentPosition(0);
        ZMotor.setCurrentPosition(0);
    }

    return 0;
}

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
