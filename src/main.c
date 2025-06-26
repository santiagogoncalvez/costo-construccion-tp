#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include "../librerias/Comun/codigos_ret.h"
#include "../librerias/secuencias/secuencias.h"
#include "../librerias/TDA_fecha/fecha.h"
#include "../librerias/estructura_indice/estructura_indice.h"
#include "../librerias/TDA_vector/vector.h"

#define ARG_TXT 1
#define ARG_TXT_ITEMS 2
#define ARG_SALIDA_BIN 3
#define ARG_BIN 3
#define ARG_REF_MEN 4
#define ARG_REF_INT 5
#define TAM_LINEA 501
#define MARGEN_VAR 0.9

typedef struct
{
    char periodo[11];
    char clasificador[20];
    char nivelGeneralAperturas[40];
    char tipoVariable[15];
    char valor[20];
} IndiceBin;

typedef struct
{
    Vector *indicesBin;
    Vector *indicesVariaciones;
    int elemNoEncontrados;
    int cantCoincidencias;
    int cantDiferencias;
} PruebaIndiceBin;

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

//Pruebas de archivo binario
int leerTxtIndicesBin(const char* nomArchTxt, size_t tamReg, IndiceTxt convIndiceTxt, EsErrorFatal esErrorFatal, Vector *vIndices);
void pruebaVariaciones(const char* nomArchBin, const char* nomArchVarMens, const char* nomArchVarInt);
int convIndiceVarMensTxt(char* linea, void* reg);
int convIndiceVarIntTxt(char* linea, void* reg);
void verificarResultadosBin (void* ind, void* dato);
int compararIndicesBinIgualdadVar(const void *a, const void *b);
void agregarClasificadorBin(IndiceBin *indice);
int compararIndicesValor(const void *a, const void *b);


/*
Argumentos enviados a main desde el proyecto:
Archivo base indices general-capitulos, Archivo base indices items, Ruta del archivo binario de salida, Archivo referencia variaciones mensuales, Archivo referencia variaciones interanuales

'../datos/entrada/indices-icc-general-capitulos.csv' '../datos/entrada/Indices_items_obra.csv'
'../salida/indices-procesados.bin' '../datos/referencia/ICC-Capitulos-Items-var-mensual.csv' '../datos/referencia/ICC-Capitulos-Items-var-interanual.csv'
*/

int main(int argc, char* argv[])
{
    Vector vIndices, vIndicesBin;
    int ret;

    vectorCrear(&vIndices, sizeof(Indice));


    // Insertar en un mismo vector
    /* Insertar elementos del primer archivo*/
    printf("\nProcesando archivos base...");
    ret = leerTxtIndices(argv[ARG_TXT], sizeof(Indice), convIndiceTxt, esErrorFatalIndice, &vIndices);
    if (ret != TODO_OK)
    {
        vectorDestruir(&vIndices);
        return ret;
    }

    /*Insertar elementos del segundo archivo*/
    ret = leerTxtIndices(argv[ARG_TXT_ITEMS], sizeof(Indice), indiceItemsTxtV, esErrorFatalIndice, &vIndices);
    if (ret != TODO_OK)
    {
        vectorDestruir(&vIndices);
        return ret;
    }


    // Calcular variaciones.
    vectorRecorrer(&vIndices, calcVariaciones, &vIndices);

    printf("\nArchivos procesados.");
    printf("\nCantidad de elementos: %d \n", vIndices.ce);


    // Creacionn del vector final que se va a grabar en el archivo binario
    printf("\nCreacion y procesamiento del vector final que se va a exportar a un archivo binario...\n");
    vectorCrear(&vIndicesBin, sizeof(IndiceBin));
    vectorRecorrer(&vIndices, genVIndicesBin, &vIndicesBin);

    printf("\n\nVector creado y procesado.");
    printf("\nCantidad de elementos: %d \n", vIndicesBin.ce);


    // Exportar datos a un archivo binario
    convVIndBinABin(argv[ARG_SALIDA_BIN], &vIndicesBin);
    mostrarArchivoBinario(argv[ARG_SALIDA_BIN]);


    // Prueba de los datos del archivo binario
    pruebaVariaciones(argv[ARG_SALIDA_BIN], argv[ARG_REF_MEN], argv[ARG_REF_INT]);


    //DESTRUIR VECTORES AL FINAL PARA LIBERAR MEMORIA
    vectorDestruir(&vIndices);
    vectorDestruir(&vIndicesBin);

    return ret;
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
        printf("\n\nError al abrir archivo de texto.");
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
    }

    fclose(archTxt);
    free(reg);

    return ret;
}

