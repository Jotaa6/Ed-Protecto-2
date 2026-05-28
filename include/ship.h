/*
 * Archivo: ship.h
 * Descripcion: Struct Ship para uso en memoria y ShipFile para serializacion binaria
 * Estructuras: Ship, ShipFile
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
 * @field  id           identificador unico de la API
 * @field  name         nombre de la nave
 * @field  isLocal      false si viene de la API, true si fue creada por el usuario via CRUD
 *                      se usa para que local_storage solo persista registros del usuario
 *                      y no duplique los datos de la API al reiniciar
 * @field  tripHistory  puntero al primer Trip en la lista enlazada de historial de esta nave
 * @field  siguiente    puntero al siguiente Ship en la lista enlazada global
 */
struct Ship {
    int   id;
    string name;
    bool  isLocal;
    Trip* tripHistory;
    Ship* siguiente;
};

/**
 * @brief  Version plana de Ship para serializacion binaria en archivo
 *         Usa char[] en lugar de string para escritura/lectura binaria segura
 *         Solo debe usarse en local_storage.cpp
 *         Todos los registros en datos_locales.txt son locales por definicion
 *         por lo tanto no necesita campo isLocal
 * @field  id    identificador unico
 * @field  name  nombre de la nave como arreglo de chars
 */
struct ShipFile {
    int  id;
    char name[100];
};

#endif
