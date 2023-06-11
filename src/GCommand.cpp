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
    case 1:
        if (!printer.wait)
            G0(params);
        break;
    case 28:
        G28(params);
        break;
    case 90:
        parserState.gState &= ~G91;
        break;
    case 91:
        parserState.gState |= G91;
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

void G0(float *params)
{
    if (!isnanf(params[F]))
        printer.feedrate = (int)params[F];

    if (parserState.gState & G91)
    {
        if (!isnanf(params[X]))
        {
            XMotor.setSpeed(printer.feedrate * X_STEPS_PER_MM);
            XMotor.move(params[X] * X_STEPS_PER_MM);
            printer.wait = 1;
        }

        if (!isnanf(params[Y]))
        {
            YMotor.setSpeed(printer.feedrate * Y_STEPS_PER_MM);
            YMotor.move(params[Y] * Y_STEPS_PER_MM);
            printer.wait = 1;
        }

        if (!isnanf(params[Z]))
        {
            ZMotor.setSpeed(printer.feedrate * Z_STEPS_PER_MM);
            ZMotor.move(params[Z] * Z_STEPS_PER_MM);
            printer.wait = 1;
        }

        if (!isnanf(params[E]))
        {
            printer.wait = 1;
            EMotor.setSpeed(printer.feedrate * E_STEPS_PER_MM);

            if (!(parserState.mState & M82))
                EMotor.move(params[E] * E_STEPS_PER_MM);
            else
                EMotor.moveTo(params[E] * E_STEPS_PER_MM);
        }
    }
    else
    {
        long absolute[4] = {0, 0, 0, 0};
        if (!isnanf(params[X]))
        {
            XMotor.setSpeed(printer.feedrate * X_STEPS_PER_MM);
            absolute[0] = params[X] * X_STEPS_PER_MM;
            printer.wait = 1;
        }
        if (!isnanf(params[Y]))
        {
            YMotor.setSpeed(printer.feedrate * Y_STEPS_PER_MM);
            absolute[1] = params[Y] * Y_STEPS_PER_MM;
            printer.wait = 1;
        }
        if (!isnanf(params[Z]))
        {
            ZMotor.setSpeed(printer.feedrate * Z_STEPS_PER_MM);
            absolute[2] = params[Z] * Z_STEPS_PER_MM;
            printer.wait = 1;
        }
        if (!isnanf(params[E]))
        {
            EMotor.setSpeed(printer.feedrate * E_STEPS_PER_MM);
            printer.wait = 1;
            if (!(parserState.mState & M82))
                EMotor.move(params[E] * E_STEPS_PER_MM);
            else
                absolute[3] = params[E] * X_STEPS_PER_MM;
        }
        Steppers.moveTo(absolute);
    }
}

void G28(float *params)
{
    printer.wait = 1;

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