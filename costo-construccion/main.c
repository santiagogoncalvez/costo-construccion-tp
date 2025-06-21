#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "../librerias/Comun/CodigosRet.h"
#include "../librerias/secuencias/secuencias.h"
#include "../librerias/TDA-fecha/fecha.h"
#include "../librerias/modificar-estructura/modificar-estructura.h"
#include "../librerias/TDA-vector/vector.h"

#define ARG_TXT 1
#define ARG_TXT_ITEMS 2
#define ARG_BIN 3
#define TAM_LINEA 501

typedef struct
{
    tFecha periodo;
    char clasificador[20];
    char nivelGeneralAperturas[40];
    char tipoVariable[15];
    float valor;
} IndiceBin;

typedef int (*IndiceTxt)(char *linea, void *reg);
typedef bool (*EsErrorFatal)(int cod);

//Indice
int leerTxtIndices(const char* nomArchTxt, size_t tamReg, IndiceTxt convIndiceTxt, EsErrorFatal esErrorFatal, Vector *vIndices);
int convIndiceTxt(char* linea, void* reg);
int indiceItemsTxtV(char* linea, void* reg);
bool esErrorFatalIndice(int cod);
void imprimirIndice(const void* a);

//IndiceBin
void genVIndicesBin(void* ind, void* vIndBin);
void pasarIndAIndB(IndiceBin *indiceBin, Indice *indice, char *tipoVariable);
int compararIndicesBin(const void *a, const void *b);
int compararIndicesBinIgualdad(const void *a, const void *b);
void imprimirIndiceBin(const void* a);


// Argumentos enviados a main desde el proyecto:
// '../datos/indices-icc-general-capitulos.csv' '../datos/Indices_items_obra.csv'
int main(int argc, char* argv[])
{
    Vector vIndices, vIndicesBin;

    vectorCrear(&vIndices, sizeof(Indice));

    // Insertar en un mismo vector
    leerTxtIndices(argv[ARG_TXT], sizeof(Indice), convIndiceTxt, esErrorFatalIndice, &vIndices);
    leerTxtIndices(argv[ARG_TXT_ITEMS], sizeof(Indice), indiceItemsTxtV, esErrorFatalIndice, &vIndices);
    vectorRecorrer(&vIndices, calcVariaciones, &vIndices);

    printf("Vector union de los 2 archivos base\n");
    vectorMostrar(&vIndices, imprimirIndice);
    printf("\nCantidad de elementos: %d \n", vIndices.ce);

    // Creacionn del vector final que se va a grabar en el archivo binario
    vectorCrear(&vIndicesBin, sizeof(IndiceBin));
    vectorRecorrer(&vIndices, genVIndicesBin, &vIndicesBin);

    printf("\n\nVector final que se va a exportar al archivo binario\n");
    vectorMostrar(&vIndicesBin, imprimirIndiceBin);
    printf("\nCantidad de elementos: %d \n", vIndicesBin.ce);

    return 0;
}


// Indice
int leerTxtIndices(const char* nomArchTxt, size_t tamReg, IndiceTxt convIndiceTxt, EsErrorFatal esErrorFatal, Vector *vIndices)
{
    void *reg = malloc(tamReg);

    if(!reg)
    {
        return ERR_MEMORIA;
    }

    FILE* archTxt = fopen(nomArchTxt, "rt");

    if(!archTxt)
    {
        free(reg);
        return ERR_ARCHIVO;
    }

    char linea[TAM_LINEA];
    int ret = TODO_OK;

    fgets(linea, TAM_LINEA, archTxt);

    while(!esErrorFatal(ret) && fgets(linea, TAM_LINEA, archTxt))
    {
        // Procesar un registro
        ret = convIndiceTxt(linea, reg);

        // Guardar el registro de forma ordenada en el vector de indices
        vectorOrdInsertar(vIndices, reg, compararIndices, compararIndicesIgualdad);
        //vectorInsertarAlFinal(vIndices, reg);
    }

    fclose(archTxt);
    free(reg);

    return ret;
}

// Funcion que se pasa como parametro para procesar los registos del primer archivo "indices-icc-general-capitulos.csv"
int convIndiceTxt(char* linea, void* reg)
{
    Indice* indice = reg;
    char* act = strchr(linea, '\n');

    char campIndice[100];

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    eliminarTodasLasComillas(linea);

    *act = '\0';
    act = strrchr(linea, ';');
    sscanf(act + 1, "%s", campIndice);
    //Procesar campo
    convertirComa(campIndice);
    indice->indice = strtof(campIndice, NULL);

    *act = '\0';
    act = strrchr(linea, ';');
    sscanf(act + 1, "%s", indice->nivelGeneralAperturas);
    //Procesar campo
    desencriptarPorPos(indice->nivelGeneralAperturas);
    normalizar(indice->nivelGeneralAperturas);

    *act = '\0';
    sscanf(linea, "%2d/%2d/%4d", &indice->periodo.d, &indice->periodo.m, &indice->periodo.a);

    indice->varMensual = 0.0;
    indice->varInteranual = 0.0;

    //Procesar elemento. Aplicar procesos restantes a los campos.
    agregarClasificador(indice);

    return TODO_OK;
}

