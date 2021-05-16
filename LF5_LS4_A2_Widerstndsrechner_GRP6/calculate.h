#pragma once
double CalcResistorR20RTh(double R20, double IstTempr, double SpecificResistance, double ElectricalConductivity, double TemperatureCoefficientA, double TemperatureCoefficientB, int Element);
double CalcResistorWireRTh(double Länge, double Querschnitt, double IstTempr, double(*Tabelle)[2], int Element);
