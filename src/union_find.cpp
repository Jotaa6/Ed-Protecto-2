/*
 * Archivo: union_find.cpp
 * Descripcion: Implementacion del Union-Find para deteccion de ciclos en Kruskal
 * Estructuras: ninguna propia
 * Funciones: initUnionFind, findRoot, unite, connected
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#include "../include/union_find.h"

// Definicion de las variables globales
int parent[100];
int rankArr[100];

/**
 * @brief  Inicializa n conjuntos disjuntos
 *         Cada nodo comienza siendo su propio padre con rango 0
 * @param  n  numero de nodos en el grafo
 * @return void
 */
void initUnionFind(int n) {
    for (int i = 0; i < n; i++) {
        parent[i]  = i;
        rankArr[i] = 0;
    }
}

/**
 * @brief  Encuentra la raiz del conjunto que contiene al nodo x
 *         Aplica compresion de camino para aplanar el arbol
 * @param  x  nodo del cual se quiere encontrar la raiz
 * @return id de la raiz del conjunto que contiene a x
 */
int findRoot(int x) {
    if (parent[x] != x)
        parent[x] = findRoot(parent[x]);
    return parent[x];
}

/**
 * @brief  Une los conjuntos que contienen a x e y usando union por rango
 * @param  x  primer nodo
 * @param  y  segundo nodo
 * @return true si se unieron exitosamente (estaban en conjuntos distintos)
 *         false si ya estaban en el mismo conjunto (se detecta un ciclo)
 */
bool unite(int x, int y) {
    int rootX = findRoot(x);
    int rootY = findRoot(y);

    if (rootX == rootY)
        return false;

    if (rankArr[rootX] < rankArr[rootY])
        parent[rootX] = rootY;
    else if (rankArr[rootX] > rankArr[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rankArr[rootX]++;
    }

    return true;
}

/**
 * @brief  Verifica si dos nodos pertenecen al mismo conjunto
 * @param  x  primer nodo
 * @param  y  segundo nodo
 * @return true si comparten la misma raiz, false en caso contrario
 */
bool connected(int x, int y) {
    return findRoot(x) == findRoot(y);
}
