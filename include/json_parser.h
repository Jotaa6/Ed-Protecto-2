/*
 * Archivo: json_parser.h
 * Descripcion: Parseo de JSON crudo a structs de C++ en tres capas
 * Estructuras: ninguna propia
 * Funciones: extractString, extractInt, extractFloat, extractBool,
 *            splitJsonArray, extractObject, extractNestedArray,
 *            parseGalaxia, parseRuta, parseNave, parseViaje,
 *            parseGalaxias, parseGalaxiaById, parseRutas, parseRutaById,
 *            parseNaves, parseNaveById, parseHistorial, parseViajeById,
 *            parseHistorialNave, parseGrafo, parseKruskal, parseAdyacencia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <cstring>
#include <cstdlib>
#include <iostream>
#include "galaxy.h"
#include "edge.h"
#include "ship.h"
#include "trip.h"
using namespace std;

// ── Capa 1 — extractores crudos ───────────────────────────────────────────

/**
 * @brief  Extrae valor string para una clave en un objeto JSON plano
 * @param  json    JSON crudo
 * @param  key     nombre del campo a buscar
 * @param  result  arreglo de chars de salida
 * @param  maxLen  max chars a copiar en result
 * @return void
 */
void extractString(const char* json, const char* key,
                   char* result, int maxLen);

/**
 * @brief  Extrae valor int para una clave en un objeto JSON plano
 * @param  json  JSON crudo
 * @param  key   nombre del campo a buscar
 * @return int extraido, o -1 si no se encuentra
 */
int extractInt(const char* json, const char* key);

/**
 * @brief  Extrae valor float para una clave en un objeto JSON plano
 * @param  json  JSON crudo
 * @param  key   nombre del campo a buscar
 * @return float extraido, o 0.0 si no se encuentra
 */
float extractFloat(const char* json, const char* key);

/**
 * @brief  Extrae valor bool para una clave en un objeto JSON plano
 * @param  json  JSON crudo
 * @param  key   nombre del campo a buscar
 * @return true si el valor es "true", false en caso contrario
 */
bool extractBool(const char* json, const char* key);

/**
 * @brief  Divide arreglo JSON en strings de objetos o sub-arreglos individuales
 * @param  jsonArray  arreglo JSON crudo
 * @param  results    arreglo de salida
 * @param  maxItems   max elementos a extraer
 * @param  count      salida — numero de elementos encontrados
 * @return void
 */
void splitJsonArray(const char* jsonArray, char results[][2048],
                    int maxItems, int& count);

/**
 * @brief  Extrae string de objeto anidado para una clave
 * @param  json    JSON crudo
 * @param  key     campo cuyo valor es un objeto
 * @param  result  salida
 * @param  maxLen  max chars
 * @return void
 */
void extractObject(const char* json, const char* key,
                   char* result, int maxLen);

/**
 * @brief  Extrae string de arreglo anidado para una clave
 * @param  json    JSON crudo
 * @param  key     campo cuyo valor es un arreglo
 * @param  result  salida
 * @param  maxLen  max chars
 * @return void
 */
void extractNestedArray(const char* json, const char* key,
                        char* result, int maxLen);

// ── Capa 2 — un parser por struct ─────────────────────────────────────────

/**
 * @brief  Parsea un objeto JSON en Galaxy
 * @param  jsonObject  JSON crudo de una galaxia
 * @return nuevo Galaxy* en heap, o nullptr si falla
 */
Galaxy* parseGalaxia(const char* jsonObject);

/**
 * @brief  Parsea un objeto JSON en Edge
 * @param  jsonObject  JSON crudo de una ruta
 * @return nuevo Edge* en heap, o nullptr si falla
 */
Edge* parseRuta(const char* jsonObject);

/**
 * @brief  Parsea un objeto JSON en Ship
 * @param  jsonObject  JSON crudo de una nave
 * @return nuevo Ship* en heap, o nullptr si falla
 */
Ship* parseNave(const char* jsonObject);

/**
 * @brief  Parsea un objeto JSON en Trip
 * @param  jsonObject  JSON crudo de un viaje
 * @return nuevo Trip* en heap, o nullptr si falla
 */
Trip* parseViaje(const char* jsonObject);

// ── Capa 3 — una funcion por endpoint ─────────────────────────────────────

/**
 * @brief  Parsea GET /galaxias en lista enlazada de Galaxy
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseGalaxias(const char* json, Galaxy*& head);

/**
 * @brief  Parsea GET /galaxias/:id en un Galaxy
 * @param  json  respuesta del endpoint
 * @return nuevo Galaxy* en heap, o nullptr si falla
 */
Galaxy* parseGalaxiaById(const char* json);

/**
 * @brief  Parsea GET /rutas en lista enlazada de Edge
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseRutas(const char* json, Edge*& head);

/**
 * @brief  Parsea GET /rutas/:id en un Edge
 * @param  json  respuesta del endpoint
 * @return nuevo Edge* en heap, o nullptr si falla
 */
Edge* parseRutaById(const char* json);

/**
 * @brief  Parsea GET /naves en lista enlazada de Ship
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseNaves(const char* json, Ship*& head);

/**
 * @brief  Parsea GET /naves/:id en un Ship
 * @param  json  respuesta del endpoint
 * @return nuevo Ship* en heap, o nullptr si falla
 */
Ship* parseNaveById(const char* json);

/**
 * @brief  Parsea GET /historial en lista enlazada de Trip
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseHistorial(const char* json, Trip*& head);

/**
 * @brief  Parsea GET /historial/:id en un Trip
 * @param  json  respuesta del endpoint
 * @return nuevo Trip* en heap, o nullptr si falla
 */
Trip* parseViajeById(const char* json);

/**
 * @brief  Parsea GET /naves/:id/historial en lista enlazada de Trip
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseHistorialNave(const char* json, Trip*& head);

/**
 * @brief  Parsea GET /grafo en listas de Galaxy y Edge
 *         El endpoint devuelve objeto con "nodos" y "aristas"
 * @param  json   respuesta del endpoint
 * @param  gHead  salida — cabeza de la lista de Galaxy
 * @param  eHead  salida — cabeza de la lista de Edge
 * @return void
 */
void parseGrafo(const char* json, Galaxy*& gHead, Edge*& eHead);

/**
 * @brief  Parsea GET /grafo/kruskal en lista enlazada de Edge
 *         El endpoint devuelve objeto con "aristas" en orden aleatorio
 * @param  json  respuesta del endpoint
 * @param  head  salida — cabeza de la lista resultante
 * @return void
 */
void parseKruskal(const char* json, Edge*& head);

/**
 * @brief  Parsea GET /grafo/adyacencia en matriz dinamica float**
 *         El endpoint devuelve objeto con "orden", "nodos" y "matriz"
 *         Los valores pueden ser null (0.0) o float
 *         Quien llama es responsable de liberar la memoria
 * @param  json    respuesta del endpoint
 * @param  matrix  salida — matriz dinamica float**
 * @param  size    salida — numero de filas y columnas
 * @return void
 */
void parseAdyacencia(const char* json, float**& matrix, int& size);

#endif
