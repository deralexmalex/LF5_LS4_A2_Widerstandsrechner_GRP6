//
//	Inhalt:
//		Einordnung:			FS-LF5-LS4
//		Projekt: 			Aufgabe_ls4_02
//		Thema:				XXXXX
//	Autor:
//		Name:				Bergs, Bremen, K�nigs, Mommertz
//		Organisaion:		BK-GuT
//
//	Datum:
//		Erstellt:			XX.04.2021
//		Letzte �nderung:	XX.05.2021
//
//
//=================================================================================================================//
// **************************                        MAINCICLE                         *************************** //
//=================================================================================================================//

// User includes
#include "calculate.h"
#include "hmi.h"
#include "material.h"

// Standard libarys
#include <locale>

using namespace std;		// Setze Standard Bibliothek
//=================================================================================================================//


int main()
{
	locale::global(locale("German_germany"));

	// Variablendeklaration
	int tmpStrinStat;
	int tmpInt;
	double tmpDdouble;
	char tmpChar;

	double ActR20 = 0, ActTempr = 0, ActLeiterLaenge = 0, ActLeiterQuerschnitt = 0;

	int step = 1;
	int material = 0;
	int MainMenuChoose = 0;
	
	// Programm
	do {
		ClsAndHello();

		switch (step)
		{

		// Hauptmenü (Auswahl Rechenziel)
		// ******************************
		case 1:
			menMainMenu();
			GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
			
			if ((tmpStrinStat == 1) && (MenuLimiter(2, tmpInt) == 1)) {
				MainMenuChoose = tmpInt;
				step++;
			}

			if (tmpStrinStat == 5)
				step = step + goTo(tmpChar, 0);
			
			break;

		// Auswahl Material
		// ****************
		case 2:
			menPickMaterial();
			GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);

			if ((tmpStrinStat == 1) && (MenuLimiter(4, tmpInt) == 1)) {
				material = tmpInt;

				switch (MainMenuChoose) {
				case 1:
					step = step + 1;
					break;
				case 2:
					step = step + 2;
				}
			}

			if (tmpStrinStat == 5)
				step = step + goTo(tmpChar, 1);
			
			break;
		
		// Werte für Hauptmenüpunkt 1 einlesen
		// ***********************************
		case 3:
			do {
				printWantedParameter("den Widerstand in [Ohm]");					// Lese Werte ein
				ActR20 = GetMathStringFromUser(+1);

				printWantedParameter("die Umgebungstemperatur in [°C]");
				ActTempr = GetMathStringFromUser(0);

				InputOK();															// Rückfrage ob Eingabe OK
				GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);	// + Möglichkeit zu Navigieren
				if (tmpStrinStat == 5)
					step = step + goTo(tmpChar, 1);
			
			} while ((1 != tmpInt) && (5 != tmpStrinStat));
			
			if (5 != tmpStrinStat)
				step = step + 2;
			
			break;
		
		// Werte für Hauptmenüpunkt 2 einlesen
		// ***********************************
		case 4:		
			do {
				printWantedParameter("die Leitungslänge in [m]");					// Lese Werte ein
				ActLeiterLaenge = GetMathStringFromUser(+1);

				printWantedParameter("den Leitungsquerschnitt in [mm2]");
				ActLeiterQuerschnitt = GetMathStringFromUser(+1);

				printWantedParameter("die Umgebungstemperatur in [°C]");
				ActTempr = GetMathStringFromUser(0);

				InputOK();															// Rückfrage ob Eingabe OK
				GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);	// + Möglichkeit zu Navigieren
				if (tmpStrinStat == 5)
					step = step + goTo(tmpChar, 2);
			
			} while ((1 != tmpInt) && (5 != tmpStrinStat));
			
			if (5 != tmpStrinStat)
				step = step + 2;
			
			break;
		
		// Berechnung & Ausgabe für Hauptmenüpunkt 1
		// *****************************************
		case 5:		
			printResult(CalcResistorR20RTh(ActR20, ActTempr, material));
			step = 1;
			break;

		// Berechnung & Ausgabe für Hauptmenüpunkt 2
		// *****************************************
		case 6:
			printResult(CalcResistorWireRTh(ActLeiterLaenge, ActLeiterQuerschnitt, ActTempr, material));
			step = 1;
			break;

		default:
			if (step <= 0)	// Zurück zum Menü
				step = 1;
		}	
	} while (step < 1000);	// Programm Zyklus oder Programm verlassen
	return 0;
}