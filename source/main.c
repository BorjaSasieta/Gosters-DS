// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "presentacio.h"
#include "So.h"
#include "nivell1.h"
#include "nivell2.h"
#include "nivell3.h"
#include "nivell4.h"
#include "estructures.h"
#include "puntuacio.h"
#include "menu.h"
#include "tilejat.h"

//varables globals

Enemic enemics[40];
Moneda mon[50];
Jugador j;
Transportador t;
bool torna;
bool segueix;
bool final;

//capseleres de funcions i procediments
void joc();
//funció principal del joc
int main()
{
	//inicialitzem el joc i els splash
	iniciar();
	soInicial();
	splash();
	inici();	
	// Bucle (es repeteix per sempre)
	while(1) 
	{
		scanKeys();//mirem si teclejem alguna cosa
		if(keysDown() & KEY_TOUCH)//si toquem la pantalla inferior
		{
			//iniciem els booleans
			torna = true;
			segueix = false;
			final = false;
			joc();//iniciem el joc
			reiniciarTilejat();//reiniciem el tilejat si sortim de la partida
			inici();//i tornem a iniciar
		}
		swiWaitForVBlank();		// Espera el sincronisme vertical
	}
	return 0;
}
//procediment que inicia el joc
void joc()
{
	//inicialitzem el jugador
	memset(&j, 0, sizeof(Jugador));
	//aturem la musica de fons
	mmStop();
	//i la eliminem de la memoria
	mmUnload(MOD_LEYENDADELBESO);
	//eliminem el tilejat del fons
	NF_ResetTiledBgBuffers();
	NF_DeleteTiledBg(0,3);
	NF_DeleteTiledBg(1,0);
	iniciarMenuInicial();
	//primer nivell
	nivell1();
	if(segueix == true) nivell2();//segon nivell
	if(segueix == true) nivell3();//tercer nivell
	if(segueix == true) nivell4();//darrer nivell
}
