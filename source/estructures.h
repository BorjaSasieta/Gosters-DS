// Includes c/c++
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

// Includes propietaris NDS
#include <nds.h>
#include <maxmod9.h>
#include <nf_lib.h>

//estructura del jugador
typedef struct
{
	s16 x; //Posició X
	s16 y; //Posició Y
	bool salt; //Si està saltant
	bool moure; //Si es mou
	s32 puntuacio; //seran les "monedes" que recull i els enemics que mata
	u8 vides; //son les vides del jugador
} Jugador;

//estructura de les monedes
typedef struct
{
	s16 x; //Posició X
	s16 y; //Posició Y
	bool agafat;//si s'agafa la moneda
} Moneda;

//estructura del transportador
typedef struct
{
	s16 x; //posició X
	s16 y; //posició Y
}Transportador;

//estructura dels enemics
typedef struct
{
	s16 x; //posició X
	s16 y; //posició Y
	bool cau; //si està gravitant
	bool viu; //es a dir si no l'has matat
	bool xoca; //si ha xocat amb una paret
} Enemic;

