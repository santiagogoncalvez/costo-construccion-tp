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
#define ARG_SALIDA_BIN 3
#define ARG_BIN 3
#define TAM_LINEA 501

typedef struct
{
    //tFecha periodo;
    char periodo[11];
    char clasificador[20];
    char nivelGeneralAperturas[40];
    char tipoVariable[15];
    char valor[20];
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

//Archivo binario
int convVIndBinABin(const char* nomArchBin, Vector *vIndBin);
int mostrarArchivoBinario(const char* nomArchBin);


// Argumentos enviados a main desde el proyecto:
// Archivo base indices general-capitulos, Archivo base indices items, Ruta del archivo binario de salida
// '../datos/indices-icc-general-capitulos.csv' '../datos/Indices_items_obra.csv' '../salida/indices-procesados.bin'
int main(int argc, char* argv[])
{
    Vector vIndices, vIndicesBin;

    vectorCrear(&vIndices, sizeof(Indice));

    printf("\nProcesando archivos base...");
    // Insertar en un mismo vector
    leerTxtIndices(argv[ARG_TXT], sizeof(Indice), convIndiceTxt, esErrorFatalIndice, &vIndices);
    leerTxtIndices(argv[ARG_TXT_ITEMS], sizeof(Indice), indiceItemsTxtV, esErrorFatalIndice, &vIndices);

    // Calcular variaciones.
    vectorRecorrer(&vIndices, calcVariaciones, &vIndices);

    printf("\n\nVector union de los 2 archivos base:\n");
    vectorMostrar(&vIndices, imprimirIndice);
    printf("\nCantidad de elementos: %d \n", vIndices.ce);

    // Creacionn del vector final que se va a grabar en el archivo binario
    vectorCrear(&vIndicesBin, sizeof(IndiceBin));
    vectorRecorrer(&vIndices, genVIndicesBin, &vIndicesBin);

    printf("\n\nVector final que se va a exportar a un archivo binario:\n");
    vectorMostrar(&vIndicesBin, imprimirIndiceBin);
    printf("\nCantidad de elementos: %d \n", vIndicesBin.ce);

    //DESTRUIR VECTORES AL FINAL PARA LIBERAR MEMORIA

    // Exportar datos a un archivo binario
    convVIndBinABin(argv[ARG_SALIDA_BIN], &vIndicesBin);
    mostrarArchivoBinario(argv[ARG_SALIDA_BIN]);

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

    indice->varMensualExiste = false;
    indice->varInteranualExiste = false;

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

    indice->varMensualExiste = false;
    indice->varInteranualExiste = false;

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

    printf("\n%02d-%02d-%04d",
           indice->periodo.d,
           indice->periodo.m,
           indice->periodo.a
          );
    printf("\t%-40s", indice->nivelGeneralAperturas);
    printf("\t%-.2f", indice->indice);
    printf("\t%-13s", indice->clasificador);

    if(indice->varMensualExiste) printf("\t%-.2f", indice->varMensual);
    else printf("\tNA");

    if(indice->varInteranualExiste) printf("\t%-.2f", indice->varInteranual);
    else printf("\tNA");
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
    fechaAString(&indice->periodo, indiceBin->periodo);
    copiar(indiceBin->clasificador, indice->clasificador);
    copiar(indiceBin->nivelGeneralAperturas, indice->nivelGeneralAperturas);

    char tiposVariables[3][15] = {{"var_interanual\0"}, {"var_mensual\0"}, {"indice_icc\0"}};

    if(comparar(tipoVariable, tiposVariables[2]) == 0)
    {
        copiar(indiceBin->tipoVariable, tiposVariables[2]);
        sprintf(indiceBin->valor, "%.2f", indice->indice);
    }

    if(comparar(tipoVariable, tiposVariables[1]) == 0)
    {
        copiar(indiceBin->tipoVariable, tiposVariables[1]);
        if(indice->varMensualExiste)
        {
            sprintf(indiceBin->valor, "%.2f", indice->varMensual);
        }
        else
        {
            copiar(indiceBin->valor, "NA");
        }
    }

    if(comparar(tipoVariable, tiposVariables[0]) == 0)
    {
        copiar(indiceBin->tipoVariable, tiposVariables[0]);
        if(indice->varInteranualExiste)
        {
            sprintf(indiceBin->valor, "%.2f", indice->varInteranual);
        }
        else
        {
            copiar(indiceBin->valor, "NA");
        }
    }
}

int compararIndicesBin(const void *a, const void *b)
{
    const IndiceBin *indA = (const IndiceBin *)a;
    const IndiceBin *indB = (const IndiceBin *)b;
    int cmpTipoVar, cmpPer, cmpClas;
    tFecha periodoA, periodoB;

    fechaSetDesdeString(&periodoA, indA->periodo);
    fechaSetDesdeString(&periodoB, indB->periodo);

    /*
    Se siguio este orden para poder cumplir con la imagen de muestra de salida del punto final, ya que en el punto 10 se menciona un orden y se muestra de esa manera, pero en el punto final no. Se pide un orden periodo-clasificador-tipoVariable pero en la imagen de muestra se aplica un orden tipoVariable-periodo-clasificador. Si el orden hubiera tenido que ser estrictamente periodo-clasificador-tipoVariable solo se tiene que desplazar la comparacon 'cmpTipoVar' como tercera comparacion.
    */
    cmpTipoVar = compararTipoVariable(indA->tipoVariable, indB->tipoVariable);
    if (cmpTipoVar != 0)
        return -cmpTipoVar;

    cmpPer = fechaComparar(&periodoA, &periodoB);
    if (cmpPer != 0)
        return cmpPer;  // Fecha ascendente

    cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    if (cmpClas != 0)
        return -cmpClas;  // Clasificador descendente


    return 0;  // Son iguales
}

int compararIndicesBinIgualdad(const void *a, const void *b)
{
    const IndiceBin *indA = (const IndiceBin *)a;
    const IndiceBin *indB = (const IndiceBin *)b;
    int cmpPer, cmpClas, cmpNivGen, cmpTipoVar, cmpValor;
    tFecha periodoA, periodoB;

    fechaSetDesdeString(&periodoA, indA->periodo);
    fechaSetDesdeString(&periodoB, indB->periodo);

    cmpPer = fechaComparar(&periodoA, &periodoB);
    cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    cmpNivGen = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    cmpTipoVar = compararTipoVariable(indA->tipoVariable, indB->tipoVariable);
    cmpValor = ((indA->valor) == (indB->valor));

    if(cmpPer == 0 && cmpNivGen == 0 && cmpValor == 0 && cmpTipoVar == 0 && cmpClas == 0) return 0;

    return 1;
}

void imprimirIndiceBin(const void* a)
{
    const IndiceBin* indiceBin = (const IndiceBin *)a;

    // Se muestra la estructura IndiceBin
    printf("\n%10s", indiceBin->periodo);
    printf("\t%-13s", indiceBin->clasificador);
    printf("\t%-40s", indiceBin->nivelGeneralAperturas);
    printf("\t%-15s", indiceBin->tipoVariable);
    printf("\t%-10s", indiceBin->valor);
}


//Archivo binario
int convVIndBinABin(const char* nomArchBin, Vector *vIndBin)
{
    printf("\n\nCreando archivo binario...");

    FILE* arch = fopen(nomArchBin, "wb");
    if (!arch)
    {
        return ERR_ARCHIVO;
    }

    fwrite(vIndBin->vec, vIndBin->tamElem, vIndBin->ce, arch);
    fclose(arch);

    printf("\n\nArchivo binario '%s' creado de forma exitosa.\n", nomArchBin);

    return TODO_OK;
}

int mostrarArchivoBinario(const char* nomArchBin)
{
    FILE* arch = fopen(nomArchBin, "rb");
    if (!arch)
    {
        perror("Error al abrir archivo binario");
        return ERR_ARCHIVO;
    }

    Vector vIndBin;
    if (!vectorCrear(&vIndBin, sizeof(IndiceBin)))
    {
        fclose(arch);
        return ERR_ARCHIVO;
    }

    IndiceBin aux;
    while (fread(&aux, sizeof(IndiceBin), 1, arch) == 1)
    {
        if (vectorInsertarAlFinal(&vIndBin, &aux)!=TODO_OK)
        {
            vectorDestruir(&vIndBin);
            fclose(arch);
            return ERR_ARCHIVO;
        }
    }

    printf("\n\nLectura del archivo binario creado '%s':\n", nomArchBin);
    vectorMostrar(&vIndBin, imprimirIndiceBin);

    vectorDestruir(&vIndBin);

    fclose(arch);

    return TODO_OK;
}







