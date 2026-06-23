/*
 * Archivo: entities.h
 * Descripcion: Implementaciones CRUD especificas para cada entidad
 * Estructuras: ninguna propia
 * Funciones: listarGalaxias, agregarGalaxia, editarGalaxia, eliminarGalaxia,
 *            buscarGalaxyPorId, listarNaves, agregarNave, editarNave,
 *            eliminarNave, buscarNavePorId, listarRutas, agregarRuta,
 *            editarRuta, eliminarRuta, buscarRutaPorId, listarViajes,
 *            registrarViaje, editarViaje, eliminarViaje, buscarViajePorId
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <Jorge Ulate>
 */
#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <string>
#include "crud.h"
#include "galaxy.h"
#include "ship.h"
#include "edge.h"
#include "trip.h"
#include "graph.h"
#include "utils.h"
using namespace std;
// Funciones de detalle para impresion individual
void printGalaxyDetail(void* item);
void printShipDetail(void* item);
void printEdgeDetail(void* item);
void printTripDetail(void* item);

// Configuraciones CrudConfig para cada entidad
extern CrudConfig galaxyConfig;
extern CrudConfig shipConfig;
extern CrudConfig routeConfig;
extern CrudConfig tripConfig;


/** @brief Imprime todas las galaxias de la lista global. @return void */
void listarGalaxias();

/** @brief Solicita campos y agrega galaxia en memoria. @return void */
void agregarGalaxia();

/** @brief Edita nombre o coordenadas en memoria por id. @param id id a editar. @return void */
void editarGalaxia(string id);

/** @brief Elimina galaxia de memoria y del grafo. @param id id a eliminar. @return void */
void eliminarGalaxia(string id);

/** @brief Busca galaxia por id. @param id id a buscar. @return void* a Galaxy o nullptr */
void* buscarGalaxyPorId(string id);


/** @brief Imprime todas las naves. @return void */
void listarNaves();

/** @brief Agrega nave en memoria. @return void */
void agregarNave();

/** @brief Edita nombre en memoria por id. @param id id a editar. @return void */
void editarNave(string id);

/** @brief Elimina nave de memoria. @param id id a eliminar. @return void */
void eliminarNave(string id);

/** @brief Busca nave por id. @param id id a buscar. @return void* a Ship o nullptr */
void* buscarNavePorId(string id);


/** @brief Imprime todas las rutas. @return void */
void listarRutas();

/** @brief Agrega ruta en memoria y en el grafo. @return void */
void agregarRuta();

/** @brief Edita costo en memoria y en el grafo por id. @param id id a editar. @return void */
void editarRuta(string id);

/** @brief Elimina ruta de memoria y del grafo. @param id id a eliminar. @return void */
void eliminarRuta(string id);

/** @brief Busca ruta por id. @param id id a buscar. @return void* a Edge o nullptr */
void* buscarRutaPorId(string id);


/** @brief Imprime todos los viajes. @return void */
void listarViajes();

/** @brief Registra viaje en memoria. @return void */
void registrarViaje();

/** @brief Edita costo o fecha en memoria por id. @param id id a editar. @return void */
void editarViaje(string id);

/** @brief Elimina viaje de memoria y del historial de la nave. @param id id a eliminar. @return void */
void eliminarViaje(string id);

/** @brief Busca viaje por id. @param id id a buscar. @return void* a Trip o nullptr */
void* buscarViajePorId(string id);

// Funciones de detalle para imprimir un solo registro

void printGalaxyDetail(void* item);

void printShipDetail(void* item);

void printEdgeDetail(void* item);

void printTripDetail(void* item);
#endif
