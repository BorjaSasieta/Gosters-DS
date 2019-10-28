// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//includes nostres
#include "So.h"
#include "camera.h"
#include "nivell2.h"
#include "estructures.h"
#include "tilejat.h"
#include "enemics.h"
#include "puntuacio.h"
#include "posicioNivell.h"

//variables globals

extern s32 enem;
extern s32 monedes;
extern Jugador j;
extern Moneda mon[50];
extern Enemic enemics[40];
extern Transportador t;
extern bool torna;
extern bool segueix;

//procediment que s'encarregua de gestionar el segon nivell
void nivell2()
{	
	//iniciem els boleans per al joc.
	torna = true;
	segueix = false;
	//presentem
	presentacio2();
	//carreguem l'audio
	carregarAudio();
	//iniciem el tilejat per a que es vegi en pantalla tot 
	iniciarTilejatN2();
	//decalrem variables necesaries per moure la camara i el jugador
	s16 fons_x, fons_y;
	//inicialitzem les posicions del jugador i de la camara amb el seguent procediment
	iniciarJugador(&fons_x,&fons_y);
	preparaPuntuacio();
	//carreguem posicions
	monedes = carregarPosicioMoneda();
	enem = carregarPosicioEnemics();
	carregarPosicioTransportador();
	//refresquem els tilejats
	tilejatMonedes(monedes);
	tilejatEnemics(monedes,enem);
	tilejatTransportador(monedes);
	//per si es mou, tornem a cercar les noves coordenades
	crearCordenades(&fons_x,&fons_y);
	//sempre entrarem aquí	
	while(torna == true)
	{
		//aquesta funció ens moura el jugador sempre i cuan premem el boto corresponent
		moureJugador(fons_x,fons_y);
		//per si es mou, tornem a cercar les noves coordenades
		crearCordenades(&fons_x,&fons_y);
		//actualitzem altres objectes
		actualitzar(fons_x,fons_y);
	}
}

// es la pantalla de presentació del nivell 2
void presentacio2()
{	
	bool bo = true;
	iniciarText();//iniciem el text amb la funció creada per mi.
	NF_WriteText16(0, 0, 1, 1, "El nostre amic ha comencat unes aventures fascinants i ara... el que li espera ");// i escribim el text
	NF_WriteText16(1, 0, 1, 1, "Prem el boto A per continuar");//ara a la pantalla inferior
	//actulitzem els layers de text	
	NF_UpdateTextLayers();
	//mentre el bolea sigui true es repetira
	while(bo == true)
	{
		//cuan pitjem la A trenquem el bucle
		scanKeys();
		if(keysDown() & KEY_A)
		{
			// si es pitja A es canvia el bolea a false que trencara el bucle
			bo = false;
		}
	}
	//netejem
	NF_ResetTiledBgBuffers();
	NF_DeleteTiledBg(1,0);
	NF_DeleteTiledBg(0,0);
}
