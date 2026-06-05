/*
 * Archivo: queries.h
 * Descripcion: Las cuatro consultas requeridas por el proyecto
 * Estructuras: ninguna propia
 * Funciones: validarGalaxia, validarNave, queryTodasLasRutas,
 *            queryRutaMenorCosto, queryArbolKruskal, queryHistorialNave
 * Creado: 4/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#ifndef QUERIES_H
#define QUERIES_H

#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
#include "galaxy.h"
#include "ship.h"
#include "dijkstra.h"
#include "dfs_routes.h"
#include "kruskal.h"
#include "file_io.h"
#include "utils.h"

using namespace std;

/**
 * @brief  Valida que un id de galaxia existe en el grafo global
 * @param  galaxyId    id numerico a validar
 * @param  entityName  nombre para mostrar en mensaje de error
 * @return true si existe, false si no se encuentra
 */
bool validarGalaxia(int galaxyId, const char* entityName);

/**
 * @brief  Valida que un id de nave existe en la lista global de naves
 * @param  shipId  id numerico a validar
 * @return true si existe, false si no se encuentra
 */
bool validarNave(int shipId);

/**
 * @brief  Consulta 1 — muestra todas las rutas posibles desde una galaxia usando DFS
 * @param  galaxyId  id numerico de la galaxia origen
 * @return void
 */
void queryTodasLasRutas(int galaxyId);

/**
 * @brief  Consulta 2 — muestra la ruta de menor costo entre dos galaxias
 *         Resultado almacenado en lista global dijkstraResults para reporte
 * @param  origenId   id numerico de la galaxia origen
 * @param  destinoId  id numerico de la galaxia destino
 * @return void
 */
void queryRutaMenorCosto(int origenId, int destinoId);

/**
 * @brief  Consulta 3 — muestra el MST de Kruskal en terminal
 *         Escribe /output/resultantesKruskal.txt automaticamente cada vez
 *         Llama buildMST() primero si mstResult es nullptr
 * @return void
 */
void queryArbolKruskal();

/**
 * @brief  Consulta 4 — muestra historial completo de viajes de una nave
 * @param  shipId  id numerico de la nave a consultar
 * @return void
 */
void queryHistorialNave(int shipId);

#endif