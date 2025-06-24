#include "estructura_indice.h"

void calcVariaciones(void* ind, void* vInd)
{
    calcVarMensual(ind, vInd);
    calcVarInteranual(ind, vInd);
}
