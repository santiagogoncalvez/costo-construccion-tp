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
    float variacion_mensual;
} Indice;


void agregarClasificador(Indice indices[], int ce);
void agregarClasificadorItems(Indice indices[], int ce);
void ordenarPorPerYClas(Indice indices[], int ce);
void calcularVarMensual(Indice indices[], int ce);

#endif // MODIFICAR_ESTRUCTURA_H_INCLUDED
