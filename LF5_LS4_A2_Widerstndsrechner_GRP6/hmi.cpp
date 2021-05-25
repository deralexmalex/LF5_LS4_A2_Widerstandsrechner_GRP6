//=================================================================================================================//
// **************************                           HMI                            *************************** //
//=================================================================================================================//
//
//	Inhalt:
//		Einordnung:			FS-LF5-LS4
//		Projekt: 			Aufgabe_ls4_02
//	Autor:
//		Name:				K�nigs, Bergs, Mommertz, Bremen
//		Organisaion:		Gruppe 6, BK-GuT

// System libraries
#include <iostream>
#include <locale>
#include <iomanip> 
#include <string>
#include <sstream>
#include <regex>

// Personal libraries
#include "hmi.h"
#include "material.h"

using namespace std;	
//=================================================================================================================//





// Ausgabe Funktionen
// ==================

void HelloUserHead() 
{
	system("cls");

	cout << "                 Willkommen im Widerstandrechner 2021" << endl;
	cout << "=======================================================================" << endl;
	cout << "  Navi	|| m -> Hauptmen� || b -> Zur�ck || e -> Programm beenden ||" << endl;
	cout << "=======================================================================" << endl << endl;
}

void menMainMenu()
{
	HelloUserHead();
	cout << " 1 | Temperaturabh�ngigen Widerstand (RTh) eines Materials berechnen" << endl;
	cout << " 2 | Temperaturabh�ngigen Widerstand (RTh) einer Leitung berechenen" << endl;
}

void menPickMaterial()
{
	HelloUserHead();
	cout << "Bitte eines der folgenden Materialien w�hlen: " << endl;
	for (int i = 1; i <= ArrMaterialPices(); i++)
	{
		cout << setfill(' ');
		cout << setw(2) << i;
		cout << " | " << ArrMaterialString(i) << endl;
	}
}


void printResult(double result, double laenge, double querschnitt, double temperatur , int MenuPointer, int MaterialPointer)
{
	HelloUserHead();
	cout << "Ergebnis des Temperaturabh�ngigen Wiederstandes";
	if (MenuPointer == 2)
	{
		cout << " einer Leitung" << endl;
		cout << "mit der L�nge:       " << laenge << " m" <<endl;
		cout << "mit dem Querschnitt: " << querschnitt << " mm2";
	}

	cout << "\nf�r das Material:    " << ArrMaterialString(MaterialPointer) << endl;
	cout << "bei der Temperatur:  " << temperatur << " �C"<<endl;
	cout << "lautet:              " << result << " Ohm" << endl << endl;
	system("pause");
}

void InputOK()
{
	cout << "\n'1' -> Weiter     ||     'beliebige Zahl' -> Eingaben Widerrufen" << endl;
}



// Hybride Ausgabe/Eingabe Funktionen
// ==================================

double WantedParameter(string AddText, int direction)
{
	cout << "\nBitte geben Sie " << AddText << " an.";

	// Hole Konfigurierten und ausgewerteten double-Wert von Benutzer
	return GetMathStringFromUser(direction);
}



// Benutzereingaben Auswertung & Navigation
// ========================================

void GetNavStringFromUser(int& tmpStrinStat, int& tmpInt, char& tmpChar)
{
	/* Folgende Variablen m�ssen in der aufrufenden Funktion deklariert werden,
	*  an GetStringFromUser() �bergeben werden und k�nnen anschlie�end direkt ausgewertet werden.
		int tmpStrinStat;
		int tmpInt;
		char tmpChar;
	*/

	// Lokale Variablen
	int strinLength = 0;
	string input;

	// Initalisiere potentiell global verf�gbare Variablen bei jedem Durchlauf
	tmpStrinStat = 0;
	tmpInt = 0;
	tmpChar = 0;


	do {
		tmpStrinStat = 0;

		cout << endl;
		cout << "Erwarte Navi Eingabe: ";	// Benutzeraufforderung
		getline(cin, input);				// Benutzereingabe

		// Bereite Werte vor
		// -----------------
		istringstream strin1;				// Definiere Eingabestream
		strin1.str(input);					// Streaminhalt mit String Variable f�llen
		strin1 >> tmpInt;					// Variable von Eingabe-Stream einlesen

		istringstream strin2;
		strin2.str(input);
		strin2 >> tmpChar;

		// Werte Eingabe aus
		// -----------------
		strinLength = input.length();		// Ermittle Anzahl der eingegebenen Zeichen

		if ((strinLength >= 1) && (false == ThereIsAnyLetOSymb(input)))		// Ganzzahl OK
			tmpStrinStat = 1;

		if (ThereIsAnyLetter(input) && (strinLength == 1))					// Char OK
			tmpStrinStat = 5;

		// Fange ung�ltige Char Eingaben ab
		// * Abh�ngig von goTo() 
		if ((tmpStrinStat == 5) && ((tmpChar != 'm') && (tmpChar != 'b') && (tmpChar != 'e')))
			tmpStrinStat = 0;

		// Wenn Eingabe nicht OK
		if (tmpStrinStat == 0)
			cout << "Ung�ltige Eingabe. Bitte erneut versuchen!" << endl;	

	} while (tmpStrinStat == 0);	// Wiederhole, solgane eingabe nicht OK
}

