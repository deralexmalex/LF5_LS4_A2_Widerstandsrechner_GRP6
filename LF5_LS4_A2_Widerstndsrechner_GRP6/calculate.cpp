//=================================================================================================================//
// **************************                        CALCULATE                         *************************** //
//=================================================================================================================//
//
//	Inhalt:
//		Einordnung:			FS-LF5-LS4
//		Projekt: 			Aufgabe_ls4_02
//	Autor:
//		Name:				K�nigs, Bergs, Mommertz, Bremen
//		Organisaion:		Gruppe 6, BK-GuT
//

// System libraries
#include <cmath>

// Personal libraries
#include "calculate.h"
#include "material.h"

//=================================================================================================================//


double CalcResistorR20RTh(double IstTempr, int Material)
{
	double R20RTh = 0;						// R�ckgabewert Temperaturabh�ngiger Widerstand
	double DeltaTempr = IstTempr - 20;		// DeltaTemperatur vorbereiten

	R20RTh = MaterialSpez(1, Material) * ( 1 + MaterialSpez(3, Material) * DeltaTempr) + (MaterialSpez(4, Material) * pow(10, -6) * pow(DeltaTempr, 2) );

	return R20RTh;
}

double CalcResistorWireRTh(double L�nge, double Querschnitt, double IstTempr, int Material)
{
	double DeltaTempr = IstTempr - 20;
	double R20 = (MaterialSpez(1, Material) * L�nge) / Querschnitt;			// R20 abh�ngig vom Leitermaterial vorbereiten
	double RTh = R20 * ( 1 + MaterialSpez(3, Material) * DeltaTempr) + (MaterialSpez(4, Material) * pow(10, -6) * pow(DeltaTempr, 2) );

	return RTh;
}