#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../librerias/estructura_indice/estructura_indice.h"
#include "../../librerias/TDA_fecha/fecha.h"
#include "../../librerias/TDA_vector/vector.h"
#include "../../librerias/secuencias/secuencias.h"

#include <math.h>

#define EPSILON 0.3f

typedef struct
{
    char periodo[11];
    char nivelGeneralAperturas[50];
    char indice[20];
    char variacionMensual[10];
} CasoVarMensual;

void pruebaAgregarClasificador();
void pruebaAgregarClasificadorItems();
bool verificarOrden(const Indice datos[], int ce);
bool verificarOrden(const Indice datos[], int ce);
void pruebaOrdenarPorPerYClas();
void ordenarIndices(Indice *indices, int ce);
void mostrarVIndices(const Indice* vector, int ce);
void pruebaCalcIndVarInteranual();
void pruebaAgregarVarMensual();

int main()
{
    system("chcp 65001");

    pruebaAgregarClasificador();
    pruebaAgregarClasificadorItems();
    pruebaOrdenarPorPerYClas();

    // Separar de la funcion calcVarMensual() la parte que hace el c�lculo para poder probarla con esta funci�n y que se aplique ya sabiendo cual es el anterior y el posterior
    /*pruebaAgregarVarMensual();*/

    // Separar de la funcion calcVarInteranual() la parte que hace el c�lculo para poder probarla con esta funci�n y que se aplique ya sabiendo cual es el anterior y el posterior
    /*pruebaCalcIndVarInteranual();*/


    return 0;
}

void pruebaAgregarClasificador()
{
    Indice indices[] =
    {
        {{11, 4, 2023}, "Nivel general", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2025}, "Vidrio", 0.0, "Materiales", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "Metal", 0.0, "Mano de obra", 0.0, false, 0.0, false},
        {{1, 7, 2020}, "Carpinteria", 0.0, "Gastos generales", 0.0, false, 0.0, false},
    };

    Indice esperados[] =
    {
        {{11, 4, 2023}, "Nivel general", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2025}, "Vidrio", 0.0, "Capitulos", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "Metal", 0.0, "Capitulos", 0.0, false, 0.0, false},
        {{1, 7, 2020}, "Carpinteria", 0.0, "Capitulos", 0.0, false, 0.0, false},
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
        agregarClasificador(p);
    }

    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificador...\n");


    for (int i = 0; i < total; i++)
    {
        if (comparar(indices[i].clasificador, esperados[i].clasificador) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, "", indices[i].clasificador, esperados[i].clasificador);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, "", esperados[i].clasificador);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificador.");
}

void pruebaAgregarClasificadorItems()
{
    Indice indices[] =
    {
        {{11, 4, 2023}, "", 0.0, "", 0.0, false, 0.0, false},
        {{6, 10, 2025}, "", 0.0, "", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "", 0.0, "", 0.0, false, 0.0, false},
        {{1, 7, 2020}, "", 0.0, "", 0.0, false, 0.0, false},
        {{10, 4, 2023}, "", 0.0, "", 0.0, false, 0.0, false}
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
        agregarClasificadorItem(p);
    }

    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificadorItems...\n");
    for (int i = 0; i < total; i++)
    {
        if (comparar(indices[i].clasificador, "Items") != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, "", indices[i].clasificador, "Items");
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, "", indices[i].clasificador);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificadorItems.");
}

void probarFecha()
{
    tFecha fecha1, fecha2;

    fechaSetDesdeString(&fecha1, "2022-08-01");
    fechaSetDesdeString(&fecha2, "2020-08-01");

    fechaMostrar(&fecha1);
    fechaMostrar(&fecha2);

    printf("\nComparacion: %d", fechaComparar(&fecha1, &fecha2));
}

void probarFechaSumarMeses(void)
{
    printf("\n\nSumar meses\n");

    tFecha fechasPrueba[] =
    {
        {31, 1, 2023},   // Enero 31 → ver qué pasa en febrero
        {28, 2, 2023},   // Febrero no bisiesto
        {28, 2, 2024},   // Febrero bisiesto
        {30, 11, 2022},  // Noviembre → suma 3 meses
        {15, 6, 2021}    // Junio → resta meses
    };
    int cantidades[] = {1, 1, 1, 3, 7};

    int n = sizeof(fechasPrueba) / sizeof(fechasPrueba[0]);

    for (int i = 0; i < n; i++)
    {
        tFecha nueva = fechaSumarMeses(&fechasPrueba[i], cantidades[i]);
        printf("Original: %02d/%02d/%04d + %d meses → Resultado: %02d/%02d/%04d\n",
               fechasPrueba[i].d, fechasPrueba[i].m, fechasPrueba[i].a,
               cantidades[i],
               nueva.d, nueva.m, nueva.a);
    }
}

