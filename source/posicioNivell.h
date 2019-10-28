// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//procediment que cerca les cordenades del fons per la camera
void crearCordenades(s16 *cord_x, s16 *cord_y);

//procediment que ens inicia la posicio del jugador per mostrar-lo en pantalla
void posicioCordenades(s16 posx, s16 posy);

//procediment per iniciar les posicions del jugador
void inicialitzarPosicioJugador();

//procediment per carregar la posicio de la moneda
s32 carregarPosicioMoneda();

//ens carrega l'audio del nivell 
void carregarAudio();

//inicia el jugador al nivell 
void iniciarJugador(s16 *x, s16 *y);

//inicia la posicio del transportador
void carregarPosicioTransportador();

//procediment per actualitzar l'scroll general
void actualitzar(s16 fons_x,s16 fons_y);

//inicia la posicio del transportador final del joc
void actualitzarDarrerNivell(s16 fons_x,s16 fons_y);

//carrega la posició del transportador final
void carregarPosicioTransportadorFinal();
