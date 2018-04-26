#pragma once


struct FT_Config			/* Assume units in SI */
{
	__int32 countsPerForce = 1000000;		/* Calibration Counts per force unit. */
	__int32 countsPerTorque = 1000000;		/* Calibration Counts per torque unit. */
};