// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>


//funció colisioMoneda que servira per eliminar del planol la moneda agafada
void colisioMoneda(s32 x, s32 y);
//procediment per cuan el jugador caigui del nivell
void caureDelNivell();
//funció per acabar el nivell (cuan es col·lisiona amb el transportador)
void colisioTransportador(s32 x, s32 y);
//funció per acabar el joc (cuan es col·lisiona amb el transportador Final)
void colisioTransportadorFinal(s32 x, s32 y);

