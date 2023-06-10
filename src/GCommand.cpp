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
        setStartPosition();
        break;
    default:
        return -1;
        break;
    }
    return 0;
}