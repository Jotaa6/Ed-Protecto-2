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

/**
 * @brief  Representa una ruta dirigida entre dos galaxias
 *         Los datos vienen unicamente de la API, se parsean y se guardan en memoria
 * @field  id             identificador unico de la API
 * @field  originId       id de la galaxia origen
 * @field  destinationId  id de la galaxia destino
 * @field  cost           costo de viaje entre las dos galaxias
 * @field  siguiente      puntero al siguiente Edge en la lista enlazada global
 */
struct Edge {
    int   id;
    int   originId;
    int   destinationId;
    int   cost;
    Edge* siguiente;
};

#endif
