/*
 * Archivo: dfs_routes.h
 * Descripcion: DFS recursivo para mostrar todas las rutas desde una galaxia
 * Estructuras: ninguna propia
 * Funciones: dfsTodasLasRutas, mostrarTodasLasRutas
 * Creado: 1/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#ifndef DFS_ROUTES_H
#define DFS_ROUTES_H

#include <string>
#include <iostream>
#include "graph.h"
#include "galaxy.h"
using namespace std;

/**
 * @brief  Encuentra e imprime recursivamente todos los caminos desde origen
 *         Usa DFS
 *         Marca visitado=true, recorre arcos, recursa, luego pone visitado=false
 * @param  origen  vertice actual siendo visitado
 * @param  ruta    string acumulando el camino actual para mostrar
 * @param  costo   costo acumulado del camino actual como float
 * @param  count   puntero al contador de caminos encontrados como float
 * @return void
 */
void dfsTodasLasRutas(Vertice* origen, string ruta, float costo, float* count);

/**
 * @brief  Punto de entrada para la consulta de todas las rutas
 *         Llama desmarcarVertices() y luego dfsTodasLasRutas()
 *         Limita la salida a los primeros 50 caminos
 * @param  galaxyId  id string de la galaxia origen
 * @return void
 */
void mostrarTodasLasRutas(string galaxyId);

#endif
