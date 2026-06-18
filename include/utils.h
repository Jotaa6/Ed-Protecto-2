/*
 * Archivo: utils.h
 * Descripcion: Funciones utilitarias compartidas entre todos los modulos
 * Estructuras: ninguna propia
 * Funciones: pedirEntero, pedirCadena, pedirFloat, confirmarAccion,
 *            getCurrentTimestamp, findGalaxyById, findShipById,
 *            findEdgeById, findTripById, playAudio, freeAll
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <Jorge Ulate>
 */
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
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
 * @brief  Lee un numero decimal de cin, repite hasta que se ingrese un valor valido
 * @param  mensaje  prompt a mostrar al usuario
 * @return numero decimal valido ingresado por el usuario
 */
float pedirFloat(const char* mensaje);

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
 * @brief  Busca en la lista global de Galaxy por id string
 * @param  id  id string a buscar e.g. "galaxia-1"
 * @return puntero a Galaxy si se encuentra, nullptr si no
 */
Galaxy* findGalaxyById(string id);

/**
 * @brief  Busca en la lista global de Ship por id string
 * @param  id  id string a buscar e.g. "nave-1"
 * @return puntero a Ship si se encuentra, nullptr si no
 */
Ship* findShipById(string id);

/**
 * @brief  Busca en la lista global de Edge por id string
 * @param  id  id string a buscar e.g. "ruta-1"
 * @return puntero a Edge si se encuentra, nullptr si no
 */
Edge* findEdgeById(string id);

/**
 * @brief  Busca en la lista global de Trip por id string
 * @param  id  id string a buscar e.g. "viaje-1"
 * @return puntero a Trip si se encuentra, nullptr si no
 */
Trip* findTripById(string id);

/**
 * @brief  Reproduce un archivo WAV de forma asíncrona usando PlaySound
 * @param  filename  nombre del archivo .wav (ej. "Guardianes.wav")
 * @return void
 */
void playAudio(const char* filename);

/**
 * @brief  Libera toda la memoria dinámica de las listas globales y del grafo
 *         Debe llamarse justo antes de salir del programa
 * @return void
 */
void freeAll();

#endif
