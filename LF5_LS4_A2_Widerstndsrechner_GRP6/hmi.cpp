//=================================================================================================================//
// **************************                           HMI                            *************************** //
//=================================================================================================================//

// System includes
#include <iostream>
#include <locale>
#include <iomanip> 
#include <string>
#include <sstream>

// User includes
#include "hmi.h"

using namespace std;		// Setze Standard Bibliothek
//=================================================================================================================//


//  Funktionen

void HelloUser() 
{
	cout << "                 Willkommen im Widerstandrechner 2021" << endl;
	cout << "======================================================================" << endl << endl;
	cout << "       Navi ||  h -> Hauptmenü    ||    b -> Zurück    ||" << endl;
	cout << "       Navi ||  a -> Eingabe abbrechen & zurück in das letztw Menü  ||" << endl;
	cout << "======================================================================" << endl << endl;
}

int menMainMenu()
{
	int input = 0;

	cout << " 1 | RTh eines genormten Widerstandes (R20) berechnen " << endl;
	cout << " 2 | RTh einer Leitung berchenen" << endl;

	cout << endl;
	cout << "Erwarte Eingabe: ";
	cin >> input;
	cout << endl;

	return input;
}

int menPickMaterial(string* arr[5])
{
	int input = 0;

	cout << "Bitte eines der folgenden Materialien wählen:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << setfill(' ');
		cout << setw(2) << i + 1 << " | " << arr[i];
	}
	return input;
}

int menSubMenu()
{

}


// Basis Funktionen

int goTo(char& buchstabe)
{
	int goTo = 0;

	if (buchstabe == 'a')	// Zurück in das letzte Menü
	{
		goTo = -1000;
	}
	if (buchstabe == 'b')	// Einen Schritt zurück
	{
		goTo = -1;
	}

	if (buchstabe == 'n')	// Einen Schriit vor
	{
		goTo = +1;
	}

	if (buchstabe == 'e')	// Programm sofort verlassen
	{
		goTo = 1000;
	}
}

void CLS()
{
	system("ctl");
}

void ClsAndHello()
{
	CLS();
	HelloUser();
}

void GetStringFromUser(int* strinStatus, int& ganzzahl, double& kommazahl, char& buchstabe, int iWant)
{
	// iWant Legende
	//  0 = Alle Typen
	// 10 = Zahl allgemein
	// 11 = Ganzzahl
	// 12 = Gleitpunktzahl
	// 20 = Buchstabe

	int strinLength = 0;
	string input;

	do {
		cout << endl;
		cout << "Erwarte eingabe: ";	// Benutzeraufforderung
		getline(cin, input);			// Benutzeringabe

		// Bereite Werte vor
		// -----------------
		istringstream strin1;			// Definiere Eingabestream
		strin1.str(input);				// Streaminhalt mit String Variable füllen
		strin1 >> ganzzahl;				// Variable von Eingabe-Stram einlesen

		istringstream strin2;
		strin2.str(input);
		strin2 >> kommazahl;

		istringstream strin3;
		strin3.str(input);
		strin3 >> buchstabe;

		strinLength = input.length();	// Ermittle anzahl der eingegebenen Zeichen

		// Werte Eingabe aus
		// -----------------
		if ((strinLength >= 1) && (ganzzahl == kommazahl))					// Ganzzahl OK
			*strinStatus = 1;

		if ((strinLength >= 1) && (ganzzahl != kommazahl))					// Gleitpunkzzahl OK
			*strinStatus = 2;

		if (((kommazahl == 0) && (strinLength > 1)) || (strinLength == 0))	// Eingabe ungültig
			*strinStatus = 0;

		if ((kommazahl == 0) && (strinLength == 1) && (buchstabe != 1))		// Char OK
			*strinStatus = 5;

		// iWant (Datentyp x)
		// ------------------
		switch (iWant) {
		case 0:			//  0 = Ganzzahl
			*strinStatus = *strinStatus;
			break;
		case 10:		// 10 = Zahl allgemein
			if ((*strinStatus != 1) && (*strinStatus != 2))
				*strinStatus = 0;
			break;
		case 11:		// 11 = Ganzzahl
			if (*strinStatus != 1)
				*strinStatus = 0;
			break;
		case 12:		// 12 = Gleitkommazahl
			if (*strinStatus != 2)
				*strinStatus = 0;
			break;
		case 20:		// 20 = Buchstabe
			if (*strinStatus != 5)
				*strinStatus = 0;
			break;
		default:		// Ungültiger Wert an Funktion übergeben
			cout << "\n\n!!! FEHLER !!!\nFunktion 'GetStringFromUser' falsch deklariert!\n\n";
			*strinStatus = -1;
			break;
		}

		if (*strinStatus == 0)
			cout << "Ungültige Eingabe. Bitte erneut versuchen!" << endl;		// Print Eingabe nicht i.O.

	} while (*strinStatus == 0);
}

