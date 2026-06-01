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
 * @field  id        identificador unico de la API e.g. "galaxia-1"
 * @field  name      nombre de la galaxia e.g. "Oxygen Galaxy"
 * @field  code      codigo unico e.g. "GAL-PHEXUF"
 * @field  type      tipo de galaxia e.g. "irregular", "espiral", "eliptica", "lenticular"
 * @field  x         coordenada X
 * @field  y         coordenada Y
 * @field  z         coordenada Z
 * @field  siguiente puntero al siguiente Galaxy en la lista enlazada global
 */
struct Galaxy {
    string  id;
    string  name;
    string  code;
    string  type;
    float   x, y, z;
    Galaxy* siguiente;
};

#endif
