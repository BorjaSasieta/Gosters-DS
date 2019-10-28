// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "estructures.h"
#include "puntuacio.h"

//variables globals
extern Jugador j;
extern s32 monedes;
extern s32 enem;

//procediment que ens prepara la puntuació
void preparaPuntuacio()
{
	// Inicialitza el motor del text (requereix tenir els fons tilejats inicialitzats)
	NF_InitTextSys(0);
	// Carrega la font del text
	NF_LoadTextFont16("fnt/font16", "normal", 256, 256, 0);
	// Crea una capa de text
	NF_CreateTextLayer16(0, 0, 0, "normal");
	NF_UpdateTextLayers();	//actualitzem les capes de text
}
//procediment per actualitzar-la
void actualitzarPuntuacio()
{
	//variable per a desar el text
	char elText[50];
	//escribim la puntucació per pantalla
	sprintf(elText,"Vides: %d \n\n Puntuacio: %d", j.vides,j.puntuacio);
	NF_WriteText16(0, 0, 1, 4, elText);
	NF_UpdateTextLayers();	//actualitzem les capes de text
}


