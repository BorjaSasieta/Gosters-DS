// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "menu.h"
#include "desar.h"

//variable global

extern bool torna;

//funcions

void iniciarMenuInicial()
{
	//variables de text
	char elText[50];
	char elText2[50];
	bool pitjar = false; //bolea que ens dira si hem pijat el menu o no.
	// Inicialitza el motor del text (requereix tenir els fons tilejats inicialitzats)
	NF_InitTextSys(0);
	// Carrega la font del text
	NF_LoadTextFont16("fnt/font16", "normal", 256, 256, 0);
	// Crea una capa de text
	NF_CreateTextLayer16(0, 0, 0, "normal");
	sprintf(elText,"A- Iniciar joc desde l'inici.\n");//imprimim
	sprintf(elText2,"B- si vols carregar la partida desada.\n");//imprimim
	NF_WriteText16(0, 0, 0, 4, elText);//mostrem el text
	NF_WriteText16(0, 0, 0, 5, elText2);//mostrem el text
	NF_UpdateTextLayers();	//actualitzem les capes de text
	while (pitjar == false)//mentre no pitjem es mostrara
	{
		//si pitjem un boto
		scanKeys();
		if(keysDown() & KEY_A) pitjar = true;//i es l'a sortim
		if(keysDown() & KEY_B)//si es el b llegim l'arxiu
		{
			llegir("Gosters.sav");
			pitjar = true;
		}
	}	
}

void menuStart()
{
	//variables de text
	char elText[50];
	char elText2[50];
	char elText3[50];
	char elText4[50];
	char elText5[50];
	bool pitjar = false;//bolea per saber si sortim del menu o no
	// Inicialitza el motor del text (requereix tenir els fons tilejats inicialitzats)
	NF_InitTextSys(0);
	// Carrega la font del text
	NF_LoadTextFont16("fnt/font16", "normal", 256, 256, 0);
	// Crea una capa de text
	NF_CreateTextLayer16(0, 0, 0, "normal");
	//imprimim els valors
	sprintf(elText,"A- continua.\n");
	sprintf(elText2,"B- continua i desa.\n");
	sprintf(elText3,"X- surt i desa.\n");
	sprintf(elText4,"Y- surt sense desar.\n");
	sprintf(elText5,"Nota: cuan desis la partida s'esborrara la desada anteriorment.\n");
	//finalment ho mostrem
	NF_WriteText16(0, 0, 0, 0, elText);
	NF_WriteText16(0, 0, 0, 1, elText2);
	NF_WriteText16(0, 0, 0, 2, elText3);
	NF_WriteText16(0, 0, 0, 3, elText4);
	NF_WriteText16(0, 0, 0, 4, elText5);
	NF_UpdateTextLayers();	//actualitzem les capes de text	
	while (pitjar == false)//mentre no pitjem es seguira veient
	{
		//si pitjem 
		scanKeys();
		if(keysDown() & KEY_A) pitjar = true;//A sortim
		if(keysDown() & KEY_B) //b desem
		{
			desar("Gosters.sav");
		}
		if(keysDown() & KEY_X) //x desem i sortim
		{
			pitjar = true;
			desar("Gosters.sav");
			torna = false;
		}
		if(keysDown() & KEY_Y)//y sortim del joc (i no desem)
		{
			pitjar = true;
			torna = false;
		}
	}
	NF_ClearTextLayer16(0,0);//netejem la capa de text
	NF_UpdateTextLayers();	//actualitzem les capes de text	
}
