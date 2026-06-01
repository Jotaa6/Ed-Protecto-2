/*
 * Archivo: kruskal.h
 * Descripcion: Algoritmo de Kruskal aleatorio usando lista de aristas de la API
 * Estructuras: ninguna propia
 * Funciones: buildMST, imprimirMST
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: Jose Pablo Barrantes Hernandez
 */
#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <iostream>
#include "edge.h"
#include "galaxy.h"
#include "union_find.h"
using namespace std;

/*
 * Resultado global del MST construido por Kruskal
 */
extern Edge* mstResult;

/*
 * Costo total acumulado del MST
 */
extern float mstTotalCost;

/**
 * @brief  Construye el MST usando el algoritmo de Kruskal aleatorio modificado
 *         Usa la lista de aristas pre-mezclada de la API y Union-Find para detectar ciclos
 *         Almacena resultado en mstResult y mstTotalCost globales
 * @param  kruskalEdges  lista enlazada de aristas en orden aleatorio de la API
 * @param  nodeCount     total de vertices en el grafo
 * @return void
 */
void buildMST(Edge* kruskalEdges, int nodeCount);

/**
 * @brief  Imprime el MST en terminal con nombres de galaxias y costos
 * @param  mst  lista enlazada de aristas que forman el MST
 * @return void
 */
void imprimirMST(Edge* mst);

#endif
