#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#include "../Comun/CodigosRet.h"


#define TAM 10

#define CAP_INI 8 // Cant elementos
#define FACTOR_INCR 1.5 // Incr 50%
#define FACTOR_DECR 0.5 // Decr 50%
#define FACTOR_OCUP 0.25 // Ocup 25%

#define AUMENTAR 1
#define DISMINUIR 2

#define BURBUJEO 1
#define SELECCION 2
#define INSERCION 3
#define QSORT 4 


typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}
Vector;


typedef int (*Cmp)(const void* a, const void* b);
typedef void (*Imprimir)(const void* a);
typedef void (*Accion)(void* elem, void* datos);


bool vectorCrear(Vector* vector, size_t tamElem); // malloc
int vectorCrearDeArchivo(Vector* vector, size_t tamElem, const char* nomArch);
int vectorGrabar(Vector* vector, const char* nomArch);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
int vectorOrdBuscar(const Vector* vector, void* elem, Cmp cmp);
void vectorOrdenar(Vector* vector, int metodo, Cmp cmp);
bool vectorOrdEliminar(Vector* vector, int elem);
bool vectorEliminarDePos(Vector* vector, int pos);
void vectorDestruir(Vector* vector); // free
void vectorMostrar(const Vector* vector, Imprimir imprimir);
void vectorRecorrer(const Vector* vector, Accion accion, void* datos);

size_t max(size_t a, size_t b);


#endif // VECTOR_H
