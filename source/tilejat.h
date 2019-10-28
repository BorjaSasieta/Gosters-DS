// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//procediment per inicialitzar el tilejat del nivell 1
void iniciarTilejatN1();
//procediment per inicialitzar el tilejat del nivell 2
void iniciarTilejatN2();
// procediment per inicialitzar el tilejat del nivell 3
void iniciarTilejatN3();
// procediment per inicialitzar el tilejat del nivell 4
void iniciarTilejatN4();
//procediment per iniciar les monedes reben un enter com a parametre
void tilejatMonedes(s32 monedes);
//procediment iniciarText
void iniciarText();
//procediment per acabar el joc
void gameOver();
//procediment per iniciar el tilejat
void reiniciarTilejat();
// procediment per reiniciar les monedes
void reiniciarMonedes();
//procediment per iniciar el tilejat del transportador
void tilejatTransportador(s32 monedes);
//procediment per iniciar el tilejat del transportador final
void tilejatTransportadorFinal(s32 monedes);
//procediment per tilejar els enemics
void tilejatEnemics(s32 monedes, s32 enem);
//procediment per crear els sprites a la ram
void carregarSprites();
//procediment per reiniciar els enemics
void reiniciarEnemics();
//procediment per a parar la musica
void aturarMusica();
