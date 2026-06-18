/*
 * Archivo: data_loader.h
 * Descripcion: Carga automatica de todos los datos de la API al inicio
 * Estructuras: ninguna propia
 * Funciones: loadAll, printLoadStep
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <Jorge Ulate>
 */
#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <iostream>
#include "api_client.h"
#include "json_parser.h"
#include "graph.h"
#include "kruskal.h"
#include "utils.h"
using namespace std;

/**
 * @brief  Orquesta la carga completa de datos en 8 pasos al inicio
 *         Paso 1: GET /galaxias  → parseGalaxias  → globalGalaxias + insertarVertice
 *         Paso 2: GET /rutas     → parseRutas      → globalEdges + insertarArco
 *         Paso 3: GET /grafo     → parseGrafo      → verificacion de estructura
 *         Paso 4: GET /grafo/adyacencia → parseAdyacencia → adjMatrix float**
 *         Paso 5: GET /naves     → parseNaves      → globalShips
 *         Paso 6: GET /historial → parseHistorial  → globalTrips + adjuntar a naves
 *         Paso 7: GET /grafo/kruskal → parseKruskal → buildMST → mstResult
 *         Paso 8: imprimir resumen
 *         Despues de retornar la API nunca se vuelve a llamar
 * @return void
 */
void loadAll();

/**
 * @brief  Imprime un mensaje de paso de carga en terminal
 * @param  paso     numero del paso a mostrar
 * @param  mensaje  descripcion de lo que se esta cargando
 * @return void
 */
void printLoadStep(int paso, const char* mensaje);

#endif
