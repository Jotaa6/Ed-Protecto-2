/*
 * Archivo: dijkstra.h
 * Descripcion: Dijkstra usando la lista de adyacencia global del grafo
 * Estructuras: DijkstraResult
 * Funciones: dijkstra, imprimirRutaDijkstra, getUltimoResultado
 * Creado: 1/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora 
 */
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <string>
#include "graph.h"
#include "galaxy.h"

using namespace std;

/**
 * @brief  Almacena un resultado de consulta Dijkstra para el reporte
 * @field  fromId     id de la galaxia origen
 * @field  toId       id de la galaxia destino
 * @field  path       arreglo de ids de galaxias formando el camino
 * @field  pathLen    numero de nodos en el camino
 * @field  cost       costo total del camino
 * @field  siguiente  puntero al siguiente resultado en la lista
 */
struct DijkstraResult {
    string fromId;
    string toId;
    string path[100];
    int pathLen;
    float cost;
    DijkstraResult* siguiente;
};

extern DijkstraResult* dijkstraResults;
extern int dijkstraCount;

/**
 * @brief  Encuentra el camino de menor costo entre dos galaxias usando Dijkstra
 *         Usa arreglos planos de float con escaneo lineal manual
 *         Almacena resultado en lista global dijkstraResults
 *         Incrementa dijkstraCount global
 * @param  origenId   id de la galaxia origen
 * @param  destinoId  id de la galaxia destino
 * @return costo total del camino mas corto, o -1 si no es alcanzable
 */
float dijkstra(string origenId, string destinoId);

/**
 * @brief  Imprime el camino almacenado en un DijkstraResult
 *         Formato: Galaxia A > Galaxia B > Galaxia C | Costo: X
 * @param  result  puntero al DijkstraResult a imprimir
 * @return void
 */
void imprimirRutaDijkstra(DijkstraResult* result);

/**
 * @brief  Retorna puntero al resultado Dijkstra mas reciente
 * @return puntero al ultimo resultado, o nullptr si ninguno fue ejecutado
 */
DijkstraResult* getUltimoResultado();

#endif