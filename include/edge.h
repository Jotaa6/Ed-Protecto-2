/*
 * Archivo: edge.h
 * Descripcion: Struct Edge para uso en memoria y EdgeFile para serializacion binaria
 * Estructuras: Edge, EdgeFile
 * Funciones: ninguna propia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef EDGE_H
#define EDGE_H

/**
 * @brief  Representa una ruta dirigida entre dos galaxias
 *         Reutilizado por Kruskal — no se necesita un struct separado para eso
 * @field  id             identificador unico de la API
 * @field  originId       id de la galaxia origen
 * @field  destinationId  id de la galaxia destino
 * @field  cost           costo de viaje entre las dos galaxias
 * @field  isLocal        false si viene de la API, true si fue creada por el usuario via CRUD
 *                        se usa para que local_storage solo persista registros del usuario
 *                        y no duplique los datos de la API al reiniciar
 * @field  siguiente      puntero al siguiente Edge en la lista enlazada global
 */
struct Edge {
    int   id;
    int   originId;
    int   destinationId;
    int   cost;
    bool  isLocal;
    Edge* siguiente;
};

/**
 * @brief  Version plana de Edge para serializacion binaria en archivo
 *         Usa tipos primitivos para escritura/lectura binaria segura
 *         Solo debe usarse en local_storage.cpp
 * @field  id             identificador unico
 * @field  originId       id de la galaxia origen
 * @field  destinationId  id de la galaxia destino
 * @field  cost           costo de viaje
 * @field  isLocal        false si viene de la API, true si fue creada por el usuario
 */
struct EdgeFile {
    int  id;
    int  originId;
    int  destinationId;
    int  cost;
    bool isLocal;
};

#endif
