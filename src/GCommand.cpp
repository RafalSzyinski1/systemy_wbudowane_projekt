#include "GCommand.h"
#include "Global.h"
#include "Parser.h"

short GCommand(float *params)
{
    if (isnanf(params[G]))
        return 0;

    switch ((int)params[G])
    {
    case 0:
        // Move fast
        break;
    case 1:
        // Move with framefate
        break;
    case 28:
        printer.isWaitFunction = 1;
        printer.waitFuntion = homing;
        break;
    case 92:
        G92(params);
        break;
    default:
        return -1;
        break;
    }
    return 0;
}

void G92(float *params)
{
    if (!isnanf(params[X]))
        XMotor.setCurrentPosition(params[X]);
    if (!isnanf(params[Y]))
        YMotor.setCurrentPosition(params[Y]);
    if (!isnanf(params[Z]))
        ZMotor.setCurrentPosition(params[Z]);
    if (!isnanf(params[E]))
        EMotor.setCurrentPosition(params[E]);
}