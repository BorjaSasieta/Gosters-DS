// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//funció per retornar el numero d'enemics mentre es carregen les seves posicions
s32 carregarPosicioEnemics();
//procediment que actualitza els enemics
void actualitzarEnemics(s32 x_fons, s32 y_fons);
//procediment per moure enemics
void moureEnemic(s32 i);
//procediment per gravitar l'enemic
void gravitarEnemic(s32 i);
//procediment per moure el frame
void moureFrameEnemic(s32 i);
//procediment que canvia el frame
void canviarFrame();
