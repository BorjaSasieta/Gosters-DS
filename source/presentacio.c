// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

// Includes de llibreries nostres
#include "So.h"
#include "presentacio.h"

//procediment per iniciar l'splash
void splash()
{
	setBrightness(3, 0);	// Restaura l'enlluernament
	NF_LoadTiledBg("splashes/nfl", "nf", 256, 256);		// Carrega el fons per la capa 3, pantalla superior
	NF_CreateTiledBg(0, 3, "nf");
	NF_LoadTiledBg("splashes/devkitpro", "dev", 256, 256);		// Carrega el fons per la capa 3, pantalla inferior
	NF_CreateTiledBg(1, 3, "dev");
	reiniciarSplash();//crida al procediment de reiniciar l'splash
	NF_ResetTiledBgBuffers();//es neteja el tilejat de l'splash
	NF_DeleteTiledBg(0,3);
	NF_DeleteTiledBg(1,3);
	NF_LoadTiledBg("splashes/logo-cepnet", "cep", 256, 256);		// Carrega el fons per la capa 3, pantalla superior
	NF_CreateTiledBg(1, 3, "cep");
	NF_LoadTiledBg("splashes/Sasieta", "sasi", 256, 256);		// Carrega el fons per la capa 3, pantalla inferior
	NF_CreateTiledBg(0, 3, "sasi");
	reiniciarSplash();// es torna a cridar el procediment de reiniciar l'splash
	NF_ResetTiledBgBuffers();// i es torna a eliminar el tilejat
	NF_DeleteTiledBg(0,3);
	NF_DeleteTiledBg(1,3);
	setBrightness(3, 0);	// Restaura l'enlluernament
}
//procediment que inicia el so
void soInicial()
{
	// Inicialitza l'engine d'audio de la DS
	soundEnable();
	// Inicialitza els buffers de so
	NF_InitRawSoundBuffers();
	// Carega els samples de so en format RAW
	NF_LoadRawSound("sfx/music", 1, 22050, 0);
	// Inicia la musica de fons
	NF_PlayRawSound(1, 127, 64, false, 0);
}
//procediment per reinciar l'splash
void reiniciarSplash()
{
	s8 caux = 0, iluminacio = -16; // iniciem valors
	while(!(iluminacio==0))
	{//cuan iluminacio no siga 0:
		caux++;
		if(caux==11)
		{
			caux= 0;
			iluminacio++;
		}
		setBrightness(3, iluminacio);//Cambia l'enlluernament
		swiWaitForVBlank();//esperem a que s'estableixi l'enlluernat
	}
	while(!(iluminacio==-16))
	{
		caux++;
		if(caux==11)
		{
			caux = 0;
			iluminacio--;
		}
		setBrightness(3, iluminacio);//Cambia l'enlluernament
		swiWaitForVBlank();//Espera el sincronisme vertical
	}
}
//funcio que s'encarrega d'iniciar la consola
void iniciar()
{
	consoleDemoInit();		// Inicialitza la consola
	consoleClear();			// Esborra la pantalla
	NF_SetRootFolder("NITROFS");//Escollim nitrofiles com a carpeta inicial
	NF_Set2D(1, 0);//Inici del sistema 2D inferior
	NF_Set2D(0, 0);//Inici del sistema 2D superior
	NF_InitTiledBgBuffers();//Iniciem els bufers dels fons tilejats
	NF_InitTiledBgSys(1);//Inici del sistema del fons inferior
	NF_InitTiledBgSys(0);//Inici del sistema del fons superior
	NF_InitSpriteBuffers();//Iniciem els buffers dels sprites
	NF_InitSpriteSys(0);//Iniciem el sistema d'sprites inferior
	NF_InitSpriteSys(1);//Iniciem el sistema d'sprites superior
	NF_ResetSpriteBuffers();//Resetejem els Sprites
	NF_ResetTiledBgBuffers();//Resetejem els fons
}
//procediment que inicia la visualització del joc
void inici()
{ 
	//NF_UnloadRawSound(1); // esborrem la musica inicial de la memoria
	//carreguem l'audio definit
	mmInitDefault("audio/So.bin");
	mmLoad(MOD_LEYENDADELBESO);
	mmStart(MOD_LEYENDADELBESO,MM_PLAY_LOOP);
	NF_InitTiledBgBuffers();//Iniciem els bufers dels fons tilejats
	NF_InitTextSys(1);//Iniciem el sistema de text inferior
	NF_InitTiledBgSys(0);//Inici del sistema del fons superior
	NF_InitTiledBgSys(1);//Inici del sistema del fons superior
	NF_LoadTiledBg("splashes/Gosters", "gosters", 256, 256);		// Carrega el fons per la capa 3, pantalla superior
	NF_CreateTiledBg(0, 3, "gosters");
	NF_LoadTextFont16("fnt/font16", "normal", 256, 256, 0);//Carregem la font
	NF_CreateTextLayer16(1, 0, 0,"normal");//Paso la font a la pantalla inferior
	NF_DefineTextColor(1, 0, 1, 31, 0, 0);//definim el color de la pantalla inferior
	NF_WriteText16(1, 0, 1, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                       Polseu la pantalla tactil per   iniciar el joc\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                                        Centre d'estudis politecnics    curs 2012-13"); //escribim el text
	NF_SetTextColor(1, 0, 1); // canviem el color del text
	NF_UpdateTextLayers();//actualitzem les capes de text
}
