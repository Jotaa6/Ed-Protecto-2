/*
 * Archivo: crud.cpp
 * Descripcion: Implementacion del motor CRUD generico
 * Estructuras: CrudConfig
 * Funciones: promptAndValidateId, runCrud
 * Creado: 7/6/2026
 * Ultima modificacion: 21/6/2026
 * Autores: Santiago Eloy Céspedes Mora, José Pablo Barrantes
 */
#include "../include/crud.h"

/**
 * @brief  Solicita un ID al usuario y valida que exista en la lista de la entidad
 * @param  config  configuracion CRUD de la entidad
 * @return ID ingresado (string) si existe, cadena vacia si no se encuentra
 */
string promptAndValidateId(CrudConfig config) {
    char buf[100];
    pedirCadena("Ingrese el ID: ", buf, 100);
    string id = string(buf);

    if (config.findById == nullptr) {
        cout << "No existe funcion de busqueda para " << config.entityName << "." << endl;
        return "";
    }

    if (config.findById(id) == nullptr) {
        cout << config.entityName << " no encontrado." << endl;
        return "";
    }

    return id;
}

/**
 * @brief  Ejecuta el submenu CRUD generico para cualquier entidad
 *         Contiene loop do-while, switch y try-catch por opcion
 * @param  config  configuracion CRUD de la entidad
 * @return void
 */
void runCrud(CrudConfig config) {
    int opcion = 0;

    do {
        cout << "\n=== CRUD DE " << config.entityName << " ===" << endl;
        cout << "1. Listar" << endl;
        cout << "2. Agregar" << endl;
        cout << "3. Editar" << endl;
        cout << "4. Eliminar" << endl;
        cout << "5. Buscar por ID" << endl;
        cout << "0. Volver" << endl;
        opcion = pedirEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                try {
                    if (config.listAll != nullptr) config.listAll();
                    else cout << "Funcion listar no disponible." << endl;
                } catch (...) {
                    cout << "Ocurrio un error al listar." << endl;
                }
                break;

            case 2:
                try {
                    if (config.add != nullptr) config.add();
                    else cout << "Funcion agregar no disponible." << endl;
                } catch (...) {
                    cout << "Ocurrio un error al agregar." << endl;
                }
                break;

            case 3:
                try {
                    if (config.edit != nullptr) {
                        string id = promptAndValidateId(config);
                        if (id != "") config.edit(id);
                    } else {
                        cout << "Funcion editar no disponible." << endl;
                    }
                } catch (...) {
                    cout << "Ocurrio un error al editar." << endl;
                }
                break;

            case 4:
                try {
                    if (config.remove != nullptr) {
                        string id = promptAndValidateId(config);
                        if (id != "") config.remove(id);
                    } else {
                        cout << "Funcion eliminar no disponible." << endl;
                    }
                } catch (...) {
                    cout << "Ocurrio un error al eliminar." << endl;
                }
                break;

            case 5:
                try {
                    string id = promptAndValidateId(config);
                    if (id != "") {
                        void* item = config.findById(id);
                        if (item != nullptr) {
                            cout << config.entityName << " encontrado:" << endl;
                            if (config.printDetail != nullptr) {
                                config.printDetail(item);
                            } else {
                                cout << "(No hay funcion de detalle para esta entidad.)" << endl;
                            }
                        }
                    }
                } catch (...) {
                    cout << "Ocurrio un error al buscar." << endl;
                }
                break;

            case 0:
                cout << "Regresando al menu anterior..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
        }

    } while (opcion != 0);
}
