// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//procediment per moure el jugador amb els parametres per referencia que seran totes les variables del jugador
void moureJugador(s16 fons_x,s16 fons_y);

//procediment que fara la funcio de saltar amb els parametres corresponents i els que modifica per referencia
void saltar(int pujada,s16 fons_x, s16 fons_y,s16 pX,s16 *pY);

//procediment que fara la funcio de moure a la dreta amb els parametres corresponents i els que modifica per referencia
void moureDreta(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y);

//procediment que fara la funcio de moure a l'esquerra amb els parametres corresponents i els que modifica per referencia
void moureEsquerra(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y);

//procediment que actualitza les monedes
void actualitzarMonedes(s16 fons_x,s16 fons_y);

//procediment que actualitza el transportador
void actualitzarTransportador(s16 fons_x, s16 fons_y);

//procediment que actualitza el transportador final
void actualitzarTransportadorFinal(s16 fons_x, s16 fons_y);

//procediments que col·lisionen amb els enemics
void enemicDreta(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y);

void enemicEsquerra(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y);

//procediment que cerca un enemic per matar-lo
void cercarMortEnemic(s16 fons_x,s16 fons_y,s16 personatje_x,s16 *personatje_y);

//procediment per captar el moviment de la creueta
void moviment(s16 fons_x,s16 fons_y,s16 *personatje_x,s16 personatje_y);
