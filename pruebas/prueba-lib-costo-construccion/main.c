#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../lib-costo-construccion/costo-construccion.h"

typedef struct
{
    const char *entrada;
    const char *esperado;
} CasoPrueba;

void pruebaFormatearFecha();
void pruebaNormalizar();

int main()
{
    system("chcp 65001");


    pruebaFormatearFecha();
    pruebaNormalizar();

    return 0;
}

void pruebaFormatearFecha()
{
    CasoPrueba fechas[] =
    {
        {"1/4/2004",    "2004/4/1"},
        {"01/04/2004",  "2004/04/01"},
        {"1/04/3004",   "3004/04/1"},
        {"10/12/1999",  "1999/12/10"},
        {"9/9/2022",    "2022/9/9"},
        {"31/12/2023",  "2023/12/31"},
        {"7/11/1980",   "1980/11/7"},
        {"3/3/2000",   "2000/3/3"}
    };

    char salida[11]; // AAAA/MM/DD + '\0'
    int total = sizeof(fechas) / sizeof(fechas[0]);
    int errores = 0;

    printf("\nEjecutando pruebas para formatearFecha...\n");

    for (int i = 0; i < total; i++)
    {
        convertirFecha(salida, fechas[i].entrada);
        if (strcmp(salida, fechas[i].esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, fechas[i].entrada, salida, fechas[i].esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, fechas[i].entrada, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en formatear_fecha.");
}

void pruebaNormalizar()
{
    CasoPrueba casos[] =
    {
        {"materiales_para_la_construCcion", "Materiales para la construccion"},
        {"mano_de_obra",                    "Mano de obra"},
        {"gastos_generales",                "Gastos generales"},
        {"EQUIPAMIENTO",                    "Equipamiento"},
        {"servicios_varios",               "Servicios varios"},
        {"costos_DIRECTOS",                "Costos directos"},
        {"costo_total",                    "Costo total"},
        {"INSTALACIONES_electricas",       "Instalaciones electricas"},
        {"obras_de_albanileria",           "Obras de albanileria"},
        {"acabados_exteriores",            "Acabados exteriores"},
        {"estructURA_de_hormigon",         "Estructura de hormigon"},
        {"infrAesTruCtura_basica",         "Infraestructura basica"},
        {"componentes_Industrializados",   "Componentes industrializados"},
    };

    char salida[60];
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\n\nEjecutando pruebas para normalizar...\n");

    for (int i = 0; i < total; i++)
    {
        strcpy(salida, casos[i].entrada);
        normalizar(salida);
        if (strcmp(salida, casos[i].esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, casos[i].entrada, salida, casos[i].esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, casos[i].entrada, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en normalizar.");
}
