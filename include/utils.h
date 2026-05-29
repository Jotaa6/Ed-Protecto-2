/*
 * Archivo: utils.h
 * Descripcion: Funciones utilitarias compartidas entre todos los modulos
 * Estructuras: ninguna propia
 * Funciones: pedirEntero, pedirCadena, confirmarAccion, getCurrentTimestamp,
 *            findGalaxyById, findShipById, findEdgeById, findTripById
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstring>
#include <ctime>
#include "galaxy.h"
#include "ship.h"
#include "edge.h"
#include "trip.h"
using namespace std;

// Listas globales de entidades
extern Galaxy* globalGalaxias;
extern Ship*   globalShips;
extern Edge*   globalEdges;
extern Trip*   globalTrips;

/**
 * @brief  Lee entero de cin, repite hasta que se ingrese un entero valido
 *         Limpia estado de error de cin en entrada invalida
 * @param  mensaje  prompt a mostrar al usuario
 * @return entero valido ingresado por el usuario
 */
int pedirEntero(const char* mensaje);

/**
 * @brief  Lee string no vacio via getline, repite hasta que no este vacio
 * @param  mensaje  prompt a mostrar
 * @param  result   arreglo de chars para almacenar resultado
 * @param  maxLen   maximo de caracteres a leer
 * @return void
 */
void pedirCadena(const char* mensaje, char* result, int maxLen);

/**
 * @brief  Muestra pregunta de si/no al usuario
 * @param  mensaje  pregunta a mostrar
 * @return true si el usuario ingresa s o S, false en caso contrario
 */
bool confirmarAccion(const char* mensaje);

/**
 * @brief  Retorna fecha y hora actual como string formateado
 *         Usa localtime_s para compatibilidad con Windows
 * @param  result   arreglo de chars para almacenar el timestamp
 * @param  maxLen   maximo de caracteres a escribir
 * @return void
 */
void getCurrentTimestamp(char* result, int maxLen);

/**
 * @brief  Busca en la lista global de Galaxy por id
 * @param  id  id a buscar
 * @return puntero a Galaxy si se encuentra, nullptr si no
 */
Galaxy* findGalaxyById(int id);

/**
 * @brief  Busca en la lista global de Ship por id
 * @param  id  id a buscar
 * @return puntero a Ship si se encuentra, nullptr si no
 */
Ship* findShipById(int id);

/**
 * @brief  Busca en la lista global de Edge por id
 * @param  id  id a buscar
 * @return puntero a Edge si se encuentra, nullptr si no
 */
Edge* findEdgeById(int id);

/**
 * @brief  Busca en la lista global de Trip por id
 * @param  id  id a buscar
 * @return puntero a Trip si se encuentra, nullptr si no
 */
Trip* findTripById(int id);

#endif
