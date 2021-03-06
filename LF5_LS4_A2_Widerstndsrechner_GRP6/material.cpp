//=================================================================================================================//
// **************************                        MATERIAL                          *************************** //
//=================================================================================================================//
//
//	Inhalt:
//		Einordnung:			FS-LF5-LS4
//		Projekt: 			Aufgabe_ls4_02
//	Autor:
//		Name:				K?nigs, Bergs, Mommertz, Bremen
//		Organisaion:		Gruppe 6, BK-GuT

// System libarys 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Personal libarys
#include "material.h"

using namespace std;
//=================================================================================================================//

// Werte Speicher & Auswertung
// ---------------------------
double SpecificResistanceOfMaterial[6] = { 0.0165, 0.0178, 0.023, 0.0286, 0.055, 0.12 };
double ElectricalConductivityOfMaterial[6] = { 60.6, 56.2, 43.5, 35.0, 18.2, 8.3 };
double TemperatureCoefficientA[6] = { 0.0038, 0.0039, 0.0039, 0.0037, 0.0048, 0.0042 };
double TemperatureCoefficientB[6] = { 0.7, 0.6, 0.5, 1.3, 1.0, 6.0 };

double MaterialSpez(int Konstante, int Material)
{
    switch (Konstante)
    {
    case 1:
        return SpecificResistanceOfMaterial[Material-1];
        break;
    case 2:
        return ElectricalConductivityOfMaterial[Material-1];
        break;
    case 3:
        return TemperatureCoefficientA[Material-1];
        break;
    case 4:
        return TemperatureCoefficientB[Material-1];
        break;
    }
}

// Titel Speicher & Auswertung
// ---------------------------
const char* NameOfMaterial[] = { "Silber", "Kupfer", "Gold", "Aluminium", "Wolfram", "Zinn" };

int ArrMaterialPices()
{
    int counter = 0;
    for (counter = 0; NameOfMaterial[counter] != NULL; counter++); // Abz?hlen wieviele Elemente im Array sind
    return counter;
}

string ArrMaterialString(int pointer)
{
    return NameOfMaterial[pointer - 1];
}
