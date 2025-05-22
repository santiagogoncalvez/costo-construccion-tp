# Costo de la Construcción - TP de Tópicos (2025)

## Estructura del proyecto

El repositorio va a contener 2 proyectos: uno que es la librería lib-costo-construccion que es el programa principal y costo-construccion-consola, que es el que va a consumir esta librería.

Los archivos de datos del trabajo van a estar dentro de la carpeta `/datos`.

Las consignas y documentos van a estar dentro de la carpeta `/documentos`.

La carpeta `/pruebas` va a contener las funciones y códigos que prueben y examinen la librería lib-costo-construccion.

## Qué hace la librería

Permite **ver índices y variaciones** del indicador económico de **Costo de la Construcción**.

## Cómo compilar en Code::Blocks

Abrir `costo-construccion-consola/costo-construccion-consola.cbp` y presionar F9.

## 🚫 Qué no subir al repositorio

Evita subir:

-  Rutas absolutas (como C:/Users/...). Usá rutas relativas al proyecto: `#include "../include/mis_funciones.h"`
-  `.cbp` con rutas específicas
-  Archivos temporales del compilador
-  Archivos personales
-  Tu configuración de entorno
-  Ejecutables para Windows (.exe)

## 📅 Cronograma y fechas

Fecha de inicio: 18/05/2025  
Fecha de entrega: 20/06/2025  
Fecha de defensa: 26/05/2025

Semana 1:
Creación del repositorio de github.
Desarrollo de las funciones de la 1 a la 5, una por cada integrante.

Semana 2:
Desarrollo de las funciones 6 a 12

Semana 3:
Testeo de todas las funciones.

Semana 4:
Estudio y entendimiento del código para la defensa oral.

## 📌 Reglas y Requerimientos

-  Cada función va a tener su propio archivo separado: `nombre-funcion.c` y los prototipos de cad una van a estar dentro de 
-  Las funciones tienen que funcionar mínimo para todos los casos de prueba que presentan.
-  Vectores y cadenas de texto deberán ser manipulados utilizando aritmética de punteros.
-  Las soluciones tienen que ser eficientes:
   En el uso de memoria: no declarar vectores o matrices auxiliares si no es necesario.
   En cantidad de ciclos de procesador y en el caso de matrices las soluciones deben ser óptimas.
   En recorridos de archivos: estos tienen que ser mínimos.
-  Nunca acceder a memoria que no nos pertenece
-  Declarar variables al inicio del bloque y no utilizar VLA (Variable length arrays).
-  Código prolijo y dividido en funciones.
-  Poner nombres significativos a las variables.
-  Las soluciones tienen que estar desarrolladas en ANSI C para garantizar tanto como sea posible compatibilidad multiplataforma.
-  Nunca mezclar funciones de manipulación de archivos de texto con funciones de operación de archivos binarios.
-  Las funciones no deben tener errores ni warnings.

**Grupo:** LOS CIBERNÉTICOS  
**Cátedra:** Tópicos de Programación - 1C 2025 - Miércoles
