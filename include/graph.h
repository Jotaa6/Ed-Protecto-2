/*
 * Archivo: graph.h
 * Descripcion: Estructura del grafo con lista de adyacencia y matriz de adyacencia dinamica
 * Estructuras: Arco, Vertice
 * Funciones: insertarVertice, insertarArco, buscarVertice, eliminarVertice,
 *            eliminarArco, actualizarCostoArco, desmarcarVertices,
 *            cargarMatrizAdyacencia, imprimirGrafo
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include "galaxy.h"
#include "edge.h"
using namespace std;

/**
 * @brief  Representa un arco en la lista de adyacencia de un vertice
 * @field  destinoId  id string de la galaxia destino e.g. "galaxia-3"
 * @field  costo      costo de viaje de este arco como float
 * @field  sigA       puntero al siguiente arco en la lista del vertice
 */
struct Arco {
    string  destinoId;
    float   costo;
    Arco*   sigA;
};

/**
 * @brief  Representa un vertice del grafo (nodo galaxia)
 * @field  galaxyId       id string de la galaxia e.g. "galaxia-1"
 * @field  nombre         nombre de la galaxia para mostrar en pantalla
 * @field  visitado       flag de recorrido — resetear antes de cada algoritmo
 * @field  subListaArcos  puntero al primer arco de este vertice
 * @field  sigV           puntero al siguiente vertice en la lista global
 */
struct Vertice {
    string   galaxyId;
    string   nombre;
    bool     visitado;
    Arco*    subListaArcos;
    Vertice* sigV;
};

// Cabeza de la lista enlazada global de vertices
extern Vertice* grafo;

// Matriz de adyacencia dinamica cargada desde /grafo/adyacencia
extern float** adjMatrix;

// Numero de filas/columnas en la matriz de adyacencia
extern int matrixSize;

/**
 * @brief  Busca un vertice en el grafo global por su galaxyId string
 * @param  galaxyId  id string de la galaxia a buscar e.g. "galaxia-1"
 * @return puntero al Vertice si se encuentra, nullptr si no existe
 */
Vertice* buscarVertice(string galaxyId);

/**
 * @brief  Inserta un nuevo vertice en el grafo global
 *         No hace nada si ya existe un vertice con el mismo galaxyId
 * @param  galaxyId  id string de la galaxia
 * @param  nombre    nombre de la galaxia
 * @return void
 */
void insertarVertice(string galaxyId, string nombre);

/**
 * @brief  Inserta un arco dirigido de origen a destino
 *         Actualiza tanto la lista de adyacencia como adjMatrix
 * @param  origenId   id string de la galaxia origen
 * @param  destinoId  id string de la galaxia destino
 * @param  costo      costo del arco como float
 * @return void
 */
void insertarArco(string origenId, string destinoId, float costo);

/**
 * @brief  Elimina un vertice y todos sus arcos del grafo global
 *         Elimina tambien los arcos entrantes desde otros vertices
 * @param  galaxyId  id string del vertice a eliminar
 * @return void
 */
void eliminarVertice(string galaxyId);

/**
 * @brief  Elimina el arco de origen a destino
 * @param  origenId   id string de la galaxia origen
 * @param  destinoId  id string de la galaxia destino
 * @return void
 */
void eliminarArco(string origenId, string destinoId);

/**
 * @brief  Actualiza el costo del arco de origen a destino
 * @param  origenId    id string de la galaxia origen
 * @param  destinoId   id string de la galaxia destino
 * @param  nuevoCosto  nuevo costo a asignar como float
 * @return void
 */
void actualizarCostoArco(string origenId, string destinoId, float nuevoCosto);

/**
 * @brief  Resetea visitado = false en todos los vertices
 *         Llamar antes de cada recorrido BFS, DFS o Dijkstra
 * @return void
 */
void desmarcarVertices();

/**
 * @brief  Carga la matriz de adyacencia desde un arreglo 2D dinamico de float
 *         Libera memoria anterior si existe
 * @param  matrix  arreglo 2D dinamico float** con los valores
 * @param  size    numero de filas y columnas
 * @return void
 */
void cargarMatrizAdyacencia(float** matrix, int size);

/**
 * @brief  Imprime el grafo completo en terminal para verificacion
 * @return void
 */
void imprimirGrafo();

#endif