// Funcion que se pasa como parametro para procesar los registos del primer archivo "indices-icc-general-capitulos.csv"
int convIndiceTxt(char* linea, void* reg)
{
    Indice* indice = reg;
    char* act = strchrProp(linea, '\n');

    char campIndice[100];

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    eliminarTodasLasComillas(linea);

    *act = '\0';
    act = strrchrProp(linea, ';');
    sscanf(act + 1, "%s", campIndice);
    //Procesar campo
    convertirComa(campIndice);
    indice->indice = atof(campIndice);

    *act = '\0';
    act = strrchrProp(linea, ';');
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
    char* act = strchrProp(linea, '\n');
    char campIndice[100];

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    eliminarTodasLasComillas(linea);

    *act = '\0';
    act = strrchrProp(linea, ';');
    sscanf(act + 1, "%s", campIndice);
    //Procesar campo
    convertirComa(campIndice);
    indice->indice = atof(campIndice);

    *act = '\0';
    act = strrchrProp(linea, ';');
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
        sprintf(indiceBin->valor, "%f", indice->indice);
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
    printf("\t%10s\t", indiceBin->valor);
}


//Archivo binario
int convVIndBinABin(const char* nomArchBin, Vector *vIndBin)
{
    printf("\n\nCreando archivo binario...");

    FILE* arch = fopen(nomArchBin, "wb");
    if (!arch)
    {
        printf("\n\nError al crear archivo binario.");
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
        perror("\n\nError al abrir archivo binario");
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




// Prueba de archivo binario final

int leerTxtIndicesBin(const char* nomArchTxt, size_t tamReg, IndiceTxt convIndiceTxt, EsErrorFatal esErrorFatal, Vector *vIndices)
{
    void *reg = malloc(tamReg);

    if(!reg)
    {
        return ERR_MEMORIA;
    }

    FILE* archTxt = fopen(nomArchTxt, "rt");

    if(!archTxt)
    {
        printf("\n\nError al abrir archivo de texto.");
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
        vectorOrdInsertar(vIndices, reg, compararIndicesBin, compararIndicesBinIgualdad);
    }

    fclose(archTxt);
    free(reg);

    return ret;
}

/*Los archivos de referencia no tienen tildes, estan separados por ";", los numeros ya tienen el "." como separcion de decimales, las fechas se transformaron a formato "aaaa-mm-01" */
void pruebaVariaciones(const char* nomArchBin, const char* nomArchVarMens, const char* nomArchVarInt)
{
    printf("\n\n\nPRUEBAS");
    printf("\nPrueba de los resultados de las variaciones mensuales y anuales del archivo binario final.");
    printf("\nMargen de error: %.1f", MARGEN_VAR);
    printf("\n\nEjecutando prueba...");

    Vector indicesBin;
    Vector indicesVariaciones;
    PruebaIndiceBin pruebaIndiceBin = {&indicesBin, &indicesVariaciones, 0, 0, 0};


    // Leer el binario y grabar los datos en un vector
    vectorCrearDeArchivo(&indicesBin, sizeof(IndiceBin), nomArchBin);

    vectorCrear(&indicesVariaciones, sizeof(IndiceBin));

    // Leer el txt referencia de variaciones mensuales y guardarlo en un vector
    leerTxtIndicesBin(nomArchVarMens, sizeof(IndiceBin), convIndiceVarMensTxt, esErrorFatalIndice, &indicesVariaciones);

    // Leer el txt referencia de variaciones interanuales y guardarlo en un vector
    leerTxtIndicesBin(nomArchVarInt, sizeof(IndiceBin), convIndiceVarIntTxt, esErrorFatalIndice, &indicesVariaciones);

    // Recorrer el vector indicesVarMens y comparar los resultados con los elementos del vector indicesBin
    vectorRecorrer(&indicesVariaciones, verificarResultadosBin, &pruebaIndiceBin);

    printf("\n\n\nCantidad de elementos no encontrados: %d", pruebaIndiceBin.elemNoEncontrados);
    printf("\nCantidad de coincidencias: %d", pruebaIndiceBin.cantCoincidencias);
    printf("\nCantidad de diferencias: %d\n", pruebaIndiceBin.cantDiferencias);

    if(pruebaIndiceBin.elemNoEncontrados == 0)
    {
        printf("\n\nTodos los elementos de los archivos del Indec existen en el archivo binario.");
        if(pruebaIndiceBin.cantDiferencias == 0)
        {
            printf("\nTodos los valores fueron calculados correctamente.\nPrueba exitosa.\n");
        }
        else
        {
            printf("\nHubo valores que no se calcularon correctamente.\nPrueba fallida.\n");
        }
    }
    else
    {
        printf("\nHay elementos de los archivos del Indec que no existen en el archivo binario.\nPrueba fallida.\n");
    }



    // Destruir vectores
    vectorDestruir(&indicesBin);
    vectorDestruir(&indicesVariaciones);
}

int convIndiceVarMensTxt(char* linea, void* reg)
{
    IndiceBin* indice = reg;
    char* act;

    eliminarTodasLasComillas(linea);
    modificarCadenaTxtIndec(linea);

    act = strchrProp(linea, '\n');

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    eliminarTodasLasComillas(linea);
    modificarCadenaTxtIndec(linea);

    *act = '\0';
    act = strrchrProp(linea, ';');
    copiar(indice->valor, act + 1);

    *act = '\0';
    act = strrchrProp(linea, ';');
    copiar(indice->nivelGeneralAperturas, act + 1);

    *act = '\0';
    act = strrchrProp(linea, ';');
    copiar(indice->clasificador, act + 1);

    //Procesar campo
    *act = '\0';
    copiar(indice->periodo, linea);

    copiar(indice->tipoVariable, "var_mensual");

    //Procesar item
    agregarClasificadorBin(indice);

    return TODO_OK;
}

int convIndiceVarIntTxt(char* linea, void* reg)
{
    IndiceBin* indice = reg;
    char* act;

    eliminarTodasLasComillas(linea);
    modificarCadenaTxtIndec(linea);

    act = strchrProp(linea, '\n');

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act = strrchrProp(linea, ';');
    copiar(indice->valor, act + 1);

    *act = '\0';
    act = strrchrProp(linea, ';');
    copiar(indice->nivelGeneralAperturas, act + 1);

    *act = '\0';
    act = strrchrProp(linea, ';');
    copiar(indice->clasificador, act + 1);

    //Procesar campo
    *act = '\0';
    copiar(indice->periodo, linea);

    copiar(indice->tipoVariable, "var_interanual");

    //Procesar item
    /*No todos los elementos de los archivos de referencia tienen el mismo formato que los elementos del archivo binario*/
    agregarClasificadorBin(indice);

    return TODO_OK;
}

// Los vectores estan ordenados
void verificarResultadosBin (void* ind, void* dato)
{
    IndiceBin *indiceAct = (IndiceBin *)ind;
    PruebaIndiceBin *pruebaIndiceBin = (PruebaIndiceBin *)dato;
    IndiceBin indiceAntMes, menorMesIndice;
    tFecha periodoAct, periodoMenorMes, periodoAnt;
    int pos;

    // Fecha inicio del archivo
    vectorBuscarPorPos(pruebaIndiceBin->indicesVariaciones,  &menorMesIndice, 0);

    // Para variacion mensual, el primer mes no se calcula
    fechaSetDesdeString(&periodoAct, indiceAct->periodo);
    fechaSetDesdeString(&periodoMenorMes, menorMesIndice.periodo);
    /*Saltear en comparaciones primer mes y primer anio*/

    if(comparar(indiceAct->tipoVariable, "var_mensual") == 0)
    {
        if(periodoAct.m <= periodoMenorMes.m && periodoAct.a <= periodoMenorMes.a) return;
    }

    if(comparar(indiceAct->tipoVariable, "var_interanual") == 0)

    {
        if(periodoAct.a <= periodoMenorMes.a) return;
    }


    // Buscar el elemento Indice correspondiente a 1 mes atrï¿½s
    indiceAntMes = *indiceAct;
    periodoAnt = periodoAct;
    // Modificación de dato que creo en esta función
    fechaRestarMeses(&periodoAnt, 1);
    fechaAString(&periodoAct, indiceAntMes.periodo);


    // Comparar variaciones
    pos = vectorBuscarSecuencial(pruebaIndiceBin->indicesBin, &indiceAntMes, compararIndicesBinIgualdadVar);
    if(pos < 0)
    {
        printf("\n\nNO SE ENCUENTRA ELEMENTO EN EL BINARIO");
        printf("\nElemento no encontrado");
        imprimirIndiceBin(indiceAct);

        pruebaIndiceBin->elemNoEncontrados++;
    }
    else
    {
        if(compararIndicesValor(indiceAct, &indiceAntMes) != 0)
        {
            printf("\n\n\nVariacion calculada INCORRECTAMENTE");
            imprimirIndiceBin(indiceAct);
            printf("\nElemento variacion calculado");
            imprimirIndiceBin(&indiceAntMes);
            pruebaIndiceBin->cantDiferencias++;
        }
        else
        {
            /*En el caso de que no se quiera mostrar todas las coincidencias se puede omitir esta salida por consola*/
            printf("\n\nVariacion calculada correctamente");
            printf("\nEsperado:");
            imprimirIndiceBin(indiceAct);
            printf("\nObtenido:");
            imprimirIndiceBin(&indiceAntMes);

            pruebaIndiceBin->cantCoincidencias++;
        }
    }
}

int compararIndicesBinIgualdadVar(const void *a, const void *b)
{
    const IndiceBin *indA = (const IndiceBin *)a;
    const IndiceBin *indB = (const IndiceBin *)b;
    int cmpPer, cmpClas, cmpNivGen, cmpTipoVar; //cmpValor
    tFecha periodoA, periodoB;

    fechaSetDesdeString(&periodoA, indA->periodo);
    fechaSetDesdeString(&periodoB, indB->periodo);

    cmpPer = fechaComparar(&periodoA, &periodoB);
    cmpClas = compararClasificador(indA->clasificador, indB->clasificador);
    cmpNivGen = comparar(indA->nivelGeneralAperturas, indB->nivelGeneralAperturas);
    cmpTipoVar = compararTipoVariable(indA->tipoVariable, indB->tipoVariable);

    if(cmpPer == 0 && cmpNivGen == 0 && cmpTipoVar == 0 && cmpClas == 0) return 0;

    return 1;
}

int compararIndicesValor(const void *a, const void *b)
{
    const IndiceBin *indA = (const IndiceBin *)a;
    const IndiceBin *indB = (const IndiceBin *)b;
    int cmpValor;
    float valorA, valorB;


    // Convertir los valores string a float y comparar con margen de error
    valorA = atof(indA->valor);
    valorB = atof(indB->valor);

    // Se evalua con margen de error ya que los indices base del trabajo con respecto a los oficiales son levemente distintos
    cmpValor = (fabs(valorA - valorB) <= MARGEN_VAR) ? 0 : 1;

    if(cmpValor == 0) return 0;

    return 1;
}

void agregarClasificadorBin(IndiceBin *indice)
{
    char text[]="Nivel general";

    if(comparar(indice->nivelGeneralAperturas, text) == 0)
    {
        copiar(indice->clasificador, text);
    }
}













