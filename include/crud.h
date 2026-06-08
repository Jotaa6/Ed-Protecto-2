/*
 * Archivo: crud.h
 * Descripcion: Motor CRUD generico con punteros a funciones
 * Estructuras: CrudConfig
 * Funciones: runCrud, promptAndValidateId
 * Creado: 7/6/2026
 * Ultima modificacion: 2026
 * Autores: Santiago Eloy Céspedes Mora
 */
#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <string>
#include "utils.h"
using namespace std;

/**
 * @brief  Struct de configuracion que define el comportamiento CRUD para una entidad
 * @field  entityName  nombre para mostrar e.g. "Galaxia", "Nave"
 * @field  listAll     funcion que imprime todos los registros
 * @field  add         funcion que solicita al usuario e inserta un registro
 * @field  edit        funcion que edita un registro por id string
 * @field  remove      funcion que elimina un registro por id string
 * @field  findById    funcion que busca un registro por id string
 */
struct CrudConfig {
    const char* entityName;
    void  (*listAll)();
    void  (*add)();
    void  (*edit)(string id);
    void  (*remove)(string id);
    void* (*findById)(string id);
};

/**
 * @brief  Ejecuta el submenu CRUD generico para cualquier entidad
 *         Contiene el loop do-while, switch y try-catch por opcion
 *         Escrito una vez, usado por todas las entidades
 * @param  config  struct CrudConfig con nombre de entidad y punteros a funciones
 * @return void
 */
void runCrud(CrudConfig config);

/**
 * @brief  Solicita un id al usuario y valida que exista en la lista de la entidad
 * @param  config  CrudConfig de la entidad siendo buscada
 * @return id ingresado por el usuario, o "" si no se encuentra
 */
string promptAndValidateId(CrudConfig config);

#endif
