// material.cpp 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip> 

#include "material.h"

using namespace std;

const double MaterialProperties[4][4] =
{
    {0.0165, 60.6, 0.0038, 0.7},
    {0.0178, 56.2, 0.0039,0.6},
    {0.023, 43.5, 0.0039, 0.5 },
    {0.0286, 35.0, 0.0037, 1.3}
};



// Materialnamen
// -------------
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

