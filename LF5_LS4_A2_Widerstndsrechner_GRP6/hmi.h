#ifndef HMI_H
#define HMI_H
#include <string>

void HelloUser();
void menMainMenu();
void menPickMaterial();
void InputOK();
void printResult(double result);
void printWantedParameter(std::string AddText);
void ClsAndHello();
void CLS();
void pause();
void GetStringFromUser(int iWant, int& tmpStrinStat, int& tmpInt, double& tmpDdouble, char& tmpChar);
double GetMathStringFromUser(int direction);
int goTo(char buchstabe, int ruecksprungweite);
int MenuLimiter(int max, int tmpInt);

#endif // !HMI_H

