/*
 * Archivo: reports.h
 * Descripcion: Generacion de reportes en archivos .txt en /output
 * Estructuras: ninguna propia
 * Funciones: generarReporteRutasCortas, generarReporteRutaOptimizada,
 *            generarReporteEstadisticas, generarTodosLosReportes
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>
#include "file_io.h"
#include "dijkstra.h"
#include "kruskal.h"
#include "galaxy.h"
#include "graph.h"
#include "edge.h"
#include "utils.h"
#include "stats.h"

using namespace std;

/**
 * @brief  Genera /output/rutasMasCortas.txt con todos los resultados
 *         Dijkstra de la sesion
 *         Escribe mensaje de sin datos si dijkstraCount es 0
 * @return void
 */
void generarReporteRutasCortas();

/**
 * @brief  Genera /output/rutaOptimizada.txt con la lista completa
 *         de aristas del MST
 *         Llama buildMST() primero si mstResult es nullptr
 * @return void
 */
void generarReporteRutaOptimizada();

/**
 * @brief  Genera /output/estadisticas.txt con estadisticas de la sesion
 *         Secciones: rutas calculadas, costo promedio, galaxia mas conectada,
 *         comparacion MST vs original, conteos totales
 * @return void
 */
void generarReporteEstadisticas();

/**
 * @brief  Genera los tres reportes de una sola vez
 * @return void
 */
void generarTodosLosReportes();

#endif
