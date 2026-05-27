/*
 * Archivo: galaxy.h
 * Descripcion: Struct Galaxy para uso en memoria y GalaxyFile para serializacion binaria
 * Estructuras: Galaxy, GalaxyFile
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
 * @field  id        identificador unico de la API
 * @field  name      nombre de la galaxia en memoria
 * @field  code      codigo unico para validacion de duplicados
 * @field  x         coordenada X
 * @field  y         coordenada Y
 * @field  z         coordenada Z
 * @field  isLocal   false si viene de la API, true si fue creada por el usuario via CRUD
 *                   se usa para que local_storage solo persista registros del usuario
 *                   y no duplique los datos de la API al reiniciar
 * @field  siguiente puntero al siguiente Galaxy en la lista enlazada global
 */
struct Galaxy {
    int     id;
    string  name;
    string  code;
    float   x, y, z;
    bool    isLocal;
    Galaxy* siguiente;
};

/**
 * @brief  Version plana de Galaxy para serializacion binaria en archivo
 *         Usa char[] en lugar de string para escritura/lectura binaria segura
 *         Solo debe usarse en local_storage.cpp
 * @field  id       identificador unico
 * @field  name     nombre como arreglo de chars
 * @field  code     codigo como arreglo de chars
 * @field  x        coordenada X
 * @field  y        coordenada Y
 * @field  z        coordenada Z
 * @field  isLocal  false si viene de la API, true si fue creada por el usuario
 */
struct GalaxyFile {
    int   id;
    char  name[100];
    char  code[50];
    float x, y, z;
    bool  isLocal;
};

#endif
