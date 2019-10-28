// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>
#include <nf_text16.h>

//includes nostres
#include "estructures.h"
#include "tilejat.h"
#include "So.h"

//variables globals
extern Jugador j;
extern bool torna;
extern Enemic enemics[40];
extern s32 enem;
extern s32 monedes;
extern Moneda mon[50];

//procediment per reiniciar el tilejat
void reiniciarTilejat()
{
	// Variables locals
        u8 screen = 0;
        u8 layer = 0;
 
	//matem els enemics per que no donin problemes
	reiniciarEnemics();
	//reiniciem les monedes
	reiniciarMonedes();

        // La pantalla principal es la superior
       	lcdMainOnTop();
 
        // Reseteja el mode grafic a 0 en les dues pantalles
        NF_Set2D(0, 0);
        NF_Set2D(1, 0);
 
        // Esborra els buffers del Fons
        NF_ResetTiledBgBuffers();
 
        // Esborra els buffers dels Sprites
        NF_ResetSpriteBuffers();
 
        // Reinicialitza els fons
        NF_InitTiledBgSys(0);
        NF_InitTiledBgSys(1);
 
        // Reinicialitza els Sprites
        NF_InitSpriteSys(0, 128);
        NF_InitSpriteSys(1, 128);
 
        // Reinicia els planols de col·lisions
        NF_ResetCmapBuffers();
 
        // Reinicialitza les capes de text
        NF_InitTextSys(0);
        NF_InitTextSys(1);
 
        // Reinicia els buffers de so (libnds)
        NF_ResetRawSoundBuffers();
 
        // Elimina els possibles efectes d'Alpha Blending
        REG_BLDCNT = BLEND_NONE;
        REG_BLDCNT_SUB = BLEND_NONE;
        REG_BLDALPHA = 0x0F | (0x0F << 8);
        REG_BLDALPHA_SUB = 0x0F | (0x0F << 8);
 
        // Restaura el color del backdrop a negre en les dues pantalles
        setBackdropColor(0);
        setBackdropColorSub(0);
 
        // Reseteja la posicio de totes les capes del fons
        for (screen = 0; screen < 2; screen ++) 
	{
                for (layer = 0; layer < 4; layer ++) 
		{
                        NF_ScrollBg(screen, layer, 0, 0);
                }
        }
}

//procediment iniciarText
void iniciarText()
{
	NF_InitTiledBgBuffers();//Iniciem els bufers dels fons tilejats
	NF_InitTextSys(0);//Iniciem el sistema de text inferior	
	NF_InitTextSys(1);//Iniciem el sistema de text superior
	NF_InitTiledBgSys(0);//Inici del sistema del fons inferior
	NF_InitTiledBgSys(1);//Inici del sistema del fons superior
	NF_LoadTextFont16("fnt/font16", "normal", 256, 256, 0);//Carregem la primera font
	NF_LoadTextFont16("fnt/font16", "normal2", 256, 256, 0);//Carregem la segona font
	NF_CreateTextLayer16(1, 0, 0,"normal2");//Paso la font a la pantalla inferior
	NF_CreateTextLayer16(0, 0, 0,"normal");//Paso la font a la pantalla superior
	NF_DefineTextColor(1, 0, 1, 31, 0, 0);//definim el color del text
	NF_SetTextColor(1, 0, 1);//agafem el color del text recen definit
}
//procediment que finalitza el joc
void gameOver()
{
	//aturem la musica de fons i els sons
	aturarMusica();
	//iniciem la musica de GameOver
	mmLoad(MOD_GAMEOVER);
	mmStart(MOD_GAMEOVER, MM_PLAY_ONCE);
	//reiniciem el tilejat
	reiniciarTilejat();
	//iniciem el text
	iniciarText();
	//escribim a la pantalla inferior
	NF_WriteText16(1, 0, 1, 1, "el 'noi' ha mort :'(, prem el boto A per continuar");
	//posem el fons a la pantalla superior
	NF_LoadTiledBg("splashes/GameOver","gameOver",256,256);
	NF_CreateTiledBg(0,3,"gameOver");
	//mentre no premem el boto a això es mostrarà per pantalla
	NF_UpdateTextLayers();
	do
	{
		scanKeys();
		if(keysDown() & KEY_A)torna = false;	
	}while(torna == true);
}

//procediment per inicialitzar el tilejat del nivell 1
void iniciarTilejatN1()
{
	//inicialitzem els buffers
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitCmapBuffers();
	//Carreguem els fons
	NF_LoadTiledBg("bgs/level1", "2", 2048, 256);
	NF_LoadTiledBg("bgs/nuvols", "3", 256, 256);
	//el planol de colisions
	NF_LoadColisionMap("cmaps/level1collision", 0, 2048,256);
	//ara els Sprites
	carregarSprites();
	NF_CreateTiledBg(1, 2, "2");//carreguem el tilejat del fons
	NF_CreateTiledBg(1, 3, "3");//carreguem el tilejat del fons
}

// procediment per inicialitzar el tilejat del nivell 2
void iniciarTilejatN2()
{
	//inicialitzem els buffers
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitCmapBuffers();
	//Carreguem els fons
	NF_LoadTiledBg("bgs/nivell2", "2", 1024, 256);
	NF_LoadTiledBg("bgs/nuvols", "3", 256, 256);
	//el planol de colisions
	NF_LoadColisionMap("cmaps/platformcollisionmap2", 0, 1024,256);
	//ara els Sprites
	carregarSprites();
	NF_CreateTiledBg(1, 2, "2");//carreguem el tilejat del fons
	NF_CreateTiledBg(1, 3, "3");//carreguem el tilejat del fons
}