int indiceItemsTxtV(char* linea, void* reg)
{
    Indice* indice = reg;
    char* act = strchr(linea, '\n');
    char campIndice[100];

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    eliminarTodasLasComillas(linea);

    *act = '\0';
    act = strrchr(linea, ';');
    sscanf(act + 1, "%s", campIndice);
    //Procesar campo
    convertirComa(campIndice);
    indice->indice = strtof(campIndice, NULL);

    *act = '\0';
    act = strrchr(linea, ';');
    sscanf(act + 1, "%s", indice->nivelGeneralAperturas);
    //Procesar campo
    desencriptarPorCaso(indice->nivelGeneralAperturas);
    sacarAntYNormalizar(indice->nivelGeneralAperturas);

    *act = '\0';
    sscanf(linea, "%2d/%2d/%4d", &indice->periodo.d, &indice->periodo.m, &indice->periodo.a);

    indice->varMensual = 0.0;
    indice->varInteranual = 0.0;

    //Procesar elemento. Aplicar procesos restantes a los campos.
    agregarClasificadorItem(indice);

    return TODO_OK;
}

bool esErrorFatalIndice(int cod)
{
    switch(cod)
    {
    case ERR_LINEA_LARGA:
        return true;

    default:
        return false;
    }
}

void imprimirIndice(const void* a)
{
    const Indice* indice = (const Indice *)a;
    // Se muestra la estructura Indice

    printf("\n%02d-%02d-%04d\t%-40s\t%-.2f\t%-13s\t%-.2f\t%-.2f",
           indice->periodo.d,
           indice->periodo.m,
           indice->periodo.a,
           indice->nivelGeneralAperturas,
           indice->indice,
           indice->clasificador,
           indice->varMensual,
           indice->varInteranual
          );
}

// IndiceBin
void genVIndicesBin(void* ind, void* vIndBin)
{
    IndiceBin indiceBin;
    char tiposVariables[3][15] = {{"var_interanual\0"}, {"var_mensual\0"}, {"indice_icc\0"}};

    for(int i = 2; i >= 0; i--)
    {
        pasarIndAIndB(&indiceBin, ind, tiposVariables[i]);
        vectorOrdInsertar(vIndBin, &indiceBin, compararIndicesBin, compararIndicesBinIgualdad);
    }

}

void pasarIndAIndB(IndiceBin *indiceBin, Indice *indice, char *tipoVariable)
{
    indiceBin->periodo = indice->periodo;
    copiar(indiceBin->clasificador, indice->clasificador);
    copiar(indiceBin->nivelGeneralAperturas, indice->nivelGeneralAperturas);

    char tiposVariables[3][15] = {{"var_interanual\0"}, {"var_mensual\0"}, {"indice_icc\0"}};

    if(comparar(tipoVariable, tiposVariables[2]) == 0)
    {
        copiar(indiceBin->tipoVariable, tiposVariables[2]);
        indiceBin->valor = indice->indice;
    }

    if(comparar(tipoVariable, tiposVariables[1]) == 0)
    {
        copiar(indiceBin->tipoVariable, tiposVariables[1]);
        indiceBin->valor = indice->varMensual;
    }

    if(comparar(tipoVariable, tiposVariables[0]) == 0)
    {
        copiar(indiceBin->tipoVariable, tiposVariables[0]);
        indiceBin->valor = indice->varInteranual;
    }
}

int compararIndicesBin(const void *a, const void *b)
{
    const IndiceBin *indA = (const IndiceBin *)a;
    const IndiceBin *indB = (const IndiceBin *)b;

    int cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    if (cmpPer != 0)
        return cmpPer;  // Fecha ascendente

    int cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    if (cmpClas != 0)
        return -cmpClas;  // Clasificador descendente

    int cmpTipoVar = compararTipoVariable(indA->tipoVariable, indB->tipoVariable);
    if (cmpTipoVar != 0)
        return -cmpTipoVar;

    return 0;  // Son iguales
}

int compararIndicesBinIgualdad(const void *a, const void *b)
{
    const IndiceBin *indA = (const IndiceBin *)a;
    const IndiceBin *indB = (const IndiceBin *)b;

    int cmpPer = fechaComparar(&indA->periodo, &indB->periodo);
    int cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    int cmpNivGen = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    int cmpTipoVar = compararTipoVariable(indA->tipoVariable, indB->tipoVariable);
    int cmpValor = ((indA->valor) == (indB->valor));

    if(cmpPer == 0 && cmpNivGen == 0 && cmpValor == 0 && cmpTipoVar == 0 && cmpClas == 0) return 0;

    return 1;
}

void imprimirIndiceBin(const void* a)
{
    const IndiceBin* indiceBin = (const IndiceBin *)a;
    // Se muestra la estructura IndiceBin

    //printf("\n%30s", indiceBin->clasificador);

    printf("\n%02d-%02d-%04d\t%-15s\t%-40s\t%-15s\t%-.2f",
           indiceBin->periodo.d,
           indiceBin->periodo.m,
           indiceBin->periodo.a,
           indiceBin->clasificador,
           indiceBin->nivelGeneralAperturas,
           indiceBin->tipoVariable,
           indiceBin->valor
          );
}














