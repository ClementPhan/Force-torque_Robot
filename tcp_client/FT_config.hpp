#pragma once


struct FT_Config			/* Assume units in SI */
{
	__int32 countsPerForce;		/* Calibration Counts per force unit. */
	__int32 countsPerTorque;	/* Calibration Counts per torque unit. */
	__int16 scaleFactors[6];	/* Additional scaling factor */
};