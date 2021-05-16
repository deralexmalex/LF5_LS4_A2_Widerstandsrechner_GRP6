// material.h
#pragma once
const char* NameOfMaterial[];
int ArrMaterialien(void);

double SpecificResistanceOfMaterial[4] = { 0.0165, 0.0178, 0.023, 0.0286 };

double ElectricalConductivityOfMaterial[4] = { 60.6, 56.2, 43.5, 35.0 };

double TemperatureCoefficientA[4] = { 0.0038, 0.0039, 0.0039, 0.0037 };

double TemperatureCoefficientB[4] = { 0.7, 0.6, 0.5, 1.3 };
