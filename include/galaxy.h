/*
 * Archivo: galaxy.h
 * Descripcion: Struct Galaxy para representar una galaxia en memoria
 * Estructuras: Galaxy
 * Funciones: ninguna propia
 * Creado: 2026
 * Ultima modificacion: 2026
 * Autores: <integrantes>
 */
#ifndef GALAXY_H
#define GALAXY_H

#include <string>
using namespace std;

/**
 * @brief  Representa una galaxia — usada como vertice en el grafo
 *         Los datos vienen unicamente de la API, se parsean y se guardan en memoria
 * @field  id        identificador unico de la API
 * @field  name      nombre de la galaxia
 * @field  code      codigo unico para validacion de duplicados
 * @field  x         coordenada X
 * @field  y         coordenada Y
 * @field  z         coordenada Z
 * @field  siguiente puntero al siguiente Galaxy en la lista enlazada global
 */
struct Galaxy {
    int     id;
    string  name;
    string  code;
    float   x, y, z;
    Galaxy* siguiente;
};

#endif
