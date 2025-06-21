#include "modificar-estructura.h"
#include "../TDA-vector/vector.h"

#include "math.h"

void calcVarMensual(void* ind, void* vInd)
{
    Indice *indiceAct = (Indice *)ind;
    Vector *vIndices = (Vector *)vInd;
    Indice indiceAntMes, menorMesIndice;
    float varMensual;

    // Fecha inicio del archivo
    vectorBuscarPorPos(vInd,  &menorMesIndice, 0);

    // Para variacion mensual, el primer mes no se calcula
    if(indiceAct->periodo.m <= menorMesIndice.periodo.m && indiceAct->periodo.a <= menorMesIndice.periodo.a) return;

    // Buscar el elemento Indice correspondiente a 12 messes atrás
    indiceAntMes = *indiceAct;
    indiceAntMes.periodo = fechaRestarMeses(&indiceAntMes.periodo, 1);

    // Calcular variacion
    vectorBuscarSecuencial(vIndices, &indiceAntMes, cmpInd12MesesAntes);
    varMensual = redondear2decimales(((indiceAct->indice / indiceAntMes.indice) - 1) * 100);

    indiceAct->varMensual = varMensual;
    indiceAct->varMensualExiste = true;
}

float redondear2decimales(float valor)
{
    return roundf(valor * 100.0f) / 100.0f;
}
