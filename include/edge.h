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
 * @field  destinationId  id string de la galaxia destino e.g. "galaxia-4"
 * @field  tipo           tipo de ruta e.g. "subespacio", "wormhole", "convencional", "hiperespacio"
 * @field  cost           costo de viaje como float e.g. 803.58
 * @field  tiempoDias     tiempo de viaje en dias como float e.g. 11.36
 * @field  activa         true si la ruta esta activa, false si no
 * @field  siguiente      puntero al siguiente Edge en la lista enlazada global
 */
struct Edge {
    string  id;
    string  originId;
    string  destinationId;
    string  tipo;
    float   cost;
    float   tiempoDias;
    bool    activa;
    Edge*   siguiente;
};

#endif
