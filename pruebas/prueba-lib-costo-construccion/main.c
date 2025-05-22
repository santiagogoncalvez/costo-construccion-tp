#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../lib-costo-construccion/costo-construccion.h"

typedef struct
{
    const char *input;
    const char *expected;
} Fecha;

void testFormatearFecha();

int main()
{
	system("chcp 65001");


    testFormatearFecha();

    return 0;
}

void testFormatearFecha()
{
   Fecha casos[] =
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
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("🧪 Ejecutando tests para formatearFecha...\n");

    for (int i = 0; i < total; i++)
    {
        convertirFecha(salida, casos[i].input);
        if (strcmp(salida, casos[i].expected) != 0)
        {
            printf("❌ Test %d falló: entrada='%s' → salida='%s' (esperado='%s')\n",
                   i + 1, casos[i].input, salida, casos[i].expected);
            errores++;
        }
        else
        {
            printf("✅ Test %d pasó: %s → %s\n", i + 1, casos[i].input, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un test falló en formatear_fecha.");
}
