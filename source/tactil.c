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
#include "tactil.h"
#include "estructures.h"

//variables globals

extern Moneda mon[50];
extern Jugador j;
extern s32 monedes;

//procediment que s'encarrega de comprovar si pitjem una moneda amb l'stylus
void cercarMonedesStylus(s16 fons_x ,s16 fons_y)
{
	int i = 0;//variable de bucle
	bool moneda = false;//ens retorna si hem agafat una moneda
	scanKeys();//per comprovar si pitjem
	if(keysHeld() & KEY_TOUCH)//a la pantalla tactil
	{
		for( i = 0; i<monedes;i++)
		{
			moneda = tocarSpriteMoneda(i+1,fons_x,fons_y);//cridem a la funció que ens retorna un bolea que ens indicara
			// si hem agafat una moneda
			if(moneda == true) colisioMoneda(mon[i].x,mon[i].y);//cridem al metode colisiomoneda per collir-la
		}
	}
}
//funció que ens retorna un bolea de si hem pitjat una moneda a la pantalla tactil 
bool tocarSpriteMoneda(u8 n,s16 fons_x ,s16 fons_y)
{	
	s16 monedaX = 0,monedaY = 0;//variables de la moneda
	bool retorn = false;// variable de retorn
	if(abs(NF_SPRITEOAM[1][n].x) < 256 && abs(NF_SPRITEOAM[1][n].y) < 192)// si la posició de l'sprite es a pantalla
	{
		//recollim les coordenades
		monedaX = NF_SPRITEOAM[1][n].x;
		monedaY = NF_SPRITEOAM[1][n].y;
		touchPosition sprTouch;//variable que recull les coordenades de l'stylus
		touchRead(&sprTouch);//la llegim ficantla a la variable creada anteriorment
		if((sprTouch.px>=monedaX) && (sprTouch.py>=monedaY) && (sprTouch.px<=monedaX+NF_SPR256VRAM[1][1].width) && (sprTouch.py<=monedaY+NF_SPR256VRAM[1][1].height))retorn = true;//si toquem moneda tornem true
	}
	return retorn;//retornem
}
//metode que cerca el jugador amb la posició de l'stylus
void cercarJugadorStylus(s16 fons_x , s16 fons_y)
{
	scanKeys();//es comprova que s'ha pitjat a la pantalla tactil
	if(keysHeld() & KEY_TOUCH)
	{
		tocarSpriteJugador(0,fons_x,fons_y);//es crida al procediment
	}
}
//procediment que ens retindra el jugador mentre el pitjem
void tocarSpriteJugador(u8 n,s16 fons_x ,s16 fons_y)
{	
	s16 cordX = 0,cordY = 0;//inicialitzem les variables
	cordX = NF_SPRITEOAM[1][n].x;//recollim les posicions
	cordY = NF_SPRITEOAM[1][n].y;
	touchPosition sprTouch;//variable per comparar les posicions
	scanKeys();//comprovem
	touchRead(&sprTouch);//desem les coordenades de l'stylus
	if((sprTouch.px>=cordX) && (sprTouch.py>=cordY) && (sprTouch.px<=cordX+NF_SPR256VRAM[1][0].width) && (sprTouch.py<=cordY+NF_SPR256VRAM[1][0].height))//si toquem el jugador
	{
		//ens quedara penjant
		j.x = cordX + fons_x;
		j.y = cordY + fons_y;
	}
}
