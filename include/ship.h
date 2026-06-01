/*
 * Archivo: ship.h
 * Descripcion: Struct Ship para representar una nave en memoria
 * Estructuras: Ship
 * Funciones: ninguna propia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef SHIP_H
#define SHIP_H

#include <string>
#include "trip.h"
using namespace std;

/**
 * @brief  Representa una nave registrada y su historial de viajes
 *         Los datos vienen unicamente de la API, se parsean y se guardan en memoria
 * @field  id           identificador unico de la API e.g. "nave-1"
 * @field  name         nombre de la nave e.g. "Chevrolet ATS 6K"
 * @field  code         codigo unico de la nave e.g. "NV-ENJCH"
 * @field  capacidad    capacidad de la nave e.g. 262
 * @field  velocidadMax velocidad maxima de la nave e.g. 4684
 * @field  activa       true si la nave esta activa, false si no
 * @field  tripHistory  puntero al primer Trip en la lista enlazada de historial
 * @field  siguiente    puntero al siguiente Ship en la lista enlazada global
 */
struct Ship {
    string  id;
    string  name;
    string  code;
    int     capacidad;
    int     velocidadMax;
    bool    activa;
    Trip*   tripHistory;
    Ship*   siguiente;
};

#endif
