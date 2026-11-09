/*
 * Archivo: conjunto.c
 * Implementación de un conjunto de estudiantes con capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * No usen memoria dinámica ni archivos.
 * Autoría: Dana Itzel Hernandez Martinez
 */

#include <stdio.h>

#include "conjunto.h"

/* Inicializa la cantidad y la capacidad del conjunto. */
void inicializarConjunto(Conjunto *conjunto, int capacidad) {
    conjunto->cantidad = 0;
    conjunto->capacidad = capacidad;
}

/* Obtiene una posición utilizada para consultarla o modificarla. */
Estudiante *obtenerElemento(Conjunto *conjunto, int indice) {
    if (indice < 0 || indice >= conjunto->cantidad)
        return NULL;
    return &conjunto->elementos[indice];
}

/* Busca por matrícula sólo en las posiciones utilizadas. */
int buscarElemento(const Conjunto *conjunto, const Estudiante *estudiante) {
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (compararEstudiantes(&conjunto->elementos[indice], estudiante) == 0)
            return indice;
    }
    return -1;
}

/* Agrega un estudiante si no existe y queda espacio. */
int agregarElemento(Conjunto *conjunto, const Estudiante *estudiante) {
    // Aquí va su código.
     if (conjunto->cantidad >= conjunto->capacidad)
        return 0;
    if (buscarElemento(conjunto, estudiante) != -1)
        return 0;
    conjunto->elementos[conjunto->cantidad] = *estudiante;
    conjunto->cantidad++;
    return 1;
}

/* Elimina un estudiante y conserva el orden de los restantes. */
int eliminarElemento(Conjunto *conjunto, const Estudiante *estudiante) {
    // Aquí va su código.
    int indice = buscarElemento(conjunto, estudiante);
    if (indice == -1)
        return 0;
    for (int i = indice; i < conjunto->cantidad - 1; i++) {
        conjunto->elementos[i] = conjunto->elementos[i + 1];
    }
    conjunto->cantidad--;
    return 1;
}

/* Sustituye un estudiante sin introducir matrículas repetidas. */
int reemplazarElemento(Conjunto *conjunto, const Estudiante *estudiante,
                       const Estudiante *reemplazo) {
    // Aquí va su código.
     int indice = buscarElemento(conjunto, estudiante);
    if (indice == -1)
        return 0;
    int indiceReemplazo = buscarElemento(conjunto, reemplazo);
    if (indiceReemplazo != -1 && indiceReemplazo != indice)
        return 0;
    conjunto->elementos[indice] = *reemplazo;
    return 1;
}

/* Deja el conjunto vacío y conserva su capacidad. */
void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    void vaciarConjunto(Conjunto *conjunto) {
    // Aquí va su código.
    conjunto->cantidad = 0;
}

/* Copia todos los estudiantes del origen. */
int copiarConjunto(const Conjunto *origen, Conjunto *destino) {
    // Aquí va su código.
     if (destino->capacidad < origen->cantidad)
        return 0;
    destino->cantidad = origen->cantidad;
    for (int i = 0; i < origen->cantidad; i++) {
        destino->elementos[i] = origen->elementos[i];
    }
    return 1;
}

/* Comprueba si todos los estudiantes de A pertenecen a B. */
int esSubconjunto(const Conjunto *conjuntoA, const Conjunto *conjuntoB) {
    // Aquí va su código.
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i]) == -1)
            return 0;
    }
    return 1;
}

/* Comprueba si ambos conjuntos contienen las mismas matrículas. */
int sonConjuntosIguales(const Conjunto *conjuntoA,
                        const Conjunto *conjuntoB) {
    // Aquí va su código.
     if (conjuntoA->cantidad != conjuntoB->cantidad)
        return 0;
    return esSubconjunto(conjuntoA, conjuntoB);
}

/* Calcula la unión conservando primero el orden de A. */
int unirConjuntos(const Conjunto *conjuntoA, const Conjunto *conjuntoB,
                  Conjunto *resultado) {
    // Aquí va su código.
    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (!agregarElemento(resultado, &conjuntoA->elementos[i]))
            return 0;
    }
    for (int i = 0; i < conjuntoB->cantidad; i++) {
        if (buscarElemento(resultado, &conjuntoB->elementos[i]) == -1) {
            if (!agregarElemento(resultado, &conjuntoB->elementos[i]))
                return 0;
        }
    }
    return 1;
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
    vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i]) != -1) {
            if (!agregarElemento(resultado, &conjuntoA->elementos[i]))
                return 0;
        }        
    }
    return 1;
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const Conjunto *conjuntoA,
                         const Conjunto *conjuntoB, Conjunto *resultado) {
    // Aquí va su código.
     vaciarConjunto(resultado);
    for (int i = 0; i < conjuntoA->cantidad; i++) {
        if (buscarElemento(conjuntoB, &conjuntoA->elementos[i]) == -1) {
            if (!agregarElemento(resultado, &conjuntoA->elementos[i]))
                return 0;
        }
    }
    return 1;
}

/* Muestra todos los estudiantes del conjunto entre llaves. */
void mostrarConjunto(const Conjunto *conjunto) {
    printf("{");
    for (int indice = 0; indice < conjunto->cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        mostrarEstudiante(&conjunto->elementos[indice]);
    }
    printf("}\n");
}
