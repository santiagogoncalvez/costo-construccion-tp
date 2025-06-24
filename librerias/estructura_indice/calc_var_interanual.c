#include "estructura_indice.h"
#include "../TDA_vector/vector.h"

#include "math.h"

//Se tiene en cuenta que el vector ya esta ordenado por periodo ascendente
void calcVarInteranual(void* ind, void* vInd)
{
    Indice *indiceAct = (Indice *)ind;
    Vector *vIndices = (Vector *)vInd;
    Indice indiceAntAnio, menorAnioIndice;
    float varInteranual;

    // Fecha inicio del archivo
    vectorBuscarPorPos(vInd,  &menorAnioIndice, 0);

    // Para variacion anual, el primer anio no se calcula
    if(indiceAct->periodo.a <= menorAnioIndice.periodo.a) return;

    // Buscar el elemento Indice correspondiente a 12 meses atr�s
    indiceAntAnio = *indiceAct;
    indiceAntAnio.periodo = fechaRestarMeses(&indiceAntAnio.periodo, 12);

    // Calcular variacion
    vectorBuscarSecuencial(vIndices, &indiceAntAnio, cmpInd12MesesAntes);
    varInteranual = redondear2decimales(((indiceAct->indice / indiceAntAnio.indice) - 1) * 100);

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

    int cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    if (cmpPer != 0)
        return cmpPer;  // Fecha ascendente

    int cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    if (cmpClas != 0)
        return -cmpClas;  // Clasificador descendente

    int cmpNivel = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    if (cmpNivel != 0)
        return cmpNivel;

    return 0;  // Son iguales
}