void probarFechaRestarMeses(void)
{
    printf("\n\nRestar meses\n");
    tFecha fechasPrueba[] =
    {
        {31, 1, 2023},   // Enero 31 → ver qué pasa en febrero
        {28, 2, 2023},   // Febrero no bisiesto
        {28, 2, 2024},   // Febrero bisiesto
        {30, 11, 2022},  // Noviembre → suma 3 meses
        {15, 6, 2021}    // Junio → resta meses
    };
    int cantidades[] = {1, 1, 1, 3, 7};

    int n = sizeof(fechasPrueba) / sizeof(fechasPrueba[0]);

    for (int i = 0; i < n; i++)
    {
        tFecha nueva = fechaRestarMeses(&fechasPrueba[i], cantidades[i]);
        printf("Original: %02d/%02d/%04d -  %d meses → Resultado: %02d/%02d/%04d\n",
               fechasPrueba[i].d, fechasPrueba[i].m, fechasPrueba[i].a,
               cantidades[i],
               nueva.d, nueva.m, nueva.a);
    }
}

bool verificarOrden(const Indice datos[], int ce)
{
    printf("\nVerificando orden...");

    for (int i = 0; i < ce - 1; i++)
    {
        int cmpFecha = fechaComparar(&datos[i].periodo, &datos[i + 1].periodo);

        // Periodo desordenado (orden ascendente)
        if (cmpFecha > 0)
            return false;

        if (cmpFecha == 0)
        {
            int cmpClas = compararClasificador(datos[i].clasificador, datos[i + 1].clasificador);

            // Mismo periodo, pero clasificador desordenado (orden descendente)
            if (cmpClas < 0)
                return false;
        }
    }

    return true;
}

void pruebaOrdenarPorPerYClas()
{
    printf("\nEjecutando pruebas para ordenarPorPerYClas...");

    Indice indicesBase[] =
    {
        {{11, 4, 2023}, "", 0.0, "Items", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Capitulos", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Items", 0.0, false, 0.0, false},
        {{10, 4, 2023}, "", 0.0, "Items", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Items", 0.0, false, 0.0, false},
    };

    int total = sizeof(indicesBase) / sizeof(indicesBase[0]);

    printf("\n\nAntes de ordenar");
    mostrarVIndices(indicesBase, total);

    ordenarIndices(indicesBase, total);

    printf("\n\nDespues de ordenar");
    mostrarVIndices(indicesBase, total);

    if (verificarOrden(indicesBase, total))
    {
        printf("\nOrden correcto\n");
    }
    else
    {
        printf("\nOrden incorrecto\n");
    }
}

void ordenarIndices(Indice *indices, int ce)
{
    int i, j;
    Indice *minPtr;
    Indice *currPtr;
    Indice temp;

    for (i = 0; i < ce - 1; i++)
    {
        minPtr = indices + i;

        for (j = i + 1; j < ce; j++)
        {
            currPtr = indices + j;

            if (compararIndices(currPtr, minPtr) < 0)
            {
                minPtr = currPtr;
            }
        }

        if (minPtr != indices + i)
        {
            temp = *(indices + i);
            *(indices + i) = *minPtr;
            *minPtr = temp;
        }
    }
}

void mostrarVIndices(const Indice* vector, int ce)
{
    const Indice* ptr;
    const Indice* fin;

    fin = vector + ce;

    for (ptr = vector; ptr < fin; ptr++)
    {
        imprimirIndice(ptr);
    }
}


void doubleToStr(double val, char *str, int size)
{
    snprintf(str, size, "%.2f", val);
}

void pruebaIndPorInteranual()
{
    Indice indices[] =
    {
        {{1, 4, 2022}, "", 100.0, "Nivel general", 0.0, false, 0.0, false},  // Base
        {{1, 4, 2023}, "", 115.5, "Nivel general", 0.0, false, 0.0, false},  // +15.5%
        {{1, 4, 2022}, "", 200.0, "Items", 0.0, false, 0.0, false},          // Base
        {{1, 4, 2023}, "", 260.0, "Items", 0.0, false, 0.0, false},          // +30.0%
        {{1, 4, 2023}, "", 300.0, "Capitulos", 0.0, false, 0.0, false}       // Sin valor base → no se puede calcular
    };

    Indice esperados[] =
    {
        {{1, 4, 2022}, "", 100.0, "Nivel general", 0.0, false, 0.0, false},     // Base, sin variación
        {{1, 4, 2023}, "", 115.5, "Nivel general", 0.0, 15.50},   // +15.5%
        {{1, 4, 2022}, "", 200.0, "Items", 0.0, false, 0.0, false},             // Base, sin variación
        {{1, 4, 2023}, "", 260.0, "Items", 0.0, 30.00},           // +30%
        {{1, 4, 2023}, "", 300.0, "Capitulos", 0.0, false, 0.0, false}
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
        calcVarInteranual(p, indices);
    }

    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificador...\n");


    for (int i = 0; i < total; i++)
    {
        if (indices[i].varInteranual != esperados[i].varInteranual)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%f' (esperado='%f')\n",
                   i + 1, "", indices[i].varInteranual, esperados[i].varInteranual);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %f\n", i + 1, "", esperados[i].varInteranual);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificador.");
}

