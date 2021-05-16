//=================================================================================================================//
// **************************                        CALCULATE                         *************************** //
//=================================================================================================================//

// System includes
#include <cmath>

// User includes
#include "calculate.h"

//=================================================================================================================//


double CalcResistorR20RTh(double R20, double IstTempr, double SpecificResistance, double ElectricalConductivity, double TemperatureCoefficientA, double TemperatureCoefficientB,int Element)
{
	double R20RTh = 0;						// R�ckgabewert Temperaturabh�ngiger Widerstand
	double DeltaTempr = IstTempr - 20;		// DeltaTemperatur vorbereiten

	R20RTh = R20 * (1 + Tabelle[Element][3] * DeltaTempr + Tabelle[Element][4] * pow(DeltaTempr, 2));

	return R20RTh;
}

double CalcResistorWireRTh(double L�nge, double Querschnitt, double IstTempr, double(* Tabelle)[2], int Element)
{
	double R20 = (Tabelle[Element][1] * L�nge) / Querschnitt;							// R20 abh�ngig vom Leitermaterial vorbereiten
	double RTh = R20 * CalcResistorR20RTh(R20, IstTempr, Tabelle, Element);

	return RTh;
}