/****************************************************************************************************************************

 * @author: Ngo Kien Hoang
 * @email: hoang.ngo000187@gmail.com
 *
 * This file contains the library for PID Controler.

 ****************************************************************************************************************************/

/****************************************************************************************************************************
 * INCLUDE
 ****************************************************************************************************************************/
#include "AppInterface.h"

FLOAT fControlSignal = 0;
FLOAT fErrorSignal_Current = 0; // Error signal is the angle of deviation from the vertical of the robot (y axis)
FLOAT fErrorSignal_Before = 0;

FLOAT KP = 4.75;
FLOAT KI = 0;
FLOAT KD = 0;

FLOAT fIntegralValue = 0;
FLOAT fDerivativeValue = 0;

// Nonlinear coefficient
FLOAT M_Left = 0;
FLOAT M_Right = 0;

// Motor control signal (BOT)
FLOAT MotorLeftControl = 0;
FLOAT MotorRightControl = 0;

FLOAT fOutputLeft = 0;
FLOAT fOutputRight = 0;

FLOAT AppControl_PIDControler(FLOAT Angle, FLOAT Offset)
{
	fErrorSignal_Current = Angle + Offset;

	/* Intergral of e(t)dt (0-->t) */
	fIntegralValue += fErrorSignal_Current;

	/* Derivative: d(e(t))/dt */
	fDerivativeValue = fErrorSignal_Current - fErrorSignal_Before;

	/* Calculate control signal */
	fControlSignal = (KP)*(fErrorSignal_Current) + (KI)*(fIntegralValue) + (KD)*(fDerivativeValue);

	/* Update error signal */
	fErrorSignal_Before = fErrorSignal_Current;

	return fControlSignal;
}

void AppControl_ConvertMotorSignalControl(FLOAT ParamL, FLOAT ParamR)
{
	if (ParamL > 0)
	{
		MotorLeftControl = 400 - ParamL;
	}
	else if(ParamL < 0)
	{
		MotorLeftControl = -400 - ParamL;
	}
	else
	{
		MotorLeftControl = 0;
	}

	if (ParamR > 0)
	{
		MotorRightControl = 400 - ParamR;
	}
	else if(ParamR < 0)
	{
		MotorRightControl = -400 - ParamR;
	}
	else
	{
		MotorRightControl = 0;
	}

	AOSpeedMotorLeft(MotorLeftControl);
	AOSpeedMotorRight(MotorRightControl);
}

void AppControl_PIDLeftRightMotor(FLOAT Angle, FLOAT Offset)
{
	static FLOAT fOutput;

	fOutput = AppControl_PIDControler(Angle, Offset);

	if (fOutput > -5 && fOutput < 5)
	{
		fOutput = 0;
	}

	if (fOutput < -400)
	{
		fOutput = -400;
	}
	else if(fOutput > 400)
	{
		fOutput = 400;
	}

	fOutputLeft = fOutput;
	fOutputRight = fOutput;

	// Nonlinear equation between robot deflection angle and robot velocity
	if (fOutput > 0)
	{
		M_Left = 405 - (1/(fOutputLeft + 9))*5500;
		M_Right = 405 - (1/(fOutputRight + 9))*5500;

		/*
		 * If fOutputRight: 1 --> 400:
		 * 		+ fOutputRight = 1 		--> M_Right = -1.45
		 * 		+ fOutputRight = 4.58 	--> M_Right = 0
		 * 		+ fOutputRight = 10		--> M_Right = 115.52
		 * 		+ fOutputRight = 400	--> M_Right = 391.55
		 */
	}
	else if (fOutput < 0)
	{
		M_Left = -405 - (1/(fOutputLeft - 9))*5500;
		M_Right = -405 - (1/(fOutputRight - 9))*5500;
	}
	else
	{
		M_Left = 0;
		M_Right = 0;
	}

	AppControl_ConvertMotorSignalControl(M_Left, M_Right);
}
