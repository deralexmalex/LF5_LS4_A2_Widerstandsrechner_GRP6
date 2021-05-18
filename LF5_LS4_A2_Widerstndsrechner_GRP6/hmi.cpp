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
#include "material.h"

using namespace std;		// Setze Standard Bibliothek
//=================================================================================================================//


void HelloUser() 
{
	cout << "                 Willkommen im Widerstandrechner 2021" << endl;
	cout << "=======================================================================" << endl;
	cout << "  Navi	|| m -> Hauptmen� || b -> Zur�ck || e -> Programm beenden ||" << endl;
	cout << "=======================================================================" << endl << endl;
}

void menMainMenu()
{
	cout << " 1 | RTh eines genormten Widerstandes (R20) berechnen " << endl;
	cout << " 2 | RTh einer Leitung berchenen" << endl;
}

void menPickMaterial()
{
	cout << "Bitte eines der folgenden Materialien w�hlen: " << endl;
	ArrMaterialien();
}

void printWantedParameter(string AddText)
{
	cout << "\nBitte geben Sie " << AddText << " an.";
}

void printResult(double result)
{
	cout << "\n\nDas Ergebnisse der Rechnung lautet: " << result << " Ohm" << endl <<endl;
	pause();
}

void InputOK()
{
	cout << "\n\nEingabe �bernehmen oder widerrufen?" << endl;
	cout << "*                '1' - Weiter" << endl;
	cout << "* 'Jede andere Zahl' - Wiederufen";
}

void CLS()
{
	system("cls");
}

void pause()
{
	system("pause");
}

void ClsAndHello()
{
	CLS();
	HelloUser();
}


int MenuLimiter(int min, int max, int tmpInt)
{
	if ((max < tmpInt) || tmpInt < min)
	{
		cout << "Fehler! Bitte Men�pubnkt zwischen " << min << " & " << max << " eingeben." << endl;
		pause();
		return 0;
		
	}
	else if ((max >= tmpInt) || tmpInt >= min)
		return 1;
}

int goToYN(char buchstabe)
{
	switch (buchstabe)
	{
	case 'n':	// Zur�ck in das letzte Men�
		return 0;
		break;

	case 'j':	// Einen Schritt zur�ck
		return 1;
		break;
	}
}

int goTo(char buchstabe, int ruecksprungweite)
{
	// Bei Erweiterung oder Reduzierung um Optionen in GetStringFromUser()
	// Char Abfangmechanismus anpassen

	switch (buchstabe)
	{
	case 'm':	// Zur�ck in das letzte Men�
		return -1000;
		break;

	case 'b':	// Einen Schritt zur�ck
		return -ruecksprungweite;
		break;

	case 'e':	// Programm sofort verlassen
		return 1000;
		break;
	}
}

void GetStringFromUser(int iWant, int &tmpStrinStat, int &tmpInt, double &tmpDdouble, char &tmpChar)
{
	/* Folgende Variablen m�ssen in der aufrufenden Funktion deklariert werden,
	*  an GetStringFromUser() �bergeben werden und k�nnen anschlie�end direkt ausgewertet werden.
		int tmpStrinStat;
		int tmpInt;
		double tmpDdouble;
		char tmpChar;
	*/

	// iWant Legende
	//  0 = Alle Typen
	// 10 = Zahl allgemein
	// 11 = Ganzzahl
	// 12 = Gleitpunktzahl
	// 15 = Ganzzahl & Buchstabe
	// 20 = Buchstabe

	// Lokale Variablen
	int strinLength = 0;
	string input;

	// Initalisiere Global verf�gbare Variablen bei jedem Durchlauf
	tmpStrinStat = 0;
	tmpInt = 0;
	tmpDdouble = 0;
	tmpChar = 0;
	

	do {
		cout << endl;
		cout << "Erwarte eingabe: ";	// Benutzeraufforderung
		getline(cin, input);			// Benutzeringabe

		// Bereite Werte vor
		// -----------------
		istringstream strin1;			// Definiere Eingabestream
		strin1.str(input);				// Streaminhalt mit String Variable f�llen
		strin1 >> tmpInt;				// Variable von Eingabe-Stram einlesen

		istringstream strin2;
		strin2.str(input);
		strin2 >> tmpDdouble;

		istringstream strin3;
		strin3.str(input);
		strin3 >> tmpChar;

		strinLength = input.length();	// Ermittle anzahl der eingegebenen Zeichen


		// Werte Eingabe aus
		if ((strinLength >= 1) && (tmpInt == tmpDdouble))					// Ganzzahl OK
			tmpStrinStat = 1;

		if ((strinLength >= 1) && (tmpInt != tmpDdouble))					// Gleitpunkzzahl OK
			tmpStrinStat = 2;

		if (((tmpDdouble == 0) && (strinLength > 1)) || (strinLength == 0))	// Eingabe ung�ltig
			tmpStrinStat = 0;

		//if ((tmpDdouble == 0) && (strinLength == 1) && (tmpChar != 1))
		if ((tmpDdouble == 0) && (strinLength == 1) && (tmpChar != 1))		// Char OK
			tmpStrinStat = 5;


		// iWant (Datentyp x)
		switch (iWant) {
		case 0:			//  0 = Alles
			tmpStrinStat = tmpStrinStat;
			break;
		case 10:		// 10 = Zahl allgemein
			if ((tmpStrinStat != 1) && (tmpStrinStat != 2))
				tmpStrinStat = 0;
			break;
		case 11:		// 11 = Ganzzahl
			if (tmpStrinStat != 1)
				tmpStrinStat = 0;
			break;
		case 12:		// 12 = Gleitkommazahl
			if (tmpStrinStat != 2)
				tmpStrinStat = 0;
			break;
		case 15:		// 15 = Ganzzahl & Buchstabe
			if ((tmpStrinStat != 1) && (tmpStrinStat != 5))
				tmpStrinStat = 0;
			break;
		case 17:		// 17 = Zahl & Buchstabe
			if ((tmpStrinStat != 1) && (tmpStrinStat != 2) && (tmpStrinStat != 5))
				tmpStrinStat = 0;
			break;
		case 20:		// 20 = Buchstabe
			if (tmpStrinStat != 5 )
				tmpStrinStat = 0;
			break;
		default:		// Ung�ltiger Wert an Funktion �bergeben
			cout << "\n\n!!! FEHLER !!!\nFunktion 'GetStringFromUser' falsch deklariert!\n\n";
			tmpStrinStat = -1;
			break;
		}


		// Fange ung�ltige Char Eingaben ab
		// * Abh�ngig von goTo() 
		if ((tmpStrinStat == 5) && ((tmpChar != 'm') && (tmpChar != 'b') && (tmpChar != 'e')))
			tmpStrinStat = 0;


		if (tmpStrinStat == 0)
			cout << "Ung�ltige Eingabe. Bitte erneut versuchen!" << endl;		// Print Eingabe nicht i.O.
	} while (tmpStrinStat == 0);
}

