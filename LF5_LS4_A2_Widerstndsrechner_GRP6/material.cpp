//=================================================================================================================//
// **************************                        Material                          *************************** //
//=================================================================================================================//

// Standard libarys 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip> 

// Personal libarys
#include "material.h"

using namespace std;
//=================================================================================================================//

// Werte Speicher & Auswertung
// ---------------------------
double SpecificResistanceOfMaterial[6] = { 0.0165, 0.0178, 0.023, 0.0286, 0.055, 0.12 };
double ElectricalConductivityOfMaterial[6] = { 60.6, 56.2, 43.5, 35.0, 18.2, 8.3 };
double TemperatureCoefficientA[6] = { 0.0038, 0.0039, 0.0039, 0.0037, 0.0048, 0.0042 };
double TemperatureCoefficientB[6] = { 0.7, 0.6, 0.5, 1.3, 18.2, 8.3 };

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

int ArrMaterialienPices()
{
    int counter = 0;
    for (counter = 0; NameOfMaterial[counter] != NULL; counter++); // Abzählen wieviele Elemente im Array sind
    return counter;
}

void ArrMaterialien()
{
    // Die Namen der Elemente auflisten (wird hier ausgeführt, d Übergabe des Arrays an HMI zu aufwendig)
    for (int i = 0; i < ArrMaterialienPices(); i++)
    {
        cout << setfill(' ');
        cout << setw(2) << i + 1;
        cout << " | " << NameOfMaterial[i] << endl;
    }
}

