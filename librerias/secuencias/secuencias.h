#ifndef SECUENCIAS_H_INCLUDED
#define SECUENCIAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void convertirFecha(char *cadDestino, const char *cadOrigen);
char *normalizar(char *cadorigen);
bool espalabra(char cadcopia);
char abcdario(char cad,int posicion);
char siesletra15(char cad,int pos);
void convertirComa(char *cad);

#endif // SECUENCIAS_H_INCLUDED
