// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "So.h"
#include "camera.h"
#include "estructures.h"
#include "colisions.h"
#include "enemics.h"
#include "nivell1.h"
#include "nivell2.h"
#include "nivell3.h"
#include "nivell4.h"
#include "puntuacio.h"
#include "posicioNivell.h"
#include "menu.h"
#include "tactil.h"

//variables globals

extern Moneda mon[50];
extern Jugador j;
extern Transportador t;
extern s32 monedes;
extern s32 enem;
extern Enemic enemics[40];
extern bool final;

//procediment per moure el jugador amb els parametres per referencia que seran totes les variables del jugador
void moureJugador(s16 fons_x,s16 fons_y)
{
	//iniciem les posicions en la que el personatje s'inicialitzi en pantalla
	s16 personatje_x = j.x - fons_x;
	s16 personatje_y = j.y - fons_y;
	actualitzarPuntuacio();//actualitzem la puntuació
	//mirem si es mou el personatge amb el procediment seguent
	moviment(fons_x,fons_y,&personatje_x,personatje_y);
	if(j.vides <= 0) caureDelNivell();//si ens quedem sense vides anem a morir-nos
	j.salt = false;//iniciem el salt a flase(es a dir que no saltarem mentre estiguem a l'aire)
	int i = j.x,k;//variables per als bucles
	//mentre cualsevol pixel de l'sprite del jugador estigue en col·lisió
	while(j.salt == false && i < (j.x + 22))//mentre no poguem saltar 
	{
		for(k = j.y + 15; k > j.y;k--)//comprobem pixel a pixel la col·lisió
		{
			if (NF_GetTile(0,i,k) == 1 || NF_GetTile(0,i,k) == 2) j.salt = true;//si estem a terra podrem saltar
			if (NF_GetTile(0,i-5,k) == 4) colisioMoneda(i-5,k);//mirem si hem agafat una moneda
			// i si cau al precipici...
			if(NF_GetTile(0,i,k) == 3) caureDelNivell();//ens morim
			if (NF_GetTile(0,i-5,k) == 6) colisioTransportador(i-5,k);// si colisionem amb el final del nivell
			if (final == true && NF_GetTile(0,i-5,k) == 7) colisioTransportadorFinal(i-5,k);//o al final del joc
		}
		i++;//augmentem la variable
	}      
	//cuan estiguem a l'aire
       	if (j.salt == false)
	{
		//el jugador cau
		j.y += 1;
		//cerquem si matem un enemic
		cercarMortEnemic(fons_x,fons_y,personatje_x,&personatje_y);
	}
	if(keysDown() & KEY_A && j.salt == true)
        {
		//o bé es salta
		saltar(90,fons_x,fons_y,personatje_x, &personatje_y);
        }
	//funcions de trampes(per agafar monedes i el jugador amb l'stylus)
	cercarMonedesStylus(fons_x,fons_y);
	cercarJugadorStylus(fons_x,fons_y);
	//actualitzem la posició del jugador
	NF_MoveSprite(1,0,personatje_x,personatje_y);
}
//procediment que fara la funcio de saltar amb els parametres corresponents i els que modifica per referencia
void saltar(int pujada,s16 fons_x, s16 fons_y,s16 pX,s16 *pY)
{
	//efecte sonor de saltar
	mmEffect(SFX_JUMP);
	bool puja = true;//variable per controlar el salt
	int cont = 0;//contador de la pujada del salt
	s32 i,k;//variables per als bucles
	//bucle per incrementar la y, es a dir per a pujar 
	while(puja == true && cont < pujada)
	{
		for(i = j.x; i < (j.x + 22);i++)
		{
			for(k = j.y + 14; k > (j.y - 8);k--)
			{
				if(NF_GetTile(0,i,k) == 1) puja = false;//si xoquem amb un mur no traspassable deixem de pujar
				if(NF_GetTile(0,i-5,k) == 4) colisioMoneda(i-5,k);//si agafem una moneda
				if(NF_GetTile(0,i-5,k) == 6) colisioTransportador(i-5,k);//o acavem el nivell 
				if(final == true && NF_GetTile(0,i-5,k) == 7) colisioTransportadorFinal(i-5,k);//o el final del joc
			}
		}
		j.y -= 1;//pujem el jugador
		//augment del contador
		cont+= 1;
		//si ens movem cuan estem saltant
		moviment(fons_x,fons_y,&pX,*pY);
		if(j.vides <= 0) caureDelNivell();
		//iniciem les posicions en la que el personatje s'inicialitzi en pantalla
		pX = j.x - fons_x;
		*pY = j.y - fons_y;	
		//movem l'sprite en la pantalla
		NF_MoveSprite(1,0,pX,*pY);
		//per si es mou, tornem a cercar les noves coordenades i actualitzem
		crearCordenades(&fons_x,&fons_y);
		//actualitzem segons si es el final o no 
		if(final == true)actualitzarDarrerNivell(fons_x,fons_y);
		else actualitzar(fons_x,fons_y);
	}	
}
//procediment que fara la funcio de moure a la dreta amb els parametres corresponents i els que modifica per referencia
void moureDreta(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y)
{	
	j.moure = true;
	int i = j.y - 8;
	//mentre el jugador es pot moure i...
	//cap dels seus pixels colisiona amb un mur
	//es podra moure, cuan no...
	while(j.moure == true && i < (j.y + 15))
	{
		//no es podra moure
		if (NF_GetTile(0, (j.x + 23), i) == 1 || NF_GetTile(0, (j.x + 23), i) == 2) j.moure = false;
		//o bé si agafem una moneda
		if (NF_GetTile(0, (j.x + 23), i) == 4) colisioMoneda(j.x+23,i);
		if (NF_GetTile(0,(j.x + 23), i) == 6) colisioTransportador(j.x+23,i);// el transportador de nivell
		if (final == true && NF_GetTile(0,(j.x + 23), i) == 7) colisioTransportadorFinal(j.x+23,i);// o de finalitzar el joc
		i++;
	}
	//si es pot moure
	if(j.moure == true)
	{		
		//es mou, contant que no passi el limit del nivell
		j.x += 1;
		if (j.x > NF_CMAP[0].width -32) j.x = NF_CMAP[0].width - 32;
		//iniciem les posicions en la que el personatje s'inicialitzi en pantalla
		*personatje_x = j.x - fons_x;
		personatje_y = j.y - fons_y;		
		//movem l'sprite en la pantalla
		NF_MoveSprite(1,0,*personatje_x,personatje_y);
	}
}
//procediment que fara la funcio de moure a l'esquerra amb els parametres corresponents i els que modifica per referencia
void moureEsquerra(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y)
{
	j.moure = true;
	int i = j.y - 8;
	//mentre el jugador es pot moure i...
	//cap dels seus pixels colisiona amb un mur
	//es podra moure, cuan no...
	while(j.moure == true && i < (j.y + 15))
	{	
		//no es podra moure
               	if (NF_GetTile(0,(j.x - 1), i) == 1 || NF_GetTile(0,(j.x - 1), i) == 2) j.moure = false;
		//o bé si agafem una moneda
		if (NF_GetTile(0,(j.x - 1), i) == 4) colisioMoneda(j.x-1,i);
		if (NF_GetTile(0,(j.x - 1), i) == 6) colisioTransportador(j.x-1,i);//o un transportador
		if (final == true && NF_GetTile(0,(j.x - 1), i) == 7) colisioTransportadorFinal(j.x-1,i);
		i++;
	}
	//si es pot moure
	if(j.moure == true)
	{
		//es mou, contant que no passi el limit del nivell
		j.x -= 1;
		if (j.x < 0) j.x = 0;
		//iniciem les posicions en la que el personatje s'inicialitzi en pantalla
		*personatje_x = j.x - fons_x;
		personatje_y = j.y - fons_y;	
		//movem l'sprite en la pantalla
		NF_MoveSprite(1,0,*personatje_x,personatje_y);
	}	
}
//procediment que actualitza les monedes
void actualitzarMonedes(s16 fons_x,s16 fons_y)
{
	//agafa variables locals
	s32 i;
	s16 x[monedes], y[monedes];
	//un bucle que recorre totes les monedes
	for(i = 0;i<monedes;i++)
	{
		//si no esta agafada
		if(mon[i].agafat == false)
		{
			//i està a la pantalla
			if(abs(mon[i].x - fons_x) < 256 && abs(mon[i].y - fons_y) < 192)
			{
				//guardem les coordenades en la variable creada
				x[i] = mon[i].x - fons_x;
				y[i] = mon[i].y - fons_y;
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
			// la posem que no (molesti fora de la pantalla)
			x[i] = -64;
			y[i] = -64;
		}
		//movem l'sprite de la moneda
		NF_MoveSprite(1,i+1,x[i],y[i]);	
	}
}
//procediment actualitzar transportador
void actualitzarTransportador(s16 fons_x, s16 fons_y)
{
	//variabels locals 
	s32 x,y;	

	//si està a la pantalla
	if(abs(t.x - fons_x) < 256 && abs(t.y - fons_y) < 192)
	{
		//guardem les coordenades en la variable creada
		x = t.x - fons_x;
		y = t.y - fons_y;
	}
	//si no ho esta
	else
	{
		// la posem que no molesti (fora de la pantalla)
		x = -64;
		y = -64;
	}	
	//movem l'sprite del transportador
	NF_MoveSprite(1,monedes+1,x,y);	
}

//procediment actualitzar el transportador del darrer nivell
void actualitzarTransportadorFinal(s16 fons_x, s16 fons_y)
{
	//variabels locals 
	s32 x,y;	

	//si està a la pantalla
	if(abs(t.x - fons_x) < 256 && abs(t.y - fons_y) < 192)
	{
		//guardem les coordenades en la variable creada
		x = t.x - fons_x;
		y = t.y - fons_y;
	}
	//si no ho esta
	else
	{
		// la posem que no molesti (fora de la pantalla)
		x = -64;
		y = -64;
	}	
	//movem l'sprite del transportador
	NF_MoveSprite(1,monedes+ enem + 2,x,y);	
}

//procediments de col·lisió amb els enemics
void enemicDreta(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y)
{
	int k,l,m,n;//variables per als bucles
	//bucle que determina la col·lisió amb l'enemic
	for(k = 0;k<enem;k++)
	{
		for(m=0;m<16;m++)
		{
			for(n=0;n<22;n++)
			{
				if((j.x + n) == (enemics[k].x) && (j.y + m) == (enemics[k].y + 6))//si es col·lisiona amb el jugador
				{
					//so de matar
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);	
					mmEffect (SFX_COP);
					j.vides -= 1;//restem una vida al jugador
					for(l=0;l<50;l++)
					{
						//el movem a l'esquerra 
						moureEsquerra(fons_x,fons_y,&*personatje_x,personatje_y);
						swiWaitForVBlank();//i anem esperant el sincronisme vertical
					}
				}
			}
		}
	}
}
void enemicEsquerra(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y)
{
	int k,l,m,n;//variables per als bucles
	//bucle que determina la col·lisió amb l'enemic
	for(k = 0;k<enem;k++)
	{
		for(m=0;m<16;m++)
		{
			for(n=0;n<22;n++)
			{
				if((j.x + n) == (enemics[k].x + 12) && (j.y + m) == (enemics[k].y + 6))//si col·lisiona amb el jugador
				{
					//so de matar
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					j.vides -= 1;//restem una vida al jugador
					for(l=0;l<50;l++)
					{
						//el movem a la dreta
						moureDreta(fons_x,fons_y,&*personatje_x,personatje_y);
						swiWaitForVBlank();//i anem esperant el sincronisme vertical
					}
				}
			}	
		}
	}
}
//procediment per captar el moviment de la creueta
void moviment(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y)
{
	//si col·lisionem amb un enemic per un costat o l'altre
	enemicDreta(fons_x,fons_y,&*personatje_x,personatje_y);
	enemicEsquerra(fons_x,fons_y,&*personatje_x,personatje_y);
	//busquem si es tecleja la creueta
        scanKeys();
	//segons el boto premat es mou
        if((keysDown() & KEY_LEFT) || (keysHeld() & KEY_LEFT))
        {
		// a l'esquerra
		moureEsquerra(fons_x,fons_y,&*personatje_x, personatje_y);
        }      
        if((keysDown() & KEY_RIGHT) || (keysHeld() & KEY_RIGHT))
        {
		//a la dreta
		moureDreta(fons_x,fons_y,&*personatje_x, personatje_y);
        }
	if(keysDown() & KEY_START)menuStart();//si pitjem start anem al menu de desament
}
//procediment que cerca un enemic per matar-lo
void cercarMortEnemic(s16 fons_x,s16 fons_y,s16 personatje_x,s16 *personatje_y)
{
	int k,l,m;//variables per als bucles
	for(k=0;k<enem;k++)
	{
		for(m=0;m<16;m++)
		{
			for(l=0;l<22;l++)
			{
				if((j.y + m) == (enemics[k].y - 8) && (j.x + l) == enemics[k].x + 6)// si el jugador l'aixafa
				{
					// si ho fem el suprimim del joc	
					enemics[k].viu = false;
					//so de matar
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					mmEffect (SFX_COP);
					j.puntuacio += 1000;//el jugador guanya 1000 punts
					actualitzarPuntuacio();//s'actualitza la puntuació
					//i saltem						
					saltar(50,fons_x,fons_y,personatje_x, &*personatje_y);
				}
			}	
		}
	}
}
