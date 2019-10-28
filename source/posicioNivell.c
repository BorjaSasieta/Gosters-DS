// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "So.h"
#include "camera.h"
#include "posicioNivell.h"
#include "estructures.h"
#include "tilejat.h"
#include "enemics.h"
#include "puntuacio.h"

//variables globals

extern s32 enem;
extern s32 monedes;
extern Jugador j;
extern Moneda mon[50];
extern Enemic enemics[40];
extern Transportador t;

//ens carrega l'audio del nivell
void carregarAudio()
{
	//carreguem l'audio definit
	mmLoadEffect(SFX_JUMP);
	mmLoadEffect(SFX_COIN);
	mmLoadEffect(SFX_COP);
	mmLoadEffect(SFX_TRANSPORTADOR);
	mmLoad(MOD_ANDES);
	// i l'iniciem
	mmStart(MOD_ANDES,MM_PLAY_LOOP);
}

//procediment que cerca les cordenades del fons per la camera
void crearCordenades(s16 *cord_x, s16 *cord_y)
{
	*cord_x = j.x -128;
	*cord_y = j.y -96;
	if(*cord_x < 0) *cord_x = 0;
	if(*cord_y < 0) *cord_y = 0; 
	if(*cord_x > NF_CMAP[0].width - 256) *cord_x = NF_CMAP[0].width - 256;
	if(*cord_y > NF_CMAP[0].height - 192) *cord_y = NF_CMAP[0].height - 192;
}
//procediment que ens inicia la posicio del jugador per mostrar-lo en pantalla
void posicioCordenades(s16 posx, s16 posy)
{
	j.x = j.x - posx -16;
	j.y = j.y - posy -16; 
}
//procediment per iniciar les posicions del jugador
void inicialitzarPosicioJugador()
{
	j.x = 280;
	j.y = 80;
	j.salt = false;
	if(j.puntuacio == (int)NULL)//si la puntuació es nula (es a dir que començem) ho posarem a 
	{
		j.puntuacio = 0;
		j.vides = 5;
	}
}

//inicia el jugador al nivell
void iniciarJugador(s16 *x, s16 *y)
{
	//iniciem la seva posició
	inicialitzarPosicioJugador();
	//cercem les coordenades del fons
	crearCordenades(*&x,*&y);
	//col·loquem el personatje en la pantalla
	posicioCordenades(*x,*y);
}

//procediment per carregar la posicio de la moneda i que retorna un s32 que serà la cuantitat de monedes
s32 carregarPosicioMoneda()	
{
	//variables locals
	int i ,j ;
	int aux = 0;
	// recorrem tots els tiles
	for(i = 0; i < NF_CMAP[0].width;i = i+8)
	{
		for(j = 1; j < NF_CMAP[0].height; j = j+8)
		{
			// si el tile es el 4 de la moneda...
			if(NF_GetTile(0,i,j) == 4)
			{
				//guardem les posicions i per defecte no estan agafades
				mon[aux].x= i;
				mon[aux].y= j;
				mon[aux].agafat = false;
				//augmentem l'aux
				aux++;
			}
		}
	}
	//retornem l'auxiliar que serà el numero de monedes	
	return aux;
}
void carregarPosicioTransportador()
{
	//variables locals
	int i,j;
	// recorrem tots els tiles
	for(i = 0; i < NF_CMAP[0].width;i = i+8)
	{
		for(j = 1; j < NF_CMAP[0].height; j = j+8)
		{
			// si el tile es el 6 del transportador...
			if(NF_GetTile(0,i,j) == 6)
			{
				//guardem la posicio
				t.x= i;
				t.y= j;
			}
		}
	}
}

void carregarPosicioTransportadorFinal()
{
	//variables locals
	int i,j;
	// recorrem tots els tiles
	for(i = 0; i < NF_CMAP[0].width;i = i+8)
	{
		for(j = 1; j < NF_CMAP[0].height; j = j+8)
		{
			// si el tile es el 7 del transportador...
			if(NF_GetTile(0,i,j) == 7)
			{
				//guardem la posicio
				t.x= i;
				t.y= j;
			}
		}
	}
}

void actualitzar(s16 fons_x,s16 fons_y)
{
	//actualitzem altres objectes
	actualitzarMonedes(fons_x,fons_y);
	actualitzarEnemics(fons_x,fons_y);	
	actualitzarTransportador(fons_x,fons_y);
	// i movem l'scroll de la camara
	NF_ScrollBg(1,2, fons_x,fons_y);
	NF_ScrollBg(1,3, fons_x,fons_y);
	//les variables per esperar els moviments corresponents
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);
	oamUpdate(&oamMain);
}
void actualitzarDarrerNivell(s16 fons_x,s16 fons_y)
{
	//actualitzem altres objectes
	actualitzarMonedes(fons_x,fons_y);
	actualitzarEnemics(fons_x,fons_y);	
	actualitzarTransportadorFinal(fons_x,fons_y);
	// i movem l'scroll de la camara
	NF_ScrollBg(1,2, fons_x,fons_y);
	NF_ScrollBg(1,3, fons_x,fons_y);
	//les variables per esperar els moviments corresponents
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);
	oamUpdate(&oamMain);
}
