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
 * @field  id        identificador unico de la API e.g. "viaje-1"
 * @field  shipId    id string de la nave e.g. "nave-5"
 * @field  rutaId    id string de la ruta e.g. "ruta-8"
 * @field  date      fecha del viaje e.g. "2025-02-26"
 * @field  cost      costo real del viaje como float
 * @field  siguiente puntero al siguiente Trip en la lista enlazada global
 */
struct Trip {
    string  id;
    string  shipId;
    string  rutaId;
    string  date;
    float   cost;
    Trip*   siguiente;
};

#endif
