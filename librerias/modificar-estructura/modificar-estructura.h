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
    double indice;
    char clasificador[20];
    float varMensual;
    bool varMensualExiste;
    float varInteranual;
    bool varInteranualExiste;
} Indice;


void agregarClasificador(Indice *indice);
void agregarClasificadorItem(Indice *indice);
int compararIndices(const void *a, const void *b);
int compararIndicesIgualdad(const void *a, const void *b);
void calcVarMensual(void* ind, void* vInd);
void calcVarInteranual(void* ind, void* vInd);
void calcVariaciones(void* ind, void* vInd);
int cmpInd12MesesAntes(const void* a, const void* b);
int compararIndicesVar(const void *a, const void *b);
float redondear2decimales(double valor);

#endif // MODIFICAR_ESTRUCTURA_H_INCLUDED