// procediment per inicialitzar el tilejat del nivell 3
void iniciarTilejatN3()
{
	//inicialitzem els buffers
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitCmapBuffers();
	//Carreguem els fons
	NF_LoadTiledBg("bgs/nivell3", "2", 1024, 256);
	NF_LoadTiledBg("bgs/nuvols", "3", 256, 256);
	//el planol de colisions
	NF_LoadColisionMap("cmaps/platformcollisionmap3", 0, 1024,192);
	//ara els Sprites
	carregarSprites();
	NF_CreateTiledBg(1, 2, "2");//carreguem el tilejat del fons
	NF_CreateTiledBg(1, 3, "3");//carreguem el tilejat del fons
}

// procediment per inicialitzar el tilejat del nivell 4
void iniciarTilejatN4()
{
	//inicialitzem els buffers
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	NF_InitCmapBuffers();
	//Carreguem els fons
	NF_LoadTiledBg("bgs/nivell4", "2", 2048, 256);
	NF_LoadTiledBg("bgs/nuvols", "3", 256, 256);
	//el planol de colisions
	NF_LoadColisionMap("cmaps/nivell4col", 0, 2048,256);
	//ara els Sprites
	NF_LoadSpriteGfx("sprites/pointer2",4,16,16);//Carrega els sprites a la RAM,asignant-li un id(0-255) i l'ampada i l'alçada.
	NF_LoadSpritePal("sprites/pointer2",4);// el mateix amb la paleta
	NF_VramSpriteGfx(1,4,4, true);//carreguem l'sprite a la ram
	NF_VramSpritePal(1,4,4);// el mateix amb la paleta
	carregarSprites();
	NF_CreateTiledBg(1, 2, "2");//carreguem el tilejat del fons
	NF_CreateTiledBg(1, 3, "3");//carreguem el tilejat del fons
}

//procediment per carregar sprites a la ram
void carregarSprites()
{
	NF_LoadSpriteGfx("sprites/player",0,32,32);
	//Carrega els sprites a la RAM,asignant-li un id(0-255) i l'ampada i l'alçada.
	NF_LoadSpritePal("sprites/player",0);
	//el mateix pero per la paleta. Aquest id anirà de 0 a 65.
	NF_VramSpriteGfx(1,0,0, true);//carreguem l'sprite a la ram
	NF_VramSpritePal(1,0,0);// el mateix amb la paleta
	NF_LoadSpriteGfx("sprites/enemy1",3,16,16);//Carrega els sprites a la RAM,asignant-li un id(0-255) i l'ampada i l'alçada.
	NF_LoadSpritePal("sprites/enemy1",3);// el mateix amb la paleta
	NF_VramSpriteGfx(1,3,3, true);//carreguem l'sprite a la ram
	NF_VramSpritePal(1,3,3);// el mateix amb la paleta
	NF_LoadSpriteGfx("sprites/pointer",2,16,16);//Carrega els sprites a la RAM,asignant-li un id(0-255) i l'ampada i l'alçada.
	NF_LoadSpritePal("sprites/pointer",2);// el mateix amb la paleta
	NF_VramSpriteGfx(1,2,2, true);//carreguem l'sprite a la ram
	NF_VramSpritePal(1,2,2);// el mateix amb la paleta
	NF_LoadSpriteGfx("sprites/coin",1,8,8);//Carrega els sprites a la RAM,asignant-li un id(0-255) i l'ampada i l'alçada.
	NF_LoadSpritePal("sprites/coin",1);// el mateix amb la paleta	
	NF_VramSpriteGfx(1,1,1, true);//carreguem l'sprite a la ram
	NF_VramSpritePal(1,1,1);// el mateix amb la paleta
	NF_CreateSprite(1,0,0,0, j.x, j.y);//carreguem l'sprite del jugador
}

//procediment per iniciar les monedes reben un enter com a parametre
void tilejatMonedes(s32 monedes)
{
	int i;
	for (i=0;i<monedes;i++)
	{
		NF_CreateSprite(1,i+1,1,1,-64,-64); //creem un sprite per cada moneda
	}
}

//procediment per tilejar el transportador
void tilejatTransportador(s32 monedes)
{
	NF_CreateSprite(1,monedes+1,2,2,-64,-64); //creem un sprite	
}
//procediment per tilejar el transportador
void tilejatTransportadorFinal(s32 monedes)
{
	NF_CreateSprite(1,monedes + enem + 2,4,4,-64,-64); //creem un sprite	
}
//procediment per tilejar els enemics
void tilejatEnemics(s32 monedes, s32 enem)
{
	s32 i = monedes + 2,k;
	for(k = i; k< i+enem;k++)
	{
		NF_CreateSprite(1,k,3,3,-64,-64); //creem un sprite per cada enemic
	}
}
void reiniciarEnemics()
{	
	int i;	
	for(i=0;i<enem;i++)
	{
		enemics[i].x =0;
		enemics[i].y =0;
		enemics[i].viu = NULL;
		enemics[i].xoca = NULL;
		enemics[i].cau = NULL;
	}
}

// procediment per reiniciar les monedes
void reiniciarMonedes()
{
	int i;	
	for(i=0;i<monedes;i++)
	{
		mon[i].x =0;
		mon[i].y =0;
		mon[i].agafat = false;
	}
}

//procediment per aturar la musica
void aturarMusica()
{
	mmStop();
	mmUnloadEffect(SFX_COP);
	mmUnloadEffect(SFX_COIN);
	mmUnloadEffect(SFX_JUMP);
	mmUnloadEffect(SFX_TRANSPORTADOR);
	mmUnload(MOD_ANDES);
}
