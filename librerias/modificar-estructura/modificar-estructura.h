#ifndef MODIFICAR_ESTRUCTURA_H_INCLUDED
#define MODIFICAR_ESTRUCTURA_H_INCLUDED

#include "../secuencias/secuencias.h"

#include "stdbool.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
    char periodo[11];
    char nivelGeneralAperturas[30];
    float indice;
    char clasificador[20];
} Indice;


void agregarClasificador(Indice indices[], int ce);

#endif // MODIFICAR_ESTRUCTURA_H_INCLUDED
