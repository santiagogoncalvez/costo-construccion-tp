#include "costo-construccion.h"

void convertirFecha(char *cadDestino, const char *cadOrigen) {
    const char *pCadOrigen = cadOrigen;
    char *pCadDestino = cadDestino;

    int cantBarras = 0;
    for(int i = 3; i > 1; i--) {
        while(*pCadOrigen && cantBarras <  i - 1) {
            if(*pCadOrigen == '/') {
                cantBarras++;
            }
            pCadOrigen++;
        }

        while(*pCadOrigen && *pCadOrigen != '/') {
            *pCadDestino = *pCadOrigen;
            pCadOrigen++;
            pCadDestino++;
        }
        *pCadDestino = '/';
        pCadDestino++;

        pCadOrigen = cadOrigen;
        cantBarras = 0;
    }

    while(*pCadOrigen && *pCadOrigen != '/') {
        *pCadDestino = *pCadOrigen;
        pCadOrigen++;
        pCadDestino++;
    }

    *pCadDestino = '\0';
}
