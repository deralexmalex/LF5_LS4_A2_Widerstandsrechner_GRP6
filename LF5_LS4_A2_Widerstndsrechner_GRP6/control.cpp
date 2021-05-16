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
#include "control.h"
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

	char choose = 0;

	ClsAndHello();
	menPickMaterial();

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