#ifndef calculate.h

double CalcResistorR20RTh(double R20, double IstTempr, double(*Tabelle)[2], int Element);
double CalcResistorWireRTh(double L�nge, double Querschnitt, double IstTempr, double(*Tabelle)[2], int Element);

#endif // !calculate.h