/*
 * Archivo: trip.h
 * Descripcion: Struct Trip para uso en memoria y TripFile para serializacion binaria
 * Estructuras: Trip, TripFile
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
 * @field  id             identificador unico de la API
 * @field  shipId         id de la nave que realizo el viaje
 * @field  originId       id de la galaxia origen
 * @field  destinationId  id de la galaxia destino
 * @field  cost           costo del viaje
 * @field  date           fecha en que ocurrio el viaje
 * @field  isLocal        false si viene de la API, true si fue creado por el usuario via CRUD
 *                        se usa para que local_storage solo persista registros del usuario
 *                        y no duplique los datos de la API al reiniciar
 * @field  siguiente      puntero al siguiente Trip en la lista enlazada global
 */
struct Trip {
    int    id;
    int    shipId;
    int    originId;
    int    destinationId;
    int    cost;
    string date;
    bool   isLocal;
    Trip*  siguiente;
};

/**
 * @brief  Version plana de Trip para serializacion binaria en archivo
 *         Usa char[] en lugar de string para escritura/lectura binaria segura
 *         Solo debe usarse en local_storage.cpp
 *         Todos los registros en datos_locales.txt son locales por definicion
 * @field  id             identificador unico
 * @field  shipId         id de la nave
 * @field  originId       id de la galaxia origen
 * @field  destinationId  id de la galaxia destino
 * @field  cost           costo del viaje
 * @field  date           fecha como arreglo de chars
 */
struct TripFile {
    int  id;
    int  shipId;
    int  originId;
    int  destinationId;
    int  cost;
    char date[50];
};

#endif
