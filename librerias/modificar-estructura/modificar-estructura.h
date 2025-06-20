#ifndef MODIFICAR_ESTRUCTURA_H_INCLUDED
#define MODIFICAR_ESTRUCTURA_H_INCLUDED

#include "../secuencias/secuencias.h"
#include "../TDA-fecha/fecha.h"

#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "math.h"

typedef struct
{
    tFecha periodo;
    char nivelGeneralAperturas[40];
    float indice;
    char clasificador[20];
    float varMensual;
    float varInteranual;
} Indice;


void agregarClasificadores(Indice indices[], int ce);
void agregarClasificador(Indice *indice);
void agregarClasificadorItems(Indice indices[], int ce);
void agregarClasificadorItem(Indice *indice);
void ordenarPorPerYClas(Indice indices[], int ce);
void agregarVarMensual(Indice indices[], int ce);
void calcIndVarInteranual(Indice indices[], int ce);
float buscarIndAnterior(Indice *indices, Indice *actIndice, int ce);
float redondear2decimales(float valor);

#endif // MODIFICAR_ESTRUCTURA_H_INCLUDED
