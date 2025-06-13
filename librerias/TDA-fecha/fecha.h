#ifndef FECHAS_H_
#define FECHAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int d;
    int m;
    int a;
} tFecha;

bool fechaSet(tFecha* f, int d, int m, int a);
bool fechaSetDesdeString(tFecha* f, const char *cadFecha);
void fechaMostrar(const tFecha* f);
bool esFechaValida(int d, int m, int a);
int cantDiasMes(int m, int a);
bool esBisiesto(int a);
tFecha fechaSumarUnDia(const tFecha *f);
tFecha fechaSumarDias(const tFecha *f, int dias);
tFecha fechaRestarDias(const tFecha *f, int dias);
int fechaDiasEntre2Fechas(const tFecha *f1, const tFecha *f2);
int fechaDiaDeLaSemana(const tFecha *f);
int fechaComparar(const tFecha *f1, const tFecha *f2);

#endif
