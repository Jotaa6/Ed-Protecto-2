/*
 * Archivo: edge.h
 * Descripcion: Struct Edge para representar una ruta entre galaxias en memoria
 * Estructuras: Edge
 * Funciones: ninguna propia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef EDGE_H
#define EDGE_H

#include <string>
using namespace std;

/**
 * @brief  Representa una ruta dirigida entre dos galaxias
 *         Los datos vienen unicamente de la API, se parsean y se guardan en memoria
 * @field  id             identificador unico de la API e.g. "ruta-1"
 * @field  originId       id string de la galaxia origen e.g. "galaxia-1"
 * @field  destinationId  id string de la galaxia destino e.g. "galaxia-11"
 * @field  cost           costo de viaje como float
 * @field  siguiente      puntero al siguiente Edge en la lista enlazada global
 */
struct Edge {
    string  id;
    string  originId;
    string  destinationId;
    float   cost;
    Edge*   siguiente;
};

#endif
