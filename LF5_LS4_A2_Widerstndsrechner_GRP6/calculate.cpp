//=================================================================================================================//
// **************************                        CALCULATE                         *************************** //
//=================================================================================================================//

// System includes
#include <cmath>

// User includes
#include "calculate.h"
#include "material.h"

//=================================================================================================================//


double CalcResistorR20RTh(double R20, double IstTempr, int Material)
{
	double R20RTh = 0;						// Rückgabewert Temperaturabhängiger Widerstand
	double DeltaTempr = IstTempr - 20;		// DeltaTemperatur vorbereiten

	R20RTh = R20 * ( 1 + MaterialSpez(3, Material) * DeltaTempr) + (MaterialSpez(4, Material) * pow(DeltaTempr, 2) );

	return R20RTh;
}

double CalcResistorWireRTh(double Länge, double Querschnitt, double IstTempr, int Material)
{
	double R20 = (MaterialSpez(1, Material) * Länge) / Querschnitt;							// R20 abhängig vom Leitermaterial vorbereiten
	double RTh = R20 * CalcResistorR20RTh(R20, IstTempr, Material);

	return RTh;
}