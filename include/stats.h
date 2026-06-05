/*
 * Archivo: stats.h
 * Descripcion: Motor de estadisticas para el informe estadistico
 * Estructuras: ninguna propia
 * Funciones: getTotalRutasCalculadas, getGalaxiaMasConectada,
 *            getCostoPromedio, imprimirComparacionMST
 * Creado: 4/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#ifndef STATS_H
#define STATS_H

#include <fstream>
#include <iostream>
#include <cstring>
#include "graph.h"
#include "galaxy.h"
#include "edge.h"
#include "kruskal.h"
#include "dijkstra.h"
#include "utils.h"

using namespace std;

/**
 * @brief  Retorna el total de consultas Dijkstra ejecutadas en la sesion
 * @return valor global de dijkstraCount
 */
int getTotalRutasCalculadas();

/**
 * @brief  Encuentra la galaxia con mas arcos de salida en el grafo
 * @param  result  arreglo de chars para almacenar nombre de la galaxia mas conectada
 * @param  degree  salida — numero de arcos de la galaxia mas conectada
 * @return void
 */
void getGalaxiaMasConectada(char* result, int& degree);

/**
 * @brief  Calcula el costo promedio de todas las aristas en la lista global
 * @return costo promedio como float, o 0.0 si no hay aristas
 */
float getCostoPromedio();

/**
 * @brief  Imprime comparacion MST vs costos originales en un archivo abierto
 * @param  archivo  referencia a ofstream abierto donde escribir
 * @return void
 */
void imprimirComparacionMST(ofstream& archivo);

#endif