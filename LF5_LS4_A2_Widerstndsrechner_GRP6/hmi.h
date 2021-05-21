#ifndef HMI_H
#define HMI_H
#include <string>


// Ausgabe Funktionen
void HelloUserHead();
void menMainMenu();
void menPickMaterial();
void printResult(double result);
void InputOK();


// Hybride Ausgabe/Eingabe Funktionen
double WantedParameter(std::string AddText, int direction);


// Benutzereingaben Auswertung & Navigation
void GetNavStringFromUser(int& tmpStrinStat, int& tmpInt, char& tmpChar);
double GetMathStringFromUser(int direction);
int MenuLimiter(int max, int tmpInt);
int goTo(char buchstabe, int ruecksprungweite);


// String Auswertung (Unterstützend)
bool ThereIsAnyNumber(std::string input);
bool ThereIsAnyLetter(std::string input);
bool ThereIsAnyLetOSymb(std::string input);
bool ThereIsAnyMathSymbol(std::string input);

#endif // !HMI_H

