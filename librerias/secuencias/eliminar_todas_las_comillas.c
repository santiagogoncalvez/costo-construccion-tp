#include "secuencias.h"

void eliminarTodasLasComillas(char *cad)
{
    char *pLectura = cad;
    char *pEscritura = cad;

    while (*pLectura != '\0')
    {
        if (*pLectura != '"')
        {
            *pEscritura = *pLectura;
            pEscritura++;
        }
        // Si es comilla, simplemente no la copiamos
        pLectura++;
    }

    *pEscritura = '\0'; // Terminamos la cadena correctamente
}
