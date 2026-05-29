/*
 * Archivo: trip.h
 * Descripcion: Struct Trip para representar un viaje registrado en memoria
 * Estructuras: Trip
 * Funciones: ninguna propia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef TRIP_H
#define TRIP_H

#include <string>
using namespace std;

/**
 * @brief  Representa un viaje registrado por una nave entre dos galaxias
 *         Los datos vienen unicamente de la API, se parsean y se guardan en memoria
 * @field  id             identificador unico de la API
 * @field  shipId         id de la nave que realizo el viaje
 * @field  originId       id de la galaxia origen
 * @field  destinationId  id de la galaxia destino
 * @field  cost           costo del viaje
 * @field  date           fecha en que ocurrio el viaje
 * @field  siguiente      puntero al siguiente Trip en la lista enlazada global
 */
struct Trip {
    int    id;
    int    shipId;
    int    originId;
    int    destinationId;
    int    cost;
    string date;
    Trip*  siguiente;
};

#endif