double GetMathStringFromUser(int direction)
{
	// Lokale Variablen
	string input;
	double tmpDdouble = 0;
	char tmpChar = 0;
	int strinLength = 0;
	int tmpStrinStat = 0;
	bool InputTrouble = false;

	do {
		tmpStrinStat = 0;

		cout << endl;
		cout << "Erwarte Eingabe als Zahl: ";	// Benutzeraufforderung
		getline(cin, input);					// Benutzereingabe


		// Werte auf double aus
		// --------------------
		istringstream strin1;					// Definiere Eingabestream
		strin1.str(input);						// Streaminhalt mit String Variable f�llen
		strin1 >> tmpDdouble;					// Variable von Eingabe-Stream einlesen

		// Wenn Eingabe nicht OK
		if (InputTrouble = ((ThereIsAnyLetOSymb(input) && (false == ThereIsAnyMathSymbol(input))) || (ThereIsAnyMathSymbol(input) && (false == ThereIsAnyNumber(input)))))
		{
			cout << "Ung�ltige Eingabe. Bitte erneut versuchen!" << endl;
			tmpStrinStat = 1;
		}

		// Wenn gefordert: Fange negative Eingabe ab
		if ((direction != 0) && (direction == +1) && (InputTrouble == false) && tmpDdouble <= 0)
		{
			cout << "Ung�ltige Eingabe. Eingabe muss positiv sein!" << endl;
			tmpStrinStat = 1;
		}
	} while (tmpStrinStat == 1);	// Wiederhole, solgane eingabe nicht OK

	return tmpDdouble;
}

int MenuLimiter(int max, int tmpInt)
{
	// Limitiere Men�eingabe entsprechend gew�nschter Men�l�nge
	if ( (max < tmpInt) || (1 > tmpInt) )
	{
		cout << "Fehler! Bitte Men�punkt zwischen " << 1 << " & " << max << " eingeben." << endl << endl;
		
		system("pause");
		return 0;
	}
	else if ( (max >= tmpInt) && (1 <= tmpInt))
		return 1;
}

int goTo(char buchstabe, int ruecksprungweite)
{
	// * Funktionen wandelt Buchstaben in Int, um Navigation zu erleichtern *
	//
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


// String Auswertung (Unterst�tzend)
// =================================

/* 
================== ThereIsAny<...> ===================
* Diese Funktionen durchsuchen Strings auf Zeichen
* um die Auswertung bei unkontrollierbaren, externen
* Eingaben zu vereinfachen.
*/

bool ThereIsAnyNumber(string input)
{
	bool value = false;

	if (regex_search(input.c_str(), regex("\\d")))
		value = true;

	return value;
}

bool ThereIsAnyLetter(string input)
{
	bool value = false;

	if ( regex_search(input.c_str(), regex("[a-z]")) || regex_search(input.c_str(), regex("[A-Z]")) )
		value = true;

	return value;
}

bool ThereIsAnyLetOSymb(string input)
{
	bool value = false;

	if ( regex_search(input.c_str(), regex("[a-z]")) || regex_search(input.c_str(), regex("[A-Z]")) || (regex_search(input.c_str(), regex("[^[:alnum:]]"))) )
		value = true;

	return value;
}

bool ThereIsAnyMathSymbol(string input)
{
	bool value = false;

	if ( regex_search(input.c_str(), regex(",")) || regex_search(input.c_str(), regex("-")) )
		value = true;

	return value;
}