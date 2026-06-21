/*
 * Archivo: dfs_routes.h
 * Descripcion: DFS recursivo para mostrar todas las rutas desde una galaxia
 * Estructuras: ninguna propia
 * Funciones: dfsTodasLasRutas, mostrarTodasLasRutas
 * Creado: 1/6/2026
 * Ultima modificacion: 21/6/2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#ifndef DFS_ROUTES_H
#define DFS_ROUTES_H

#include <string>
#include <iostream>
#include <fstream>
#include "graph.h"
#include "galaxy.h"
using namespace std;

/**
 * @brief  Encuentra e imprime recursivamente todos los caminos desde origen
 *         Usa DFS con backtracking. Escribe directamente en un archivo si se proporciona.
 * @param  origen  vertice actual siendo visitado
 * @param  ruta    string acumulando el camino actual para mostrar
 * @param  costo   costo acumulado del camino actual
 * @param  count   puntero al contador de caminos encontrados
 * @param  archivo puntero a ofstream donde se escribiran las rutas (opcional)
 * @return void
 */
void dfsTodasLasRutas(Vertice* origen, string ruta, float costo, int* count, ofstream* archivo = nullptr);

/**
 * @brief  Punto de entrada para la consulta de todas las rutas
 *         Llama desmarcarVertices() y luego dfsTodasLasRutas()
 *         Guarda TODAS las rutas en /output/todasLasRutas.txt
 *         No imprime las rutas en terminal, solo un mensaje de confirmacion.
 * @param  galaxyId  id de la galaxia origen
 * @return void
 */
void mostrarTodasLasRutas(string galaxyId);

#endif