void pruebaCalcIndVarInteranual()
{
    Indice indicesBase[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Cap�tulos", 0.0f, false, 0.0f, false}
    };

    Indice indicesEsperados[] =
    {
        // A�o 2022
        {{1,  1, 2022}, "Nivel general", 100.00f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Cap�tulos", 0.0f, false, 0.0f, false},

        // A�o 2023 (con valores de variaci�n interanual esperados)
        {{1,  1, 2023}, "Nivel general", 199.24f, "Cap�tulos", 0.0f, 99.4f},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Cap�tulos", 0.0f, 103.6f},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Cap�tulos", 0.0f, 103.1f},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Cap�tulos", 0.0f, 114.6f},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Cap�tulos", 0.0f, 116.9f},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Cap�tulos", 0.0f, 115.3f},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Cap�tulos", 0.0f, 118.3f},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Cap�tulos", 0.0f, 133.1f},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Cap�tulos", 0.0f, 148.8f},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Cap�tulos", 0.0f, 148.4f},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Cap�tulos", 0.0f, 159.6f},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Cap�tulos", 0.0f, 225.2f}
    };

    int total = sizeof(indicesBase) / sizeof(indicesBase[0]);

    // Ejecuta la funci�n a probar
    Indice* p;
    Indice* fin = indicesBase + total;

    for (p = indicesBase; p < fin; p++)
    {
        calcVarInteranual(p, indicesBase);
    }

    printf("\nEjecutando pruebas para pruebaCalcIndVarInteranual...\n");
    int errores = 0;

    for (int i = 0; i < total; i++)
    {
        float dif = fabs(indicesBase[i].varInteranual - indicesEsperados[i].varInteranual);
        if (dif > EPSILON)
        {
            printf("Error en indice %d (%d-%02d): esperado %.2f, obtenido %.2f\n",
                   i,
                   indicesBase[i].periodo.a, indicesBase[i].periodo.m,
                   indicesEsperados[i].varInteranual, indicesBase[i].varInteranual);
            errores++;
        }
        else
        {
            printf("Indice %d (%d-%02d) OK: %.2f\n", i, indicesBase[i].periodo.a, indicesBase[i].periodo.m, indicesBase[i].varInteranual);
        }
    }

    if (errores == 0)
    {
        printf("�Todos los tests pasaron correctamente!\n");
    }
    else
    {
        printf("Cantidad de errores: %d\n", errores);
    }
}

void pruebaAgregarVarMensual()
{
    Indice indicesBase[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Cap�tulos", 0.0f, false, 0.0f, false}
    };

    Indice indicesEsperados[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Cap�tulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Cap�tulos", 3.8f, true, 0.0f, false},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Cap�tulos", 5.0f, true, 0.0f, false},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Cap�tulos", 2.3f, true, 0.0f, false},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Cap�tulos", 6.6f, true, 0.0f, false},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Cap�tulos", 6.6f, true, 0.0f, false},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Cap�tulos", 6.9f, true, 0.0f, false},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Cap�tulos", 7.5f, true, 0.0f, false},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Cap�tulos", 7.4f, true, 0.0f, false},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Cap�tulos", 7.3f, true, 0.0f, false},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Cap�tulos", 6.7f, true, 0.0f, false},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Cap�tulos", 4.3f, true, 0.0f, false},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Cap�tulos", 6.7f, true, 0.0f, false},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Cap�tulos", 6.0f, true, 0.0f, false},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Cap�tulos", 4.7f, true, 0.0f, false},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Cap�tulos", 8.1f, true, 0.0f, false},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Cap�tulos", 7.8f, true, 0.0f, false},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Cap�tulos", 5.8f, true, 0.0f, false},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Cap�tulos", 8.4f, true, 0.0f, false},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Cap�tulos", 14.8f, true, 0.0f, false},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Cap�tulos", 14.7f, true, 0.0f, false},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Cap�tulos", 7.1f, true, 0.0f, false},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Cap�tulos", 11.5f, true, 0.0f, false},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Cap�tulos", 30.6f, true, 0.0f, false}
    };

    int total = sizeof(indicesBase) / sizeof(indicesBase[0]);

    // Llamamos a la funci�n que llena varMensual
    Indice* p;
    Indice* fin = indicesBase + total;

    for (p = indicesBase; p < fin; p++)
    {
        calcVarMensual(p, indicesBase);
    }

    printf("\nEjecutando pruebas para pruebaAgregarVarMensual...\n");
    int errores = 0;

    for (int i = 0; i < total; i++)
    {
        float dif = fabs(indicesBase[i].varMensual - indicesEsperados[i].varMensual);
        if (dif > EPSILON)
        {
            printf("Error en indice %d (%d-%02d): esperado %.2f, obtenido %.2f\n",
                   i,
                   indicesBase[i].periodo.a, indicesBase[i].periodo.m,
                   indicesEsperados[i].varMensual, indicesBase[i].varMensual);
            errores++;
        }
        else
        {
            printf("Indice %d (%d-%02d) OK: %.2f\n", i,
                   indicesBase[i].periodo.a, indicesBase[i].periodo.m,
                   indicesBase[i].varMensual);
        }
    }

    if (errores == 0)
    {
        printf("Todos los tests para varMensual pasaron correctamente!\n");
    }
    else
    {
        printf("Cantidad de errores: %d\n", errores);
    }
}
