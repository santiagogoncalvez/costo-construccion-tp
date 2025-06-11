#ifndef SECUENCIAS_H_INCLUDED
#define SECUENCIAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void convertirFecha(char *cadOrigen);
void convertirComa(char *cad);
void normalizar(char *cad);
bool espalabra(char cadcopia);
char abcdario(char cad,int posicion);
char siesletra15(char cad,int pos);
void desencriptarPorPos(char* cad);
void desencriptarPorCaso(char *cad);
void sacarAntYNormalizar(char *cad);
char toUpperProp(char c);
char toLowerProp(char c);
bool comparar(char* cad1,char* cad2);
void copiar(char* cadDestinio,char* cadOrigen);
void generarClasificador(char *clasificador);

#endif // SECUENCIAS_H_INCLUDED
