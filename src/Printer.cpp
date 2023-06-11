#include <Arduino.h>

#include "Printer.h"
#include "Global.h"
#include "Configure.h"

void Printerloop()
{
    XendStop.loop();
    YendStop.loop();
    ZendStop.loop();

    if (XMotor.distanceToGo() != 0 ||
        YMotor.distanceToGo() != 0 ||
        ZMotor.distanceToGo() != 0 ||
        EMotor.distanceToGo() != 0)
    {
        // Serial.print("X:");
        // Serial.println(XMotor.distanceToGo());
        // Serial.print("Y:");
        // Serial.println(YMotor.distanceToGo());
        // Serial.print("Z:");
        // Serial.println(ZMotor.distanceToGo());
        // Serial.print("E:");
        // Serial.println(EMotor.distanceToGo());

        if (parserState.gState & G91)
        {
            XMotor.run();
            YMotor.run();
            ZMotor.run();
            EMotor.run();
        }
        else
        {
            Steppers.run();
            if (parserState.mState & M82)
                EMotor.run();
        }

        if (XMotor.distanceToGo() == 0 &&
            YMotor.distanceToGo() == 0 &&
            ZMotor.distanceToGo() == 0 &&
            EMotor.distanceToGo() == 0)
            printer.wait = 0;
        }
}
