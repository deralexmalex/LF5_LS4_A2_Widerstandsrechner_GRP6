//=================================================================================================================//
// **************************                           HMI                            *************************** //
//=================================================================================================================//
//
//	Inhalt:
//		Einordnung:			FS-LF5-LS4
//		Projekt: 			Aufgabe_ls4_02
//	Autor:
//		Name:				Königs, Bergs, Mommertz, Bremen
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
	cout << "  Navi	|| m -> Hauptmenü || b -> Zurück || e -> Programm beenden ||" << endl;
	cout << "=======================================================================" << endl << endl;
}

void menMainMenu()
{
	HelloUserHead();
	cout << " 1 | Temperaturabhängigen Widerstand (RTh) eines Materials berechnen" << endl;
	cout << " 2 | Temperaturabhängigen Widerstand (RTh) einer Leitung berechenen" << endl;
}

void menPickMaterial()
{
	HelloUserHead();
	cout << "Bitte eines der folgenden Materialien wählen: " << endl;
	ArrMaterialien();		// Array wird in material.cpp ausgewertet und ausgegeben
							// (aufgrund von Parameterübergabe Problemen)
}


void printResult(double result, double laenge, double querschnitt, double temperatur , int MenuPointer, int MaterialPointer)
{
	HelloUserHead();
	cout << "Ergebnis des Temperaturabhängigen Wiederstandes";
	if (MenuPointer == 2)
	{
		cout << " einer Leitung" << endl;
		cout << "mit der Länge:       " << laenge << " m" <<endl;
		cout << "mit dem Querschnitt: " << querschnitt << " mm2";
	}

	cout << "\nfür das Material:    " << ArrMaterialString(MaterialPointer) << endl;
	cout << "bei der Temperatur:  " << temperatur << " °C"<<endl;
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
	/* Folgende Variablen müssen in der aufrufenden Funktion deklariert werden,
	*  an GetStringFromUser() übergeben werden und können anschließend direkt ausgewertet werden.
		int tmpStrinStat;
		int tmpInt;
		char tmpChar;
	*/

	// Lokale Variablen
	int strinLength = 0;
	string input;

	// Initalisiere potentiell global verfügbare Variablen bei jedem Durchlauf
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
		strin1.str(input);					// Streaminhalt mit String Variable füllen
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

		// Fange ungültige Char Eingaben ab
		// * Abhängig von goTo() 
		if ((tmpStrinStat == 5) && ((tmpChar != 'm') && (tmpChar != 'b') && (tmpChar != 'e')))
			tmpStrinStat = 0;

		// Wenn Eingabe nicht OK
		if (tmpStrinStat == 0)
			cout << "Ungültige Eingabe. Bitte erneut versuchen!" << endl;	

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
		strin1.str(input);						// Streaminhalt mit String Variable füllen
		strin1 >> tmpDdouble;					// Variable von Eingabe-Stream einlesen

		// Wenn Eingabe nicht OK
		if (InputTrouble = ((ThereIsAnyLetOSymb(input) && (false == ThereIsAnyMathSymbol(input))) || (ThereIsAnyMathSymbol(input) && (false == ThereIsAnyNumber(input)))))
		{
			cout << "Ungültige Eingabe. Bitte erneut versuchen!" << endl;
			tmpStrinStat = 1;
		}

		// Wenn gefordert: Fange negative Eingabe ab
		if ((direction != 0) && (direction == +1) && (InputTrouble == false) && tmpDdouble <= 0)
		{
			cout << "Ungültige Eingabe. Eingabe muss positiv sein!" << endl;
			tmpStrinStat = 1;
		}
	} while (tmpStrinStat == 1);	// Wiederhole, solgane eingabe nicht OK

	return tmpDdouble;
}

int MenuLimiter(int max, int tmpInt)
{
	// Limitiere Menüeingabe entsprechend gewünschter Menülänge
	if ( (max < tmpInt) || (1 > tmpInt) )
	{
		cout << "Fehler! Bitte Menüpunkt zwischen " << 1 << " & " << max << " eingeben." << endl << endl;
		
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
	case 'm':	// Zurück in das letzte Menü
		return -1000;
		break;

	case 'b':	// Einen Schritt zurück
		return -ruecksprungweite;
		break;

	case 'e':	// Programm sofort verlassen
		return 1000;
		break;
	}
}

/*
void GetStringFromUser(int iWant, int &tmpStrinStat, int &tmpInt, double &tmpDdouble, char &tmpChar)
{
	// Folgende Variablen müssen in der aufrufenden Funktion deklariert werden,
	//*an GetStringFromUser() übergeben werden und können anschließend direkt ausgewertet werden.
	//	int tmpStrinStat;
	//	int tmpInt;
	//	double tmpDdouble;
	//	char tmpChar;

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

	// Initalisiere Global verfügbare Variablen bei jedem Durchlauf
	tmpStrinStat = 0;
	tmpInt = 0;
	tmpDdouble = 0;
	tmpChar = 0;
	

	do {
		cout << endl;
		cout << "Erwarte eingabe: ";	// Benutzeraufforderung
		getline(cin, input);			// Benutzereingabe

		// Bereite Werte vor
		// -----------------
		istringstream strin1;			// Definiere Eingabestream
		strin1.str(input);				// Streaminhalt mit String Variable füllen
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

		if (((tmpDdouble == 0) && (strinLength > 1)) || (strinLength == 0))	// Eingabe ungültig
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
		default:		// Ungültiger Wert an Funktion übergeben
			cout << "\n\n!!! FEHLER !!!\nFunktion 'GetStringFromUser' falsch deklariert!\n\n";
			tmpStrinStat = -1;
			break;
		}


		// Fange ungültige Char Eingaben ab
		// * Abhängig von goTo() 
		if ((tmpStrinStat == 5) && ((tmpChar != 'm') && (tmpChar != 'b') && (tmpChar != 'e')))
			tmpStrinStat = 0;


		if (tmpStrinStat == 0)
			cout << "Ungültige Eingabe. Bitte erneut versuchen!" << endl;		// Print Eingabe nicht i.O.
	} while (tmpStrinStat == 0);
}
*/




// String Auswertung (Unterstützend)
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

