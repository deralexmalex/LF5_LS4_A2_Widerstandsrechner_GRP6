#ifndef CALCULATE_H
#define CALCULATE_H

double CalcResistorR20RTh(double R20, double IstTempr, double(*Tabelle)[2], int Element);
double CalcResistorWireRTh(double Länge, double Querschnitt, double IstTempr, double(*Tabelle)[2], int Element);

#endif // !calculate.h