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
double SpecificResistanceOfMaterial[4] = { 0.0165, 0.0178, 0.023, 0.0286 };
double ElectricalConductivityOfMaterial[4] = { 60.6, 56.2, 43.5, 35.0 };
double TemperatureCoefficientA[4] = { 0.0038, 0.0039, 0.0039, 0.0037 };
double TemperatureCoefficientB[4] = { 0.7, 0.6, 0.5, 1.3 };

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


// Materialnamen Stringspeicher & Auswertung / Ausgabe
// ---------------------------------------------------
const char* NameOfMaterial[] = { "Silber", "Kupfer", "Gold", "Aluminium" };

int ArrMaterialien()
{
    int counter, i;

    for (counter = 0; NameOfMaterial[counter] != NULL; counter++); // Abzählen wieviele Elemente im Array sind

    // Die Namen der Elemente auflisten (wird hier ausgeführt, d Übergabe des Arrays an HMI zu aufwendig)
    for (i = 0; i < counter; i++)
    {
        cout << setfill(' ');
        cout << setw(2) << i + 1;
        cout << " | " << NameOfMaterial[i] << endl;
    }
    return counter;
}

