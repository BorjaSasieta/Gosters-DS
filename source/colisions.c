// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "colisions.h"
#include "estructures.h"
#include "So.h"
#include "tilejat.h"
#include "puntuacio.h"

//variables globals
extern Moneda mon[50];
extern bool torna;
extern bool segueix;
extern Jugador j;

//procediment colisioMoneda servira per fer sonar la moneda i per eliminar-la de la pantalla
void colisioMoneda(s32 x, s32 y)
{
	int i;
	for(i = 0; i < 50 ; i++)
	{
		if(mon[i].x == x && mon[i].y == y && mon[i].agafat == false)
		{
			//que soni la moneda
			mmEffect(SFX_COIN);
			mmEffect(SFX_COIN);
			mmEffect(SFX_COIN);
			j.puntuacio += 100;//pujem els punts
			//i que no estigui a la pantalla
			mon[i].agafat = true;
			actualitzarPuntuacio();// i ho actualitzem
		}
	}
}
//procediment de caure de nivell, per acabar el joc cuan ens morim amb "suicidi"
void caureDelNivell()
{
	gameOver();//cridem a la funció que acaba el joc
}

void colisioTransportador(s32 x, s32 y)
{
	//fem sonar l'efecte de so
	mmEffect(SFX_TRANSPORTADOR);
	//actualitzem la vida i la puntució
	j.puntuacio += 10000;
	j.vides += 1;
	//aturem la musica de fons
	mmStop();
	reiniciarTilejat();//reiniciem el tilejat
	reiniciarEnemics();//i els enemics
	segueix = true;
	torna = false;
}
// procediment que ens transporta al final del joc(credits)
void colisioTransportadorFinal(s32 x, s32 y)
{
	mmEffect(SFX_TRANSPORTADOR);
	//aturem la musica de fons
	mmStop();
	reiniciarTilejat();//reiniciem el tilejat
	iniciarText();//iniciem el text
	reiniciarEnemics();// reiniciem els enemics
	//escribim a la pantalla inferior
	NF_WriteText16(1, 0, 1, 1, "aixo es un projecte per al Centre d'estudis politecnics creat per Borja Sasieta i Sole que es alumne de DAM2T.\n\n Missatge d'en Borja: Gracies per jugar al meu joc");
	//ara a la superior
	NF_WriteText16(0, 0, 1, 1," el noi ha trobat el tresor mes preciat i aqui s'acava l'aventura ;) prema a per reiniciar");
	NF_UpdateTextLayers();// i actualitzem les capes de text
	//mentre no es premi la tecla A no sortirem	
	do
	{
		scanKeys();
		if(keysDown() & KEY_A)torna = false;	
	}while(torna == true);	
}
