#include <Arduino.h>

#include "MCommand.h"
#include "Global.h"

void M17(float *params)
{
    if (params[X] != NAN)
        XMotor.enableOutputs();
    if (params[Y] != NAN)
        YMotor.enableOutputs();
    if (params[Z] != NAN)
        ZMotor.enableOutputs();
    if (params[E] != NAN)
        EMotor.enableOutputs();
    if (params[X] == NAN &&
        params[Y] == NAN &&
        params[Z] == NAN &&
        params[E] == NAN)
    {
        XMotor.enableOutputs();
        YMotor.enableOutputs();
        ZMotor.enableOutputs();
        EMotor.enableOutputs();
    }
}

void M84(float *params)
{
    if (params[X] != NAN)
        XMotor.disableOutputs();
    if (params[Y] != NAN)
        YMotor.disableOutputs();
    if (params[Z] != NAN)
        ZMotor.disableOutputs();
    if (params[E] != NAN)
        EMotor.disableOutputs();
    if (params[X] == NAN &&
        params[Y] == NAN &&
        params[Z] == NAN &&
        params[E] == NAN)
    {
        XMotor.disableOutputs();
        YMotor.disableOutputs();
        ZMotor.disableOutputs();
        EMotor.disableOutputs();
    }
}

short MCommand(float *params)
{
    if (params[M] == NAN)
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