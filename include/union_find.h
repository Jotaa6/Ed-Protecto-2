/*
 * Archivo: union_find.h
 * Descripcion: Estructura Union-Find para deteccion de ciclos en el algoritmo de Kruskal
 * Estructuras: ninguna propia
 * Funciones: initUnionFind, findRoot, unite, connected
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef UNION_FIND_H
#define UNION_FIND_H

// Arreglo de padres — parent[i] = padre del nodo i en el bosque disjunto
extern int parent[100];

// Arreglo de rangos — rankArr[i] = rango del nodo i para union por rango
extern int rankArr[100];

/**
 * @brief  Inicializa n conjuntos disjuntos
 *         Cada nodo comienza siendo su propio padre con rango 0
 * @param  n  numero de nodos en el grafo
 * @return void
 */
void initUnionFind(int n);

/**
 * @brief  Encuentra la raiz del conjunto que contiene al nodo x
 *         Aplica compresion de camino para aplanar el arbol
 * @param  x  nodo del cual se quiere encontrar la raiz
 * @return id de la raiz del conjunto que contiene a x
 */
int findRoot(int x);

/**
 * @brief  Une los conjuntos que contienen a x e y usando union por rango
 * @param  x  primer nodo
 * @param  y  segundo nodo
 * @return true si se unieron exitosamente (estaban en conjuntos distintos)
 *         false si ya estaban en el mismo conjunto (se detecta un ciclo)
 */
bool unite(int x, int y);

/**
 * @brief  Verifica si dos nodos pertenecen al mismo conjunto
 * @param  x  primer nodo
 * @param  y  segundo nodo
 * @return true si comparten la misma raiz, false en caso contrario
 */
bool connected(int x, int y);

#endif
