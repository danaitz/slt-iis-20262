/*
 * Archivo: conjunto.c
 * Implementación de un conjunto genérico con almacenamiento dinámico.
 * Completen las funciones pendientes según conjunto.h.
 * Autoría: Hernaández Martínez Dana Itzel.
 */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conjunto.h"

/* Inicializa el conjunto y reserva un arreglo lleno de bytes con valor 0. */
int inicializarConjunto(Conjunto *conjunto, int capacidadInicial,
                        size_t tamElemento, Comparador comparar) {
    // Aquí va su código.
    if (capacidadInicial <= 0 || tamElemento == 0 || !comparar)
        return 0;
    
    conjunto->elementos = calloc((size_t)capacidadInicial, tamElemento);
    if (!conjunto->elementos)
        return 0;
        
    conjunto->cantidad = 0;
    conjunto->capacidad = capacidadInicial;
    conjunto->tamElemento = tamElemento;
    conjunto->comparar = comparar;
    return 1;
}

/* Obtiene una posición utilizada para consultarla o modificarla. */
void *obtenerElemento(Conjunto *conjunto, int indice) {
    if (indice < 0 || indice >= conjunto->cantidad)
        return NULL;
    unsigned char *inicio = conjunto->elementos;
    return inicio + (size_t)indice * conjunto->tamElemento;
}

/* Busca con el comparador sólo en las posiciones utilizadas. */
int buscarElemento(const Conjunto *conjunto, const void *elemento) {
    const unsigned char *inicio = conjunto->elementos;
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        const void *actual = inicio + (size_t)indice * conjunto->tamElemento;
        if (conjunto->comparar(actual, elemento) == 0)
            return indice;
    }
    return -1;
}

/* Agrega un elemento y duplica la capacidad cuando el arreglo está lleno. */
int agregarElemento(Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    if (buscarElemento(conjunto, elemento) != -1)
        return 0;

    if (conjunto->cantidad >= conjunto->capacidad) {
        int nuevaCapacidad = conjunto->capacidad * 2;
        void *nuevoArreglo = realloc(conjunto->elementos, (size_t)nuevaCapacidad * conjunto->tamElemento);
        if (!nuevoArreglo)
            return 0;
        conjunto->elementos = nuevoArreglo;
        conjunto->capacidad = nuevaCapacidad;
    }

    unsigned char *destino = (unsigned char *)conjunto->elementos + (size_t)conjunto->cantidad * conjunto->tamElemento;
    memcpy(destino, elemento, conjunto->tamElemento);
    conjunto->cantidad++;
    return 1;
}

/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    int indice = buscarElemento(conjunto, elemento);
    if (indice == -1)
        return 0;

    unsigned char *inicio = conjunto->elementos;
    void *destino = inicio + (size_t)indice * conjunto->tamElemento;
    void *origen = inicio + (size_t)(indice + 1) * conjunto->tamElemento;
    size_t bytesACopiar = (size_t)(conjunto->cantidad - indice - 1) * conjunto->tamElemento;

    if (bytesACopiar > 0) {
        memmove(destino, origen, bytesACopiar);
    }
    conjunto->cantidad--;
    return 1;
}

/* Sustituye un elemento sin introducir elementos repetidos. */
int reemplazarElemento(Conjunto *conjunto, const void *elemento,
                       const void *reemplazo) {
    // Aquí va su código.
    int indice = buscarElemento(conjunto, elemento);
    if (indice == -1)
        return 0;
    if (buscarElemento(conjunto, reemplazo) != -1)
        return 0;

    unsigned char *inicio = conjunto->elementos;
    memcpy(inicio + (size_t)indice * conjunto->tamElemento, reemplazo, conjunto->tamElemento);
    return 1;
}

