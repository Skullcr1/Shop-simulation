#ifndef ilgas_h
#define ilgas_h

#define GALAS 99
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Autoriai: Jonas Brusokas, Diana Kanajeva PS1, 2015 */

typedef struct LinkedList* ManoIlgas;  

int  Str2Ilgas(ManoIlgas* Ilgas, char* S);
char* Ilgas2Str(ManoIlgas Ilgas);
void Int2Ilgas(ManoIlgas* Ilgas, int S);
int Iadd (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Suma);
int Isub (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Skirtumas) ;
int Imul (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Sandauga) ;
int Idiv (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Dalmuo);
int Imod (ManoIlgas Ilgas1, ManoIlgas Ilgas2, ManoIlgas* Liekana) ;
int Icmp (ManoIlgas Ilgas1, ManoIlgas Ilgas2); 
int Iabs (ManoIlgas Ilgas , ManoIlgas* rezultatas);
int Ipow (ManoIlgas Ilgas ,int l, ManoIlgas* rezultatas);
void freeIlgas (ManoIlgas *Ilgas);

#endif