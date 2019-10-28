// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "enemics.h"
#include "estructures.h"
#include "colisions.h"

//variables globals
extern s32 monedes;
extern Enemic enemics[40];
extern Jugador j;
extern bool torna;
extern s32 enem;
int contFrame = 0;
int varFrame = 0;

//funció per retornar el numero d'enemics mentre es carregen les seves posicions
s32 carregarPosicioEnemics()
{
	//variables locals
	int i ,j ;
	int aux = 0;
	// recorrem tots els tiles
	for(i = 0; i < NF_CMAP[0].width;i = i+8)
	{
		for(j = 1; j < NF_CMAP[0].height; j = j+8)
		{
			// si el tile es el 5 de l'enemic...
			if(NF_GetTile(0,i,j) == 5)
			{
				//guardem les posicions
				enemics[aux].x = i;
				enemics[aux].y = j;
				//i els boleans
				enemics[aux].cau = true;
				enemics[aux].viu = true;
				enemics[aux].xoca = false;
				//augmentem l'aux
				aux++;
			}
		}
	}
	//retornem l'auxiliar que serà el numero dels enemics	
	return aux;
}

//procediment que actualitza els enemics
void actualitzarEnemics(s32 x_fons, s32 y_fons)
{
	//agafa variables locals
	s32 i;
	s16 x[enem], y[enem];
	//un bucle que recorre tots els enemics
	for(i= 0;i<enem;i++)
	{
		if(enemics[i].viu == true)
		{
			//si està a la pantalla
			if(abs(enemics[i].x - x_fons) < 256 && abs(enemics[i].y - y_fons) < 192)
			{
				//guardem les coordenades en la variable creada
				x[i] = enemics[i].x - x_fons;
				y[i] = enemics[i].y - y_fons;
				moureEnemic(i);
				moureFrameEnemic(i);
			}
			//si no ho esta
			else
			{
				// la posem que no (molesti fora de la pantalla)
				x[i] = -64;
				y[i] = -64;
			}
		}
		else
		{
			// la posem que no molesti (fora de la pantalla)
			x[i] = -64;
			y[i] = -64;
			// i per no interferir al joc
			enemics[i].x = -64;
			enemics[i].y = -64;
		}
		NF_MoveSprite(1,i+2+monedes,x[i],y[i]);	//movem l'sprite per pantalla
	}
}
//procediment per moure enemics
void moureEnemic(s32 i)
{
	//comprovem la gravetat de l'enemic
	gravitarEnemic(i);
	if(enemics[i].xoca == false)//si no ha col·lisionat amb una paret
	{
		enemics[i].x -= 1;//es moura ca a l'esquerra
		if(enemics[i].x < 0) enemics[i].xoca = true;//si arriba al inici de la pantalla canvia de sentit
		//si col·lisiona amb una paret també cambia de sentit
		if (NF_GetTile(0,enemics[i].x,enemics[i].y) == 1 || NF_GetTile(0,enemics[i].x,enemics[i].y) == 2) enemics[i].xoca = true;
	}
	else 
	{
		//i l'enemic ha xocat es mou per l'altre sentit
		enemics[i].x += 1;
		if(enemics[i].x > NF_CMAP[0].width) enemics[i].xoca = false; // si arriba al final del nivell torna a canviar el sentit
		//si col·lisiona amb una paret igual que en l'altre cas canviara el sentit
		if (NF_GetTile(0,(enemics[i].x + 12),enemics[i].y) == 1 || NF_GetTile(0,(enemics[i].x + 12),enemics[i].y) == 2) enemics[i].xoca = false;
	}
}
//procediment per gravitar l'enemic
void gravitarEnemic(s32 i)
{
	enemics[i].cau = false;//l'enemic gravitarà
	//mentre no col·lisioni verticalment amb el terra traspassable o no traspassable
	if (NF_GetTile(0,(enemics[i].x + 8),(enemics[i].y + 6)) == 1 || NF_GetTile(0,(enemics[i].x + 8),(enemics[i].y + 6)) == 2) enemics[i].cau = true;
	if (enemics[i].cau == false)//si gravita
	{
		enemics[i].y += 1;//anira baixant de la pantalla
		if (NF_GetTile(0,(enemics[i].x + 8),(enemics[i].y + 6)) == 3)//si l'axafa el jugador
		{
			enemics[i].viu = false;//es mor el mateix
		}
	}
}
//procediment per moure el frame de l'enemic
void moureFrameEnemic(s32 i)
{
	contFrame++;//contem el contador per canviar de frame
	if(contFrame >= 60)// si arribem als 60 
	{
		canviarFrame();//canviem el frame
		contFrame = 0;// i el contador a 0
	}
	NF_SpriteFrame(1,i+2+monedes, varFrame);//mevem el frame de l'enemic
}
//procediment que canvia el frame
void canviarFrame()
{
	if (varFrame == 1)//si es el Segon 
	{	
		varFrame = 0;//posem el primer
	}	
	else// o en cas invers
	{
		varFrame = 1;
	}
}
