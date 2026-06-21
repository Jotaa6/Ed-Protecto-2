/*
 * Archivo: crud.h
 * Descripcion: Motor CRUD generico usando punteros a funciones
 * Estructuras: CrudConfig
 * Funciones: promptAndValidateId, runCrud
 * Creado: 7/6/2026
 * Ultima modificacion: 21/6/2026
 * Autores: Santiago Eloy Céspedes Mora, José Pablo Barrantes
 */
#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <string>
#include "../include/utils.h"

using namespace std;

/**
 * @brief  Configuracion CRUD para una entidad (Galaxia, Nave, Ruta, Viaje)
 * @field  entityName   nombre de la entidad (ej. "Galaxia")
 * @field  listAll      funcion que imprime todos los registros
 * @field  add          funcion que agrega un nuevo registro
 * @field  edit         funcion que edita un registro por ID
 * @field  remove       funcion que elimina un registro por ID
 * @field  findById     funcion que busca un registro por ID y devuelve void*
 * @field  printDetail  funcion que imprime los detalles de un registro (void*)
 */
struct CrudConfig {
    const char* entityName;
    void  (*listAll)();
    void  (*add)();
    void  (*edit)(string id);
    void  (*remove)(string id);
    void* (*findById)(string id);
    void  (*printDetail)(void* item);
};

/**
 * @brief  Solicita un ID al usuario y valida que exista en la lista de la entidad
 * @param  config  configuracion CRUD de la entidad
 * @return ID ingresado (string) si existe, cadena vacia si no se encuentra
 */
string promptAndValidateId(CrudConfig config);

/**
 * @brief  Ejecuta el submenu CRUD generico para cualquier entidad
 *         Contiene loop do-while, switch y try-catch por opcion
 * @param  config  configuracion CRUD de la entidad
 * @return void
 */
void runCrud(CrudConfig config);

#endif
