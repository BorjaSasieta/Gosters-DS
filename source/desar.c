// Includes c/c++
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//Includes NDS
#include <nds.h>
#include <fat.h>
#include <nf_lib.h>

// Includes nostres
#include "estructures.h"
#include "desar.h"

//variables globals
extern Jugador j;
extern Transportador t;
extern Enemic enemics[40];
extern Moneda mon[50];

void iniciarFitxers()
{
	// Intenta inicialitzar la FAT
	if (fatInitDefault()) 
	{
		// Si es correcte, canviem al ROOT del FAT
		chdir("fat:/");
	}
	else 
	{
		// si hi ha un error. s'atura el programa
		consoleDemoInit();	// Inicialitzem la consola de text
		iprintf("Error al iniciar FAT.\n");
		iprintf("Programa aturat.\n");
		while(1)
		{
			swiWaitForVBlank();//espera el sincronisme vertical
		}
	}
}

void llegir(char* fitxer)
{
	iniciarFitxers();//iniciem si es pot escriure
	// Variables
	FILE* apFitxer;	// Apuntador de l'arxiu
	int i = 0; //variable per als bucles
	//es llegueix l'arxiu
	apFitxer = fopen(fitxer, "rb");
	
	// i si no existeix
	if (apFitxer == NULL) 
	{
		//mostrem un error
		iprintf("No s'ha pogut llegir el fitxer o no existeix.\n\n");
		while(1)
		{
			swiWaitForVBlank();//espera el sincronisme vertical
		}	
	}
	// si en canvi no es així
	else
	{
		// Esborrem el contingut previ
		memset((void *)&j, 0, sizeof(Jugador));
		memset((void *)&t, 0, sizeof(Transportador));
		for(i = 0; i<50;i++)
		{
			memset((void *)&mon[i], 0, sizeof(Moneda));
		}
		for(i = 0; i<40;i++)
		{
			memset((void *)&enemics[i], 0, sizeof(Enemic));
		}
		// Llegim les dades i tanquem el fitxer
		fread((void *)&j, sizeof(Jugador), 1, apFitxer);
		fread((void *)&t, sizeof(Transportador), 1, apFitxer);
		for(i = 0; i<50;i++)
		{
			fread((void *)&mon[i], sizeof(Moneda), 1, apFitxer);
		}
		for(i = 0; i<40;i++)
		{
			fread((void *)&enemics[i], sizeof(Enemic), 1, apFitxer);
		}
		fclose(apFitxer);//tanquem el fitxer
	}
	//tornem el root a NitroFS
        chdir("nitro:/");
}

void desar(char* fitxer)
{
	iniciarFitxers();//iniciem el fat i comprovem que es pugui llegir i desar
	// Variables
	FILE* apFitxer;	// Apuntador
	int i = 0; //variable per als bucles
	// Creem l'arxiu
	apFitxer = fopen(fitxer, "wb");

	// Si no el podem crear
	if (apFitxer == NULL) 
	{
		//mostrem l'error
		iprintf("Error creant el fitxer.\n\n");
		while(1) 
		{
			swiWaitForVBlank();//espera el sincronisme vertical
		}	

	}
	//si en canvi podem llegir-lo
	else 
	{
		// escribim les dades i tanquem el fitxer
		fwrite((void *)&j, sizeof(Jugador), 1, apFitxer);
		fwrite((void *)&t, sizeof(Transportador), 1, apFitxer);
		for(i = 0; i<50;i++)
		{
			fwrite((void *)&mon[i], sizeof(Moneda), 1, apFitxer);
		}
		for(i = 0; i<40;i++)
		{
			fwrite((void *)&enemics[i], sizeof(Enemic), 1, apFitxer);
		}
		fclose(apFitxer);//tanquem el fitxer
	}
	//tornem el root a NitroFS
        chdir("nitro:/");
}
