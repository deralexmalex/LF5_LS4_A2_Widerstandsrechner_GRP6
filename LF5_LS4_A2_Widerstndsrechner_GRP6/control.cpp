//=================================================================================================================//
// **************************                        MAINCICLE                         *************************** //
//=================================================================================================================//
//
//	Inhalt:
//		Einordnung:			FS-LF5-LS4
//		Projekt: 			Aufgabe_ls4_02
//	Autor:
//		Name:				Königs, Bergs, Mommertz, Bremen
//		Organisaion:		Gruppe 6, BK-GuT

// System libraries
#include <locale>

// Personal libraries
#include "calculate.h"
#include "hmi.h"
#include "material.h"

using namespace std;
//=================================================================================================================//
#include <iostream>

int main()
{
	locale::global(locale("German_germany"));

	// Variablendeklaration
	// ====================

	int tmpStrinStat;			// Temporär zu verwendender UserInput Status
	int tmpInt;					// Temporär zu verwendender UserInput int
	char tmpChar;				// Temporär zu verwendender UserInput char

	double ActTempr = 0, ActLeiterLaenge = 0, ActLeiterQuerschnitt = 0;		// Wertespeicher für Berechnungen

	int step = 1;				// Merker: aktueller Schritt
	int material = 0;			// Merker: Materialauswahl
	int MainMenuChoose = 0;		// Merker: Hauptmenüauswahl
	

	// Programm
	// ========
	do {
		switch (step) {

		// Hauptmenü (Auswahl Rechenziel)
		// ******************************
		case 1:
			menMainMenu();
			GetNavStringFromUser(tmpStrinStat, tmpInt, tmpChar);
			
			// Auswertung Menüauswahl
			if ((tmpStrinStat == 1) && (MenuLimiter(2, tmpInt) == 1))
			{
				MainMenuChoose = tmpInt;
				step++;					// Schrittziel: Materialauswahl
			}

			// Auswertung Navi
			if (tmpStrinStat == 5)
				step = step + goTo(tmpChar, 0);
			
			break;


		// Auswahl Material
		// ****************
		case 2:
			menPickMaterial();
			GetNavStringFromUser(tmpStrinStat, tmpInt, tmpChar);

			// Auswertung Menüauswahl
			if ((tmpStrinStat == 1) && (MenuLimiter(ArrMaterialPices(), tmpInt) == 1)) {
				material = tmpInt;

				switch (MainMenuChoose) {
				case 1:
					step = step + 1;	// Schrittziel: Eingabe Parameter für Hauptmenüpunkt 1
					break;
				case 2:
					step = step + 2;	// Schrittziel: Eingabe Parameter für Hauptmenüpunkt 2
				}
			}

			// Auswertung Navi
			if (tmpStrinStat == 5)
				step = step + goTo(tmpChar, 1);
			
			break;
		

		// Werte für Hauptmenüpunkt 1 einlesen
		// ***********************************
		case 3:
			do {
				// Lese Werte von Benutzer ein	
				HelloUserHead();
				ActTempr = WantedParameter("die Umgebungstemperatur in [°C]", 0);

				// Rückfrage ob Eingabe OK & Möglichkeit zu Navigieren
				InputOK();																			
				GetNavStringFromUser(tmpStrinStat, tmpInt, tmpChar);								
				if (tmpStrinStat == 5)
					step = step + goTo(tmpChar, 1);

			} while ((1 != tmpInt) && (5 != tmpStrinStat));	// Wiederhole Eingabe wenn Nutzer sagt: nicht OK
			
			if (5 != tmpStrinStat)		// Schrittziel: Berechnung & Ausgabe
				step = step + 2;
			
			break;
		

		// Werte für Hauptmenüpunkt 2 einlesen
		// ***********************************
		case 4:		
			do {
				// Lese Werte von Benutzer ein
				HelloUserHead();
				ActLeiterLaenge = WantedParameter("die Leitungslänge in [m]", +1);
				ActLeiterQuerschnitt = WantedParameter("den Leitungsquerschnitt in [mm2]", +1);
				ActTempr = WantedParameter("die Umgebungstemperatur in [°C]", 0);

				// Rückfrage ob Eingabe OK & Möglichkeit zu Navigieren
				InputOK();												
				GetNavStringFromUser(tmpStrinStat, tmpInt, tmpChar);
				if (tmpStrinStat == 5)
					step = step + goTo(tmpChar, 2);		

			} while ((1 != tmpInt) && (5 != tmpStrinStat));	// Wiederhole Eingabe wenn Nuter sagt: nicht OK
			
			if (5 != tmpStrinStat)		// Schrittziel: Berechnung & Ausgabe
				step = step + 2;
			
			break;
		

		// Berechnung & Ausgabe für Hauptmenüpunkt 1
		// *****************************************
		case 5:	
			printResult(CalcResistorR20RTh(ActTempr, material), 0, 0, ActTempr, MainMenuChoose, material);
			step = 1;					// Schrittziel: Hauptmenü

			break;


		// Berechnung & Ausgabe für Hauptmenüpunkt 2
		// *****************************************
		case 6:
			printResult(CalcResistorWireRTh(ActLeiterLaenge, ActLeiterQuerschnitt, ActTempr, material), ActLeiterLaenge ,ActLeiterQuerschnitt , ActTempr, MainMenuChoose, material);
			step = 1;					// Schrittziel: Hauptmenü

			break;
		}	


		// Navigation in Hauptmenü
		// ***********************
		if (step <= 0)				// Schrittziel: Hauptmenü
			step = 1;

	} while (step < 1000);			// Programm wiederholen oder abbrechen
	
	return 0;
}