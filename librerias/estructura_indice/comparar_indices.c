#include "estructura_indice.h"
#include "../TDA_fecha/fecha.h"

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

    int cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    int cmpNivGen = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    int cmpIndice = ((indA->indice) == (indB->indice));
    int cmpClas = compararClasificador(indA->clasificador, indB->clasificador);

    if(cmpPer == 0 && cmpNivGen == 0 && cmpIndice == 0 && cmpClas == 0) return 0;

    return 1;
}
