#include <Arduino.h>

#include "MCommand.h"
#include "Global.h"

void M17(float *params)
{
    if (!isnanf(params[X]))
        XMotor.enableOutputs();
    if (!isnanf(params[Y]))
        YMotor.enableOutputs();
    if (!isnanf(params[Z]))
        ZMotor.enableOutputs();
    if (!isnanf(params[E]))
        EMotor.enableOutputs();
    if (isnanf(params[X]) &&
        isnanf(params[Y]) &&
        isnanf(params[Z]) &&
        isnanf(params[E]))
    {
        XMotor.enableOutputs();
        YMotor.enableOutputs();
        ZMotor.enableOutputs();
        EMotor.enableOutputs();
    }
}

void M84(float *params)
{
    if (!isnanf(params[X]))
        XMotor.disableOutputs();
    if (!isnanf(params[Y]))
        YMotor.disableOutputs();
    if (!isnanf(params[Z]))
        ZMotor.disableOutputs();
    if (!isnanf(params[E]))
        EMotor.disableOutputs();
    if (isnanf(params[X]) &&
        isnanf(params[Y]) &&
        isnanf(params[Z]) &&
        isnanf(params[E]))
    {
        XMotor.disableOutputs();
        YMotor.disableOutputs();
        ZMotor.disableOutputs();
        EMotor.disableOutputs();
    }
}

short MCommand(float *params)
{
    if (isnanf(params[M]))
        return 0;

    switch ((int)params[M])
    {
    case 17:
        M17(params);
        break;
    case 82:
    case 83:
        // Relative, Absolute codes (ignore)
        break;
    case 18:
    case 84:
        M84(params);
        break;
    case 104:
        // TODO: hotend fun
        break;
    case 105:
        if (addMessage("T0:200.0/200.0 T1:100.0/100.0") == -1) // TODO: Temp message
            return -1;
        break;
    case 107:
        // TODO: fan off
        break;
    case 109:
        // TODO: hotend fun
        break;
    case 110:
        parserState.mState |= M110;
        parserState.lastNumberLine = -1;
        break;
    case 140:
        // TODO: hot bed fun
        break;
    default:
        return -1;
        break;
    }

    return 0;
}