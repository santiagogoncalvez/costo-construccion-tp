#include "estructura_indice.h"
#include "../TDA_vector/vector.h"

#include "math.h"

void agregarClasificador(Indice *indice)
{
    char text[]="Nivel general";
    char text2[]="Capitulos";

    if(comparar(indice->nivelGeneralAperturas, text) == 0)
    {
        copiar(indice->clasificador, text);
    }
    else
    {
        copiar(indice->clasificador, text2);
    }
}

void agregarClasificadorItem(Indice *indice)
{
    copiar(indice->clasificador, "Items");
}

//Se tiene en cuenta que el vector ya esta ordenado por periodo ascendente
void calcVarInteranual(void* ind, void* vInd)
{
    Indice *indiceAct = (Indice *)ind;
    Vector *vIndices = (Vector *)vInd;
    Indice indiceAntAnio, menorAnioIndice;
    float varInteranual;
    int pos;

    // Fecha inicio del archivo
    vectorBuscarPorPos(vInd,  &menorAnioIndice, 0);

    // Para variacion anual, el primer anio no se calcula
    if(indiceAct->periodo.a <= menorAnioIndice.periodo.a) return;

    // Buscar el elemento Indice correspondiente a 12 meses atr�s
    indiceAntAnio = *indiceAct;
    indiceAntAnio.periodo = fechaRestarMeses(&indiceAntAnio.periodo, 12);

    // Calcular variacion
    pos = vectorBuscarSecuencial(vIndices, &indiceAntAnio, cmpInd12MesesAntes);
    if(pos < 0)
    {
        printf("\n\nNO SE ENCONTRO ELEMENTO\n\n");
        indiceAct->varInteranual = 0.0;
        indiceAct->varInteranual = false;
        return;
    }


    varInteranual = redondear2decimales(calcVariacion(indiceAct->indice, indiceAntAnio.indice));

    indiceAct->varInteranual = varInteranual;
    indiceAct->varInteranualExiste = true;
}

int cmpInd12MesesAntes(const void* a, const void* b)
{
    const Indice* indA = (const Indice*)a;
    const Indice* indB = (const Indice*)b;

    return !(fechaComparar(&indA->periodo, &indB->periodo) == 0
             && compararClasificador(indA->clasificador, indB->clasificador) == 0
             && comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas) == 0
            );
}

int compararIndicesVar(const void *a, const void *b)
{
    const Indice *indA = (const Indice *)a;
    const Indice *indB = (const Indice *)b;
    int cmpPer, cmpClas, cmpNivel;

    cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    if (cmpPer != 0)
        return cmpPer;  // Fecha ascendente

    cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    if (cmpClas != 0)
        return -cmpClas;  // Clasificador descendente

    cmpNivel = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    if (cmpNivel != 0)
        return cmpNivel;

    return 0;  // Son iguales
}

void calcVarMensual(void* ind, void* vInd)
{
    Indice *indiceAct = (Indice *)ind;
    Vector *vIndices = (Vector *)vInd;
    Indice indiceAntMes, menorMesIndice;
    float varMensual;
    int pos;

    // Fecha inicio del archivo
    vectorBuscarPorPos(vInd,  &menorMesIndice, 0);

    // Para variacion mensual, el primer mes no se calcula
    if(indiceAct->periodo.m <= menorMesIndice.periodo.m && indiceAct->periodo.a <= menorMesIndice.periodo.a) return;

    // Buscar el elemento Indice correspondiente a 12 messes atr�s
    indiceAntMes = *indiceAct;
    indiceAntMes.periodo = fechaRestarMeses(&indiceAntMes.periodo, 1);

    // Calcular variacion
    pos = vectorBuscarSecuencial(vIndices, &indiceAntMes, cmpInd12MesesAntes);
    if(pos < 0)
    {
        printf("\n\nNO SE ENCONTRO ELEMENTO\n\n");
        indiceAct->varMensual = 0.0;
        indiceAct->varMensualExiste = false;
        return;
    }


    varMensual = redondear2decimales(calcVariacion(indiceAct->indice, indiceAntMes.indice));

    indiceAct->varMensual = varMensual;
    indiceAct->varMensualExiste = true;
}

double calcVariacion(double numAct, double numAnt)
{
    return ((numAct / numAnt) - 1) * 100;
}

float redondear2decimales(double valor)
{
    return (float)(round(valor * 100.0) / 100.0);
}

void calcVariaciones(void* ind, void* vInd)
{
    calcVarMensual(ind, vInd);
    calcVarInteranual(ind, vInd);
}

int compararIndices(const void *a, const void *b)
{
    const Indice *indA = (const Indice *)a;
    const Indice *indB = (const Indice *)b;

    int cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    if (cmpPer != 0)
        return cmpPer;  // Fecha ascendente

    int cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    if (cmpClas != 0)
        return -cmpClas;  // Clasificador descendente

    /*
    int cmpNivel = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    if (cmpNivel != 0)
        return cmpNivel;
    */
    return 0;  // Son iguales
}

int compararIndicesIgualdad(const void *a, const void *b)
{
    const Indice *indA = (const Indice *)a;
    const Indice *indB = (const Indice *)b;
    int cmpPer, cmpNivGen, cmpIndice, cmpClas;

    cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    cmpNivGen = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    cmpIndice = ((indA->indice) == (indB->indice));
    cmpClas = compararClasificador(indA->clasificador, indB->clasificador);

    if(cmpPer == 0 && cmpNivGen == 0 && cmpIndice == 0 && cmpClas == 0) return 0;

    return 1;
}

void imprimirIndice(const void* a)
{
    const Indice* indice = (const Indice *)a;
    // Se muestra la estructura Indice

    printf("\n%02d-%02d-%4d",
           indice->periodo.d,
           indice->periodo.m,
           indice->periodo.a
          );
    printf("\t%-38s", indice->nivelGeneralAperturas);
    printf("\t%-.4f", indice->indice);
    printf("\t%-13s", indice->clasificador);

    if(indice->varMensualExiste) printf("\t%-.2f", indice->varMensual);
    else printf("\tNA");

    if(indice->varInteranualExiste) printf("\t%-.2f", indice->varInteranual);
    else printf("\tNA");
}
