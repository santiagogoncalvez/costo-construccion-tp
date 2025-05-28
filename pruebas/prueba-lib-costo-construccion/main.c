#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../lib-costo-construccion/costo-construccion.h"

typedef struct
{
    const char *input;
    const char *expected;
} CasoPrueba;

void testFormatearFecha();
void testNormalizar();

int main()
{
    system("chcp 65001");


    testFormatearFecha();
    testNormalizar();

    return 0;
}

void testFormatearFecha()
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

    printf("\nEjecutando tests para formatearFecha...\n");

    for (int i = 0; i < total; i++)
    {
        convertirFecha(salida, fechas[i].input);
        if (strcmp(salida, fechas[i].expected) != 0)
        {
            printf("Test %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, fechas[i].input, salida, fechas[i].expected);
            errores++;
        }
        else
        {
            printf("Test %d paso: %s --> %s\n", i + 1, fechas[i].input, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un test fallo en formatear_fecha.");
}

void testNormalizar()
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

    char salida[60]; // AAAA/MM/DD + '\0'
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\n\nEjecutando tests para normalizar...\n");

    for (int i = 0; i < total; i++)
    {
        strcpy(salida, casos[i].input);
        normalizar(salida);
        if (strcmp(salida, casos[i].expected) != 0)
        {
            printf("Test %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, casos[i].input, salida, casos[i].expected);
            errores++;
        }
        else
        {
            printf("Test %d paso: %s --> %s\n", i + 1, casos[i].input, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un test fallo en normalizar.");
}
