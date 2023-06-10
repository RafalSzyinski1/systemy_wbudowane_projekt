#include "GCommand.h"
#include "Global.h"
#include "Parser.h"
#include "Configure.h"

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
        printer.wait = 1;
        G28(params);
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

void G28(float *params)
{
    short allnan = 0;
    short isfinish = 1;
    if (isnan(params[X]) && isnan(params[Y]) && isnan(params[Z]))
        allnan = 1;

    if (allnan || !isnan(params[X]))
    {
        if (XendStop.getState() == LOW)
        {
            XMotor.runSpeed();
            isfinish = 0;
        }
        else
        {
            XMotor.stop();
            XMotor.setCurrentPosition((WIDTH / 2.0) * X_STEPS_PER_MM);
        }
    }

    if (allnan || !isnan(params[Y]))
    {
        if (YendStop.getState() == LOW)
        {
            YMotor.runSpeed();
            isfinish = 0;
        }
        else
        {
            YMotor.stop();
            YMotor.setCurrentPosition((DEPTH / 2.0) * Y_STEPS_PER_MM);
        }
    }

    if (allnan || !isnan(params[Z]))
    {
        if (ZendStop.getState() == LOW)
        {
            ZMotor.runSpeed();
            isfinish = 0;
        }
        else
        {
            ZMotor.stop();
            ZMotor.setCurrentPosition(HEIGHT * Z_STEPS_PER_MM);
        }
    }

    if (isfinish)
        printer.wait = 0;
}

void G92(float *params)
{
    if (!isnanf(params[X]))
        XMotor.setCurrentPosition(params[X] * X_STEPS_PER_MM);
    if (!isnanf(params[Y]))
        YMotor.setCurrentPosition(params[Y] * Y_STEPS_PER_MM);
    if (!isnanf(params[Z]))
        ZMotor.setCurrentPosition(params[Z] * Z_STEPS_PER_MM);
    if (!isnanf(params[E]))
        EMotor.setCurrentPosition(params[E] * E_STEPS_PER_MM);
}