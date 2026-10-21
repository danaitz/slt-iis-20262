/*
 * Archivo: conjunto.c
 * Implementación de conjuntos de enteros con arreglos de capacidad fija.
 * Completen las funciones pendientes según conjunto.h.
 * Usen funciones, arreglos y apuntadores; no usen estructuras, memoria
 * dinámica, archivos ni ordenamientos.
 * Autoría: Dana Itzel Hernandez Martinez
 */

#include <stdio.h>

#include "conjunto.h"

/* Busca únicamente en las posiciones utilizadas del conjunto. */
int buscarElemento(const int conjunto[], int cantidad, int elemento) {
    for (int indice = 0; indice < cantidad; indice++) {
        if (conjunto[indice] == elemento)
            return indice;
    }
    return -1;
}

/* Agrega un elemento si no existe y queda espacio. */
int agregarElemento(int conjunto[], int capacidad, int *cantidad,
                    int elemento) {
    // Aquí va su código.
       if(*cantidad >= capacidad){
        return 0;
    }
    if(buscarElemento(conjunto, *cantidad, elemento) != -1){
        return 0;
    }
    conjunto[*cantidad] = elemento;
    (*cantidad)++;
    return 1;
}


/* Elimina un elemento y conserva el orden de los restantes. */
int eliminarElemento(int conjunto[], int *cantidad, int elemento) {
    // Aquí va su código.
     int indice = buscarElement0(conjunto, *cantidad, elemento);
    if(indice == -1){
        return 0;
    }
    for(int i = indice; i < *cantidad - 1; i++){
        conjunto[i] = conjunto[i + 1];
    }
    (*cantidad)--;
    return 1;  
}

/* Sustituye un elemento sin cambiar la cantidad ni introducir repetidos. */
int reemplazarElemento(int conjunto[], int cantidad, int elemento,
                       int reemplazo) {
    // Aquí va su código.
        int indice = buscarElemento(conjunto, cantidad, elemento);
    if(indice == -1){
        return 0;
    }
    if(elemento == reemplazo){
        return 1;
    }
    if(buscarElemento(conjunto, cantidad, reemplaz) != -1){
        return 0;
    }
    conjunto[indice] = reemplazo;
    return 1;
}

/* Deja el conjunto vacío, conservando el arreglo y su capacidad. */
void vaciarConjunto(int *cantidad) {
    // Aquí va su código.
     *cantidad = 0;
}

/* Copia los elementos a otro arreglo, conservando su orden. */
int copiarConjunto(const int origen[], int cantidad,
                   int destino[], int capacidadDestino) {
    // Aquí va su código.
     if (capacidadDestino < cantidad){
        return 0;
    }
    for(int i = 0; i < cantidad; i++){
        destino[i] = origen[i];
    }
    resturn cantidad;
}

/* Indica si A es subconjunto de B, sin importar el orden. */
int esSubconjunto(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB) {
    // Aquí va su código.
     for (int i = 0; i < cantidadA; i++){
        if(buscarElemento(conjuntoB, conjuntoA[i]) == -1){
            return 0;
        }
    }
}

/* Indica si los conjuntos tienen los mismos elementos, sin importar el orden. */
int sonConjuntosIguales(const int conjuntoA[], int cantidadA,
                       const int conjuntoB[], int cantidadB) {
    // Aquí va su código.
    if(cantidadA != cantidadB){
        return 0;
    }
    return esSubcojunto(conjuntoA, cantidadA, conjuntoB, CantidadB);
}

/* Calcula la unión conservando primero A y después los elementos nuevos de B. */
int unirConjuntos(const int conjuntoA[], int cantidadA,
                 const int conjuntoB[], int cantidadB,
                 int resultado[], int capacidadResultado) {
    // Aquí va su código.
     int cantidadResultado = 0;
    if (capacidadResultado < cantidadA){
        return -1;
    }
    for (int i = 0; i < cnatidadA; i++){
        resultado[i] = conjuntoA[i];
        cantidadResultado++;
    }
    for (int i = 0; i < cantidadB; i++){
        if (buscarElemento(conjuntoB, cantidadB, conjuntoA[i]) ! = -1){
            if(cantidadResultado >= capacidadResultado){
                retirn -1;
            }
            resultado[cantidadResultado] = conjuntoA[i];
            cantidadResultado++;
        }
    }
    return cantidadResultado;
}

/* Calcula la intersección conservando el orden de A. */
int intersectarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado) {
    // Aquí va su código.
    int cantidadResultado = 0;
    for (int i = 0; i < cantidadA; i++) {
        if (buscarElemento(conjuntoB, cantidadB, conjuntoA[i]) != -1) {
            if (cantidadResultado >= capacidadResultado) {
                return -1;
}
            resultado[cantidadResultado] = conjuntoA[i];
            cantidadResultado++;
        }
        return cantidadResultado;
}

/* Calcula la diferencia A-B conservando el orden de A. */
int diferenciarConjuntos(const int conjuntoA[], int cantidadA,
                        const int conjuntoB[], int cantidadB,
                        int resultado[], int capacidadResultado) {
    // Aquí va su código.
     int cantidadResultado = 0;
    for (int i = 0; i < cantidadA; i++) {
        if (buscarElemento(conjuntoB, cantidadB, conjuntoA[i]) == -1) {
            if (cantidadResultado >= capacidadResultado) {
                return -1;
            }
            resultado[cantidadResultado] = conjuntoA[i];
            cantidadResultado++;
        }
    }
}
/* Muestra el conjunto con llaves, comas y un salto de línea al final. */
void mostrarConjunto(const int conjunto[], int cantidad) {
    printf("{");
    for (int indice = 0; indice < cantidad; indice++) {
        if (indice > 0)
            printf(", ");
        printf("%d", conjunto[indice]);
    }
    printf("}\n");
}
