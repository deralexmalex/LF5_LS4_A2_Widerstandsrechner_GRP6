/*
**

material.cpp
Alles was mit den Materialeigenschaften zu tun
hat wird in dieser Datei zusammnegefasst.



/
GetMaterialConf
BuildMaterialArray
PutLog
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <locale>
#include <vector>

#include "material.h"



using namespace std;

string NameOfMaterial[4] = { "Silber", "Kupfer", "Gold", "Aluminium" };

string *PointerNameOfMaterial =& NameOfMaterial[0];

double MaterialProperties[4][4] =
{
    {0.0165, 60.6, 0.0038, 0.7},
    {0.0178, 56.2, 0.0039,0.6},
    {0.023, 43.5, 0.0039, 0.5 },
    {0.0286, 35.0, 0.0037, 1.3}
};

double SpecificResistanceOfMaterial[4] = { 0.0165, 0.0178, 0.023, 0.0286 };

double ElectricalConductivityOfMaterial[4] = { 60.6, 56.2, 43.5, 35.0 };

double TemperatureCoefficientA[4] = { 0.0038, 0.0039, 0.0039, 0.0037 };

double TemperatureCoefficientB[4] = { 0.7, 0.6, 0.5, 1.3 };