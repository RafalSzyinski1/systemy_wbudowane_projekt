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
            XMotor.move(params[X] * X_STEPS_PER_MM);

        if (!isnanf(params[Y]))
            YMotor.move(params[Y] * Y_STEPS_PER_MM);

        if (!isnanf(params[Z]))
            ZMotor.move(params[Z] * Z_STEPS_PER_MM);

        if (!isnanf(params[E]))
        {
            if (!(parserState.mState & M82))
                EMotor.move(params[E] * E_STEPS_PER_MM);
            else
                EMotor.moveTo(params[E] * E_STEPS_PER_MM);
        }

        while (XMotor.distanceToGo() != 0 ||
               YMotor.distanceToGo() != 0 ||
               ZMotor.distanceToGo() != 0 ||
               EMotor.distanceToGo() != 0)
        {
            XMotor.run();
            YMotor.run();
            ZMotor.run();
            EMotor.run();
        }
    }
    else
    {
        long absolute[4] = {0, 0, 0, 0};
        if (!isnanf(params[X]))
            absolute[0] = params[X] * X_STEPS_PER_MM;

        if (!isnanf(params[Y]))
            absolute[1] = params[Y] * Y_STEPS_PER_MM;

        if (!isnanf(params[Z]))
            absolute[2] = params[Z] * Z_STEPS_PER_MM;

        if (!isnanf(params[E]))
        {
            if (!(parserState.mState & M82))
            {
                EMotor.move(params[E] * E_STEPS_PER_MM);
                absolute[3] = EMotor.targetPosition();
            }
            else
                absolute[3] = params[E] * E_STEPS_PER_MM;
        }
        Steppers.moveTo(absolute);

        while (XMotor.distanceToGo() != 0 ||
               YMotor.distanceToGo() != 0 ||
               ZMotor.distanceToGo() != 0 ||
               EMotor.distanceToGo() != 0)
            Steppers.run();
    }
}

void G28(float *params)
{
    short allnan = 0;
    if (isnan(params[X]) && isnan(params[Y]) && isnan(params[Z]))
        allnan = 1;

    if (allnan || !isnan(params[X]))
    {
        XMotor.setSpeed(X_MAX_SPEED);
        while (!XendStop.isPressed())
        {
            XendStop.loop();
            XMotor.runSpeed();
        }

        XMotor.stop();
        XMotor.setCurrentPosition(0);
    }

    if (allnan || !isnan(params[Y]))
    {
        YMotor.setSpeed(Y_MAX_SPEED);
        while (!YendStop.isPressed())
        {
            YendStop.loop();
            YMotor.runSpeed();
        }
        YMotor.stop();
        YMotor.setCurrentPosition(0);
    }

    if (allnan || !isnan(params[Z]))
    {
        ZMotor.setSpeed(Z_MAX_SPEED);
        while (!ZendStop.isPressed())
        {
            ZendStop.loop();
            ZMotor.runSpeed();
        }
        ZMotor.stop();
        ZMotor.setCurrentPosition(0);
    }
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