/* Libera el arreglo y deja el conjunto listo para volver a crecer. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    free(conjunto->elementos);
    conjunto->elementos = NULL;
    conjunto->cantidad = 0;
    conjunto->capacidad = 0;
}

/* Copia todos los elementos y amplía el destino cuando hace falta. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    // Aquí va su código.
    if (destino->capacidad < origen->cantidad) {
        void *nuevoArreglo = realloc(destino->elementos, (size_t)origen->cantidad * origen->tamElemento);
        if (!nuevoArreglo)
            return 0;
        destino->elementos = nuevoArreglo;
        destino->capacidad = origen->cantidad;
    }
    memcpy(destino->elementos, origen->elementos, (size_t)origen->cantidad * origen->tamElemento);
    destino->cantidad = origen->cantidad;
    destino->tamElemento = origen->tamElemento;
    destino->comparar = origen->comparar;
    return 1;
}

/* Comprueba si todos los elementos de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    // Aquí va su código.
    const unsigned char *inicioA = conjuntoA->elementos;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = inicioA + (size_t)i * conjuntoA->tamElemento;
        if (buscarElemento(conjuntoB, elem) == -1)
            return 0;
    }
    return 1;
}

/* Comprueba si ambos conjuntos contienen los mismos elementos. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB) {
    // Aquí va su código.
    if (conjuntoA->cantidad != conjuntoB->cantidad)
        return 0;
    return esSubconjunto(conjuntoA, conjuntoB);
}

/* Calcula la unión y reserva de antemano la capacidad necesaria. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
    if (!inicializarConjunto(resultado, conjuntoA->cantidad + conjuntoB->cantidad, conjuntoA->tamElemento, conjuntoA->comparar))
        return 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        agregarElemento(resultado, obtenerElemento((Conjunto*)conjuntoA, i));
    }
    for (int i = 0; i < conjuntoB->cantidad; i++) {
        agregarElemento(resultado, obtenerElemento((Conjunto*)conjuntoB, i));
    }
    return 1;
}

/* Calcula la intersección y reserva de antemano la capacidad necesaria. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    int cap = conjuntoA->cantidad < conjuntoB->cantidad ? conjuntoA->cantidad : conjuntoB->cantidad;
    if (!inicializarConjunto(resultado, cap > 0 ? cap : 1, conjuntoA->tamElemento, conjuntoA->comparar))
        return 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = obtenerElemento((Conjunto*)conjuntoA, i);
        if (buscarElemento(conjuntoB, elem) != -1) {
            agregarElemento(resultado, elem);
        }
    }
    return 1;
}

/* Calcula la diferencia y reserva de antemano la capacidad necesaria. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    if (!inicializarConjunto(resultado, conjuntoA->cantidad > 0 ? conjuntoA->cantidad : 1, conjuntoA->tamElemento, conjuntoA->comparar))
        return 0;
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        const void *elem = obtenerElemento((Conjunto*)conjuntoA, i);
        if (buscarElemento(conjuntoB, elem) == -1) {
            agregarElemento(resultado, elem);
        }
    }
    return 1;
}

/* Intercambia registros completos mediante almacenamiento temporal dinámico. */
int intercambiarElementos(Conjunto *conjunto, int indiceA, int indiceB) {
    // Aquí va su código.
    if (indiceA < 0 || indiceA >= conjunto->cantidad || indiceB < 0 || indiceB >= conjunto->cantidad)
        return 0;
    if (indiceA == indiceB)
        return 1;

    unsigned char *inicio = conjunto->elementos;
    void *ptrA = inicio + (size_t)indiceA * conjunto->tamElemento;
    void *ptrB = inicio + (size_t)indiceB * conjunto->tamElemento;

    void *temp = malloc(conjunto->tamElemento);
    if (!temp)
        return 0;

    memcpy(temp, ptrA, conjunto->tamElemento);
    memcpy(ptrA, ptrB, conjunto->tamElemento);
    memcpy(ptrB, temp, conjunto->tamElemento);
    free(temp);
    return 1;
}

/* Ordena con el mismo comparador que determina la pertenencia. */
void ordenarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    if (conjunto->cantidad <= 1)
        return;
    qsort(conjunto->elementos, (size_t)conjunto->cantidad, conjunto->tamElemento, conjunto->comparar);
}

/* Busca mediante búsqueda binaria en un conjunto ya ordenado. */
int buscarElementoOrdenado(const Conjunto *conjunto, const void *elemento) {
    // Aquí va su código.
    if (conjunto->cantidad == 0)
        return -1;
    void *res = bsearch(elemento, conjunto->elementos, (size_t)conjunto->cantidad, conjunto->tamElemento, conjunto->comparar);
    if (!res)
        return -1;
    unsigned char *inicio = conjunto->elementos;
    return (int)(((unsigned char *)res - inicio) / conjunto->tamElemento);
}

/* Muestra el contenido mediante la función correspondiente al tipo. */
void mostrarConjunto(const Conjunto *conjunto, MostrarElemento mostrar) {
    const unsigned char *inicio = conjunto->elementos;
    printf("{");
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        mostrar(inicio + (size_t)indice * conjunto->tamElemento);
    }
    printf("}\n");
}
