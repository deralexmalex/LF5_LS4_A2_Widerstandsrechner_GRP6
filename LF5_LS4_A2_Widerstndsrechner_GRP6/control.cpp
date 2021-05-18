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
//#include "control.h"
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
		case 1:		// Hauptmenü (Auswahl Rechenziel)
			menMainMenu();
			GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
			
			if ((tmpStrinStat == 1) && (MenuLimiter(1, 2, tmpInt) == 1)) {
				MainMenuChoose = tmpInt;
				step++;
			}

			if (tmpStrinStat == 5)
				step = step + goTo(tmpChar, 0);
			break;

		case 2:		// Auswahl Material
			menPickMaterial();
			GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);

			if ((tmpStrinStat == 1) && (MenuLimiter(1, 4, tmpInt) == 1)) {
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
		
		case 3:		// Werte für Menüpunkt 1 einlesen
			do {
				printWantedParameter("den Widerstand in [Ohm]");
				GetStringFromUser(10, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				ActR20 = tmpInt;

				printWantedParameter("die Umgebungstemperatur in [°C]");
				GetStringFromUser(10, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				ActTempr = tmpInt;

				InputOK();
				GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				if (tmpStrinStat == 5)
					step = step + goTo(tmpChar, 1);
			} while ((1 != tmpInt) && (5 != tmpStrinStat));
			if (5 != tmpStrinStat)
				step = step + 2;
			break;
		
		case 4:		// Werte für Menüpunkt 2 einlesen
			do {
				printWantedParameter("die Leitungslänge in [m]");
				GetStringFromUser(10, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				ActLeiterLaenge = tmpInt;

				printWantedParameter("den Leitungsquerschnitt in [mm2]");
				GetStringFromUser(10, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				ActLeiterQuerschnitt = tmpInt;

				printWantedParameter("die Umgebungstemperatur in [°C]");
				GetStringFromUser(10, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				ActTempr = tmpInt;

				InputOK();
				GetStringFromUser(15, tmpStrinStat, tmpInt, tmpDdouble, tmpChar);
				if (tmpStrinStat == 5)
					step = step + goTo(tmpChar, 2);
			} while ((1 != tmpInt) && (5 != tmpStrinStat));
			if (5 != tmpStrinStat)
				step = step + 2;
			break;

		case 5:
			printResult(CalcResistorR20RTh(ActR20, ActTempr, material));
			step = 1;
			break;

		case 6:
			printResult(CalcResistorWireRTh(ActLeiterLaenge, ActLeiterQuerschnitt, ActTempr, material));
			step = 1;
			break;

		default:
			if (step <= 0)	// Zurück zum Menü
				step = 1;
		}	
	} while (step < 1000);
	


/*
	do
	{
		choose = 0;
		HelloUser();
		mainmenu();

	} while (choose != 'e');

	return 0;
}

int mainmenu()										// Hauptmenü
{



	do
	{
		int choose;
		choose = 0;
		menMainMenu();


		switch (choose)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	} while (true);

*/

	return 0;
}