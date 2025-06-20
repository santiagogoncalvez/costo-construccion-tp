#include <stdio.h>
#include <stdlib.h>

#include "../librerias/Comun/CodigosRet.h"
#include "../librerias/secuencias/secuencias.h"
#include "../librerias/TDA-fecha/fecha.h"
#include "../librerias/modificar-estructura/modificar-estructura.h"
#include "../librerias/TDA-vector/vector.h"

#define ARG_TXT 1
#define ARG_TXT_ITEMS 2
#define ARG_BIN 3
#define TAM_LINEA 501
#define TAM_REGS 156

typedef int (*TxtABin)(char *linea, void *reg);

int convTxt(const char* nomArchTxt, Indice *indices, TxtABin indiceTxtV);
int indiceTxtV(char* linea, void* reg);
int indiceItemsTxtV(char* linea, void* reg);
void mostrarIndices(Indice *indices, int ce);


// Argumentos enviados a main desde el proyecto:
// '../datos/indices-icc-general-capitulos.csv' '../datos/Indices_items_obra.csv'

// Todo esto se esta ejecutando con MEMORIA ESTÁTICA
// Hay que pasar todo a memoria dinamica utilizando el TDA-vector para poder hacer la union y hacer el proceso final.
int main(int argc, char* argv[])
{
    Indice indices[TAM_REGS];
    Indice indicesItems[TAM_REGS];

    int ret = 0;

    ret = convTxt(argv[ARG_TXT], indices, indiceTxtV);

    ret = convTxt(argv[ARG_TXT_ITEMS], indicesItems, indiceItemsTxtV);

    mostrarIndices(indices, TAM_REGS);
    printf("\n\n");
    mostrarIndices(indicesItems, TAM_REGS);


    return ret;

    return 0;
}


int convTxt(const char* nomArchTxt, Indice *indices, TxtABin indiceTxtV)
{
    FILE* archTxt = fopen(nomArchTxt, "rt");
    Indice *pIndice = indices;

    if(!archTxt)
    {
        return ERR_ARCHIVO;
    }

    char linea[TAM_LINEA];
    int ret = TODO_OK;

    fgets(linea, TAM_LINEA, archTxt);

    for(int i = 0; i < TAM_REGS; i++)
    {
        fgets(linea, TAM_LINEA, archTxt);
        indiceTxtV(linea, (pIndice + i));
    }

    fclose(archTxt);

    return ret;
}

// Funcion que se pasa como parametro para procesar los registos del primer archivo "indices-icc-general-capitulos.csv"
int indiceTxtV(char* linea, void* reg)
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

void mostrarIndices(Indice *indices, int ce)
{
    // Se muestra la estructura Indice
    for(int i = 0; i < ce; i++)
    {
        printf("\n%02d-%02d-%04d\t%-40s\t%-.2f\t%-13s\t%-.2f\t%-.2f",
               indices[i].periodo.d,
               indices[i].periodo.m,
               indices[i].periodo.a,
               indices[i].nivelGeneralAperturas,
               indices[i].indice,
               indices[i].clasificador,
               indices[i].varMensual,
               indices[i].varInteranual
              );
    }
}




