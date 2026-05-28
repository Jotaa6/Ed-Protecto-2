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
 *         Sigue el estilo de recorrido_grafos.cpp
 * @field  destinoId  id de la galaxia destino
 * @field  costo      costo de viaje de este arco
 * @field  sigA       puntero al siguiente arco en la lista de arcos del vertice
 */
struct Arco {
    int   destinoId;
    int   costo;
    Arco* sigA;
};

/**
 * @brief  Representa un vertice del grafo (nodo galaxia)
 *         Sigue el estilo de recorrido_grafos.cpp
 * @field  galaxyId       id de la galaxia que representa este vertice
 * @field  nombre         nombre de la galaxia para mostrar en pantalla
 * @field  visitado       flag de recorrido — debe resetearse antes de cada algoritmo
 * @field  subListaArcos  puntero al primer arco en la lista de arcos de este vertice
 * @field  sigV           puntero al siguiente vertice en la lista enlazada global
 */
struct Vertice {
    int      galaxyId;
    string   nombre;
    bool     visitado;
    Arco*    subListaArcos;
    Vertice* sigV;
};

// Cabeza de la lista enlazada global de vertices
extern Vertice* grafo;

// Matriz de adyacencia dinamica cargada desde /grafo/adyacencia
extern int** adjMatrix;

// Numero de filas/columnas en la matriz de adyacencia
extern int matrixSize;

/**
 * @brief  Busca un vertice en el grafo global por su galaxyId
 * @param  galaxyId  id de la galaxia a buscar
 * @return puntero al Vertice si se encuentra, nullptr si no existe
 */
Vertice* buscarVertice(int galaxyId);

/**
 * @brief  Inserta un nuevo vertice en el grafo global
 *         No hace nada si ya existe un vertice con el mismo galaxyId
 * @param  galaxyId  id de la galaxia a insertar
 * @param  nombre    nombre de la galaxia
 * @return void
 */
void insertarVertice(int galaxyId, string nombre);

/**
 * @brief  Inserta un arco dirigido de origen a destino
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  origenId   id de la galaxia origen
 * @param  destinoId  id de la galaxia destino
 * @param  costo      costo del arco
 * @return void
 */
void insertarArco(int origenId, int destinoId, int costo);

/**
 * @brief  Elimina un vertice y todos sus arcos del grafo global
 *         Elimina tambien los arcos entrantes desde otros vertices
 *         para evitar arcos colgando apuntando a un vertice inexistente
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  galaxyId  id del vertice a eliminar
 * @return void
 */
void eliminarVertice(int galaxyId);

/**
 * @brief  Elimina el arco de origen a destino
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  origenId   id de la galaxia origen
 * @param  destinoId  id de la galaxia destino
 * @return void
 */
void eliminarArco(int origenId, int destinoId);

/**
 * @brief  Actualiza el costo del arco de origen a destino
 *         Actualiza tanto la lista de adyacencia como adjMatrix[][]
 * @param  origenId    id de la galaxia origen
 * @param  destinoId   id de la galaxia destino
 * @param  nuevoCosto  nuevo costo a asignar
 * @return void
 */
void actualizarCostoArco(int origenId, int destinoId, int nuevoCosto);

/**
 * @brief  Resetea visitado = false en todos los vertices del grafo
 *         Debe llamarse antes de cada recorrido BFS, DFS o Dijkstra
 * @return void
 */
void desmarcarVertices();

/**
 * @brief  Carga la matriz de adyacencia desde un arreglo 2D dinamico
 *         Libera memoria anterior si existe y asigna nueva memoria dinamica
 * @param  matrix  arreglo 2D dinamico fuente con los valores de adyacencia
 * @param  size    numero de filas y columnas
 * @return void
 */
void cargarMatrizAdyacencia(int** matrix, int size);

/**
 * @brief  Imprime el grafo completo en terminal para verificacion
 * @return void
 */
void imprimirGrafo();

#endif
